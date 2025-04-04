// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Menu.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include "VolumeMenu.h"


using namespace agp;

MenuItem::MenuItem(Menu* container, int index, const std::string& text, std::function<void()> task)
	: RenderableObject(container,
		RectF(
			container->menuRect().left(),
			container->menuRect().top() + 0.5f + 0.7f * index,
			container->menuRect().size.x, 0.5f),
		SpriteFactory::instance()->getText(' ' +text, { 0.5f, 0.5f }, 0, ' ', false))
{
	_container = container;
	_index = index;
	_text = text;
	_task = task;
	_selected = false;
	_focusColor = { 255, 255, 255, 128 };
	
}

void MenuItem::refresh()
{
	setSprite(SpriteFactory::instance()->getText(' ' + _text, { 0.5f + _selected / 30.0f, 0.5f + _selected / 30.0f }, 0, ' ', _selected));
}

void MenuItem::update(float dt)
{
	RenderableObject::update(dt);
	//_focused = _selected;
}

Menu::Menu(const PointF& position, float width, Menu* parent, bool closable)
	: UIScene(RectF(0, 0, 16, 15))
{
	_parent = parent;
	_itemSelected = 0;
	_menuRect = { position.x, position.y, width, 0.5f };
	_closable = closable;

	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, Color(0, 0, 0, 255));
	_menuBackground->setBorderColor({ 0, 0, 0, 255 });

	// default: modal menu (blocks all lower scenes)
	_blocking = true;
	animation_scheduler = nullptr;
	logo = nullptr;
	ok_controls = true;

}

Menu::Menu(Menu* parent)
	: Menu(parent->menuRect().tl(), parent->menuRect().size.x, parent)
{
}

MenuItem* Menu::addItem(const std::string& text, std::function<void()> task)
{
	MenuItem* item = new MenuItem(this, int(_items.size()), text, task);
	_items.push_back(item);
	if (_items.size() == 1)
		item->setSelected(true);

	_menuRect.size.y = 0.5f + _items.size() * 0.7f + 0.3f;
	_menuBackground->setRect(_menuRect);

	return item;
}

void Menu::event(SDL_Event& evt)
{
	UIScene::event(evt);
	
		if (evt.type == SDL_KEYDOWN)
		{
			if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_itemSelected]->setSelected(false);
				_itemSelected = (_itemSelected + 1) % int(_items.size());
				_items[_itemSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_itemSelected]->setSelected(false);
				_itemSelected = (_itemSelected - 1) < 0 ? int(_items.size()) - 1 : _itemSelected - 1;
				_items[_itemSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				_items[_itemSelected]->run();
			}
			else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE || evt.key.keysym.scancode == SDL_SCANCODE_LEFT))
			{
				Audio::instance()->playSound("40 Dragon Quest 1 - Missed!");
				Game::instance()->popSceneLater();
			}
		}
	
}

Menu* Menu::mainMenu()
{
	
	Menu* menu = new Menu({ 5.0, 7.5 }, 6.0, 0, false);
	new RenderableObject(menu, RectF(0, 0, 20, 20), Color(0, 0, 0, 255));
	new RenderableObject(menu, RectF(3, 2, 9,5), SpriteFactory::instance()->get("logo_animation"));
	menu->addItem("New Game", []()
		{
			Audio::instance()->pauseMusic();
			Game::instance()->popSceneLater();
			Audio::instance()->playMusic("02 Dragon Quest 1 - Tantegel Castle");
		});
	menu->addItem("Options", [menu]()
		{
			Menu* nestedMenu = new Menu(menu);
			nestedMenu->addItem("Commands", [nestedMenu]() {
				Game::instance()->pushScene(Dialogue_Menu::commands());
				});
			nestedMenu->addItem("Volume", [nestedMenu]() {Game::instance()->pushScene(VolumeMenu::volume_menu());});
			SDL_RendererInfo info;
			SDL_GetRendererInfo(Game::instance()->window()->renderer(), &info);
			bool vsyncOn = info.flags & SDL_RENDERER_PRESENTVSYNC;
			nestedMenu->addItem("Tips", [nestedMenu]() {
				Game::instance()->pushScene(Dialogue_Menu::tips());
				});
			nestedMenu->addItem(std::string("Vsync ") + (vsyncOn ? "On" : "Off"), [nestedMenu]()
				{
					bool vsyncOn = nestedMenu->itemAt(3)->text() == "Vsync On";
					nestedMenu->itemAt(3)->setText(vsyncOn ? "Vsync Off" : "Vsync On");
					SDL_RenderSetVSync(Game::instance()->window()->renderer(), !vsyncOn);
				});
			Game::instance()->pushScene(nestedMenu);
		});
	menu->addItem("Quit", []() {Game::instance()->quit(); });

	Audio::instance()->playMusic("01 Dragon Quest 1 - Intro ~ Overture");
	return menu;
}
