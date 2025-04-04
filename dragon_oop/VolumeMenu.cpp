#include "VolumeMenu.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include <iostream>


using namespace agp;

VolumeMenuItem::VolumeMenuItem(VolumeMenu* container, int index, const std::string& text, std::function<void()> task)
	: RenderableObject(container,
		RectF(
			container->menuRect().left(),
			container->menuRect().top() + 0.5f + 1.5f * index,
			container->menuRect().size.x, 0.5f),
		SpriteFactory::instance()->getText(' ' + text, { 0.5f, 0.5f }, 0, ' ', false))
{
	_container = container;
	_index = index;
	_text = text;
	_task = task;
	_selected = false;
	_focusColor = { 255, 255, 255, 128 };
	token1 = new RenderableObject(container, RectF(_rect.size.x - 5, _rect.top() - 0.6f, 1.5f, 1.5f), Color(0, 0, 255, 0));
	token2 = new RenderableObject(container, RectF(_rect.size.x - 3.5f, _rect.top() - 0.6f, 1.5f, 1.5f), Color(0, 0, 255, 0));
	token3 = new RenderableObject(container, RectF(_rect.size.x - 2.0f, _rect.top() - 0.6f, 1.5f, 1.5f), Color(0, 0, 255, 0));
	token4 = new RenderableObject(container, RectF(_rect.size.x - 0.5f, _rect.top() - 0.6f, 1.5f, 1.5f), Color(0, 0, 255, 0));


}

void VolumeMenuItem::refresh()
{
	setSprite(SpriteFactory::instance()->getText(' ' + _text, { 0.5f + _selected / 30.0f, 0.5f + _selected / 30.0f }, 0, ' ', _selected));
}

void VolumeMenuItem::update(float dt)
{
	RenderableObject::update(dt);
	//_focused = _selected;

	updateSprite();


}
void VolumeMenuItem::updateSprite() {
	if (_index == 0) {
		int soundvolume = Mix_Volume(-1,-1);
		if (soundvolume > 0)
			token1->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token1->setSprite(nullptr);
		if (soundvolume > 32)
			token2->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token2->setSprite(nullptr);
		if (soundvolume > 64)
			token3->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token3->setSprite(nullptr);
		if (soundvolume > 96)
			token4->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token4->setSprite(nullptr);
	}
	if(_index == 1) {
		int musicvolume = Mix_VolumeMusic(-1);
		if (musicvolume > 0) 
			token1->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token1->setSprite(nullptr);
		if (musicvolume > 32)
			token2->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token2->setSprite(nullptr);
		if (musicvolume > 64)
			token3->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token3->setSprite(nullptr);
		if (musicvolume > 96)
			token4->setSprite(SpriteFactory::instance()->get("yellow_ghost"));
		else
			token4->setSprite(nullptr);
	}
}
VolumeMenu::VolumeMenu(const PointF& position, float width, VolumeMenu* parent, bool closable)
	: UIScene(RectF(0, 0, 16, 15))
{
	_parent = parent;
	_itemSelected = 0;
	_menuRect = { position.x, position.y, width, 0.5f };
	_closable = closable;

	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, Color(0, 0, 0, 255));
	_menuBackground->setBorderColor({ 255, 255, 255, 0 });

	// default: modal menu (blocks all lower scenes)
	_blocking = true;
	animation_scheduler = nullptr;
	logo = nullptr;
	left = false;
	right = false;
}

VolumeMenu::VolumeMenu(VolumeMenu* parent)
	: VolumeMenu(parent->menuRect().tl(), parent->menuRect().size.x, parent)
{
}

VolumeMenuItem* VolumeMenu::addItem(const std::string& text, std::function<void()> task)
{
	VolumeMenuItem* item = new VolumeMenuItem(this, int(_items.size()), text, task);
	_items.push_back(item);
	if (_items.size() == 1)
		item->setSelected(true);

	_menuRect.size.y = 1.5f + _items.size() * 0.7f + 0.3f;
	_menuBackground->setRect(_menuRect);

	return item;
}

void VolumeMenu::event(SDL_Event& evt)
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
		else if (evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
			right = true;
			left = false;
			_items[_itemSelected]->run();
		}
		else if (evt.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
			right = false;
			left = true;
			_items[_itemSelected]->run();
		}
		else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		{
			Audio::instance()->playSound("40 Dragon Quest 1 - Missed!");
			Game::instance()->popSceneLater();
		}
	}
}

VolumeMenu* VolumeMenu::volume_menu()
{

	VolumeMenu* menu = new VolumeMenu({ 2.5, 7.5 }, 11.5, 0, true);
	menu->addItem("Sound:", [menu]()
		{
			int chunkvolume = Mix_Volume(-1, -1);
			if (menu->getLeft())
				chunkvolume -= 32;
			else
				chunkvolume += 32;
			int volume = Mix_Volume(-1, chunkvolume);
			
			
		});
	menu->addItem("Music:", [menu]()
		{
			int musicvolume = Mix_VolumeMusic(-1);
			if (menu->getLeft()) 
				musicvolume -= 32;
			else
				musicvolume += 32;
			int volume = Mix_VolumeMusic(musicvolume);
		});
	return menu;
}
