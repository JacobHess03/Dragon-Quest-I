#pragma once
#include "UIScene.h"
#include "RenderableObject.h"
#include <string>
#include <vector>
#include <functional>
#include "Npc.h"

namespace agp
{
	class VolumeMenuItem;
	class VolumeMenu;
}

// MenuItem
// - implements a simple textSprite-based menu item
class agp::VolumeMenuItem : public RenderableObject
{
protected:

	VolumeMenu* _container;
	int _index;
	int _selected;
	RenderableObject* token1;
	RenderableObject* token2;
	RenderableObject* token3;
	RenderableObject* token4;

	std::string _text;
	std::function<void()> _task;	// performed when Enter pressed on this item

public:

	VolumeMenuItem(VolumeMenu* container, int index, const std::string& text, std::function<void()> task);
	virtual ~VolumeMenuItem() {};

	bool selected() { return _selected; }
	void setSelected(bool on) { _selected = on; refresh(); }
	const std::string& text() { return _text; }
	void setText(const std::string& text) { _text = text; refresh(); }
	void refresh();

	void run() { _task(); }

	// extends update logic (+selection)
	virtual void update(float dt) override;
	void updateSprite();
	
};

// Menu
// - implements a simple multiple-choice Menu
class agp::VolumeMenu : public UIScene
{
protected:

	VolumeMenu* _parent;
	RectF _menuRect;
	int _itemSelected;
	bool _closable;
	std::vector< VolumeMenuItem* > _items;
	RenderableObject* _menuBackground;
	RenderableObject* logo;
	Scheduler* animation_scheduler;
	bool right;
	bool left;

public:

	VolumeMenu(const PointF& position, float width, VolumeMenu* parent = 0, bool closable = true);
	VolumeMenu(VolumeMenu* parent);
	virtual ~VolumeMenu() {};

	// getters/setters (to be completed)
	const RectF& menuRect() { return _menuRect; }
	VolumeMenuItem* addItem(const std::string& text, std::function<void()> task);
	VolumeMenuItem* itemAt(int index) { return _items[index]; }
	bool getRight() { return right; }
	bool getLeft() { return left; }


	// extends event handler (+menu selection)
	virtual void event(SDL_Event& evt) override;

	// provide main menus
	static VolumeMenu* volume_menu();
	



};