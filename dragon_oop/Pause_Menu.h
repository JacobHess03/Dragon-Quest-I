#pragma once
#include "UIScene.h"
#include "RenderableObject.h"
#include <string>
#include <vector>
#include <functional>
#include "Npc.h"
#include "Seller.h"

namespace agp
{
	class Pause_MenuItem;
	class Pause_Menu;
}

// Pause_MenuItem
class agp::Pause_MenuItem : public RenderableObject
{
private:

	Pause_Menu* _container;
	int _selected;
	std::string _text;
	std::function<void()> _task;	// performed when Enter pressed on this item

public:

	Pause_MenuItem(int row, int col, Pause_Menu* container, const std::string& text, std::function<void()> task);
	virtual ~Pause_MenuItem() {};

	bool selected() { return _selected; }
	void setSelected(bool on) { _selected = on; refresh(); }
	const std::string& text() { return _text; }
	void setText(const std::string& text) { _text = text; refresh(); }
	void refresh();

	void run() { _task(); }

	void lightup() { _focused = _selected; }
	std::string getText() { return _text; }
	// extends update logic (+selection)
	virtual void update(float dt) override;
};

// Menu
// - implements a simple multiple-choice Menu
class agp::Pause_Menu : public UIScene
{
private:

	Pause_Menu* _parent;
	RectF _menuRect;
	int _colSelected;
	int _rowSelected;
	bool _closable;
	std::vector<std::vector<Pause_MenuItem*>> _items;
	RenderableObject* _menuBackground;
	int _cols;
	int _rows;

public:

	Pause_Menu(int cols, int rows, const PointF& position, float width, Pause_Menu* parent = 0, bool closable = true);
	Pause_Menu(int cols,int rows,Pause_Menu* parent);
	virtual ~Pause_Menu() {};

	// getters/setters (to be completed)
	const RectF& menuRect() { return _menuRect; }
	int getCols() { return _cols; }
	int getRows() { return _rows; }
	std::vector<std::vector<Pause_MenuItem*>> getItems() { return _items; }
	Pause_MenuItem* addItem(int col, int row, const std::string& text, std::function<void()> task);
	Pause_MenuItem* itemAt(int col, int row) { return _items[row][col]; }
	
	// extends event handler (+menu selection)
	virtual void event(SDL_Event& evt) override;

	// provide main menus
	//static Menu* mainMenu();
	static Pause_Menu* pauseMenu(Hero* hero);
	static Pause_Menu* deathMenu();
	static Pause_Menu* pauseMenuSeller(Hero* hero, Seller* seller);
	static Pause_Menu* victory_menu();
	//info functions
	void infoSpell(Spell* spell);
	void infoItem(Item* item);


};