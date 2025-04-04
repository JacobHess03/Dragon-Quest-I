#pragma once
#include "UIScene.h"
#include "RenderableObject.h"
#include <string>
#include <vector>
#include <functional>
#include "Npc.h"
#include "Battle_Menu.h"
#include "Monster.h"
#include "HUD.h"

namespace agp
{
	class Battle_MenuItem;
	class Battle_Menu;
}
class agp::Battle_MenuItem : public RenderableObject
{
private:

	Battle_Menu* _container;
	int _selected;
	std::string _text;
	std::function<void()> _task;	// performed when Enter pressed on this item

public:

	Battle_MenuItem(int row, int col, Battle_Menu* container, const std::string& text, std::function<void()> task);
	virtual ~Battle_MenuItem() {};

	bool selected() { return _selected; }
	void setSelected(bool on) { _selected = on; refresh(); }
	const std::string& text() { return _text; }
	void setText(const std::string& text) { _text = text; refresh(); }
	void refresh();

	void run() { _task(); }

	// extends update logic (+selection)
	virtual void update(float dt) override;
};

// Menu
// - implements a simple multiple-choice Menu
class agp::Battle_Menu : public UIScene
{
private:

	Battle_Menu* _parent;
	RectF _menuRect;
	RectF _fightField;
	RectF _hud;
	int _colSelected;
	int _rowSelected;
	bool _closable;
	std::vector<std::vector<Battle_MenuItem*>> _items;
	RenderableObject* _menuBackground;
	RenderableObject* _fieldBackground;
	RenderableObject* _hudBackground;
	int _cols;
	int _rows;
	bool monster_death;
	bool hero_death;
	
	bool ok_controls;
	int popup_counter=0;
	int i = 255;


public:

	Battle_Menu(int cols, int rows, const PointF& position, float width, Battle_Menu* parent = 0, bool closable = true);
	Battle_Menu(int cols, int rows, Battle_Menu* parent);
	virtual ~Battle_Menu() {};
	virtual void update(float timeToSimulate) override;

	// getters/setters (to be completed)
	const RectF& menuRect() { return _menuRect; }
	int getCols() { return _cols; }
	int getRows() { return _rows; }
	Battle_MenuItem* addItem(int col, int row, const std::string& text, std::function<void()> task);
	Battle_MenuItem* itemAt(int col, int row) { return _items[row][col]; }
	bool getMonster_Death() { return monster_death; }
	bool getHero_Death() { return hero_death; }
	int getPopupCounter() { return popup_counter; }
	void setControls() { ok_controls = true; }
	RenderableObject* getMenuBackground() { return _menuBackground; }
	RenderableObject* getFieldBackground() { return _fieldBackground; }
	RenderableObject* getHudBackground() { return _hudBackground; }
	//void addText();

	// extends event handler (+menu selection)
	virtual void event(SDL_Event& evt) override;

	// provide main menus
	//static Menu* mainMenu();
	static Battle_Menu* BattleMenu(const std::string monster_name,Hero* hero,std::string map);
	//battle
	void battle(Hero* hero, Monster* monster);
	void Spellbattle(Hero* hero, Monster* monster, Spell* spell);
	void Itembattle(Hero* hero, Monster* monster, Item* item);
	//transition
	void increaseA(int n);
	void decreaseA(int n);

	
};