#include "Battle_Menu.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include <iostream>
#include "Menu.h"
#include "Hero.h"
#include "Dialogue_Menu.h"
#include <iostream>
#include "Pause_Menu.h"



using namespace agp;

Battle_MenuItem::Battle_MenuItem(int row, int col, Battle_Menu* container, const std::string& text, std::function<void()> task)
	: RenderableObject(container,
		RectF(
			container->menuRect().left() + 0.5f + 6 * (col - 1),
			container->menuRect().top() + 0.5f + 0.7f * (row - 1),
			container->menuRect().size.x / (container->getCols() + 1) + 2, 0.5f),
		SpriteFactory::instance()->getText(' ' + text, { 0.5f, 0.5f }, 0, ' ', false))
{
	_container = container;
	_text = text;
	_task = task;
	_selected = false;
	_focusColor = { 255, 255, 255, 128 };
}

void Battle_MenuItem::refresh()
{
	setSprite(SpriteFactory::instance()->getText(' ' + _text, { 0.5f + _selected / 30.0f, 0.5f + _selected / 30.0f }, 0, ' ', _selected));
}

void Battle_MenuItem::update(float dt)
{
	RenderableObject::update(dt);

	//_focused = _selected;
}

Battle_Menu::Battle_Menu(int cols, int rows, const PointF& position, float width, Battle_Menu* parent, bool closable)
	: UIScene(RectF(0, 0, 16, 15))
{
	_rows = rows;
	_cols = cols;
	_parent = parent;
	_rowSelected = 0;
	_colSelected = 0;
	_fightField = { 4,3,8,7 };
	_menuRect = { position.x, position.y, width, 0.5f };
	_hud = { 0.5,0.5,4,2 };
	_closable = closable;
	monster_death = false;
	hero_death = false;
	
	ok_controls = false;
	_items.resize(_rows, std::vector<Battle_MenuItem*>(_cols, nullptr));
	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, Color(0, 0, 0, 0));
	_menuBackground->setBorderColor({ 255, 255, 255, 255 });
	//hud layer
	_hudBackground= new RenderableObject(this, _hud, Color(0, 0, 0, 0));
	_hudBackground->setBorderColor({ 255, 255, 255, 255 });
	//battle field background
	_fieldBackground = new RenderableObject(this, _fightField, Color(0, 0, 0, 0));
	_fieldBackground->setBorderColor({ 255, 255, 255, 255 });
	// default: modal menu (blocks all lower scenes)
	_blocking = true;
	
}

Battle_Menu::Battle_Menu(int rows, int cols, Battle_Menu* parent)
	: Battle_Menu(cols, rows, { parent->menuRect().right(),parent->menuRect().top()+0.5f }, parent->menuRect().size.x, parent)
{
}

Battle_MenuItem* Battle_Menu::addItem(int col, int row, const std::string& text, std::function<void()> task)
{
	Battle_MenuItem* item = new Battle_MenuItem(row, col, this, text, task);
	if (row - 1 >= 0 && row - 1 < _items.size() && col - 1 >= 0 && col - 1 < _items[0].size())
		_items[row - 1][col - 1] = item;

	if (_items.size() == 1 && _items[0].size() == 1)
		item->setSelected(true);

	_menuRect.size.y = 0.5f + (_items.size()) * 0.8f + 0.3f;
	_menuRect.size.x = 0.5f + this->menuRect().size.x / _cols * _items[0].size()-0.205f;
	_menuBackground->setRect(_menuRect);

	return item;
}

void Battle_Menu::event(SDL_Event& evt)
{
	UIScene::event(evt);
	if(ok_controls)
		if (evt.type == SDL_KEYDOWN)
		{
		
			if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_rowSelected = (_rowSelected + 1) % int(_items.size());
				_items[_rowSelected][_colSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_rowSelected = (_rowSelected - 1) < 0 ? int(_items.size()) - 1 : _rowSelected - 1;
				_items[_rowSelected][_colSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_colSelected = (_colSelected + 1) % int(_items[_rowSelected].size());
				_items[_rowSelected][_colSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				Audio::instance()->playSound("32 Dragon Quest 1 - Menu Button");
				_items[_rowSelected][_colSelected]->setSelected(false);
				_colSelected = (_colSelected - 1) < 0 ? int(_items[_rowSelected].size()) - 1 : _colSelected - 1;
				_items[_rowSelected][_colSelected]->setSelected(true);
			}
			else if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				_items[_rowSelected][_colSelected]->run();
			}
			else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE || evt.key.keysym.scancode == SDL_SCANCODE_LEFT))
			{
				Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
				Game::instance()->popSceneLater();
				Audio::instance()->resumeMusic();
			}
		}
}
void Battle_Menu::update(float timeToSimulate)
{
	UIScene::update(timeToSimulate);
	if (popup_counter <= 255) {
		decreaseA(popup_counter);
		popup_counter++;
	}
	if (popup_counter == 255) {
		ok_controls = true;
	}
	if (monster_death || hero_death) {
		Audio::instance()->pauseMusic();
		if (i > 0) {
			ok_controls = false;
			i--;
			decreaseA(i);
		}
		if (i==0) {
			if (monster_death) {
				Game::instance()->popSceneLater();
				Game::instance()->popSceneLater();
				Audio::instance()->resumeMusic();
			}
			else {
				Game::instance()->popSceneLater();
				
			}
		}
	}
}
Battle_Menu* Battle_Menu::BattleMenu(const std::string monster_name,Hero* hero,std::string map) {
	Battle_Menu* menu = new Battle_Menu(1, 4, { 0.5, 10.5 }, 4, 0, true);
	Monster* monster = new Monster(menu, { 0,0 }, monster_name);
	
	
	
	//Different backgrounds
	if (map == "overworld")
		menu->_fieldBackground->setSprite(SpriteFactory::instance()->get("slime_background"));

	else if (map == "level_1")
		menu->_fieldBackground->setSprite(SpriteFactory::instance()->get("dungeon_background"));
	else if (map == "dragonlord_castle_s")
		menu->_fieldBackground->setSprite(SpriteFactory::instance()->get("rock_background"));
	else if(map=="level_8")
		menu->_fieldBackground->setSprite(SpriteFactory::instance()->get("final_background"));
	
	new RenderableObject(menu, RectF(0.5, 1.1, 4, 0.05), Color(255, 255, 255, 255));
	//main fight menu
	menu->addItem(1, 1, "Attack", [monster, menu,hero,map](){
		std::vector<std::string> dialogue = { "Bla bal" };
		Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
		menu->battle(hero, monster);

		
			if (menu->getMonster_Death()) {
				Audio::instance()->pauseMusic();
				Audio::instance()->playSound("25 Dragon Quest 1 - Victory");
				monster->setSprite(nullptr);
				if (map == "overworld")
					Audio::instance()->playMusic("05 Dragon Quest 1 - Kingdom of Alefgard");
				if (map == "level_1")
					Audio::instance()->playMusic("Dungeon_1");
				if (map == "dragonlord_castle_s")
					Audio::instance()->playMusic("Dungeon_6");
				if (map == "level_8")
					Audio::instance()->playMusic("Dungeon_8");
			}
		});
	menu->addItem(1, 2, "Spell", [menu,hero,monster]()
		{
			int i = 1;
			if (hero->getSpells().size() > 0) {
				Pause_Menu* nestedmenu = new Pause_Menu(1, hero->getBattleSpells() + 1, { 6, 10.5 }, 5, 0, true);
				for (auto spell : hero->getSpells()) {
					if (spell.second->getFight()) {
						nestedmenu->addItem(1, i, spell.second->getName(), [menu, hero, monster, spell]() {

							if (spell.second->getCost() > hero->getMp())
								Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
							else
								menu->Spellbattle(hero, monster, spell.second);
							if (menu->getMonster_Death()) {
								Audio::instance()->playSound("25 Dragon Quest 1 - Victory");
								monster->setSprite(nullptr);
							}
							});
						i++;
					}
				}
				nestedmenu->addItem(1, hero->getBattleSpells() + 1, "Back", []() {
					Game::instance()->popSceneLater();
					});
				Game::instance()->pushScene(nestedmenu);
			}
			else {
				std::vector<std::string> dialogue = { "You have no spells!" };
				Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
			}
		});
	menu->addItem(1, 3, "Flee", [monster,map]() {
		if (monster->getName() == "Dragonlord" || monster->getName() == "True dragonlord" || monster->getName() == "Dark Wizard") {
			std::vector<std::string> dialogue = { "You can t escape!" };
			Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
		}
		else {
			Audio::instance()->haltMusic();
			Game::instance()->popSceneLater();
			Game::instance()->popSceneLater();
			if (map == "overworld")
				Audio::instance()->playMusic("05 Dragon Quest 1 - Kingdom of Alefgard");
			if(map=="level_1")
				Audio::instance()->playMusic("Dungeon_1");
			if (map == "dragonlord_castle_s")
				Audio::instance()->playMusic("Dungeon_6");
			if (map == "level_8")
				Audio::instance()->playMusic("Dungeon_8");
		}
		});
	menu->addItem(1, 4, "Item", [menu,hero,monster]() {
		int i = 1;
		if (hero->getItems().size() > 0) {
			Pause_Menu* nestedmenu = new Pause_Menu(1, hero->getBattleItems() + 1, { 6, 10.5 }, 5, 0, true);
			for (auto item : hero->getItems()) {
				if (item.second->getFight()) {
					nestedmenu->addItem(1, i, item.second->getName(), [menu, hero, monster, item]() {
						menu->Itembattle(hero, monster, item.second);
						hero->removeItem(item.first);
						if (menu->getMonster_Death()) {
							Audio::instance()->playSound("25 Dragon Quest 1 - Victory");
							monster->setSprite(nullptr);
						}
						});
					i++;
				}
			}
			nestedmenu->addItem(1, hero->getBattleItems() + 1, "Back", []() {
				Game::instance()->popSceneLater();
				});
			Game::instance()->pushScene(nestedmenu);
		}
		else {
			std::vector<std::string> dialogue = { "You have no items!" };
			Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
		}
		});
	if (monster_name == "Dragonlord" || monster_name == "True dragonlord")
		Audio::instance()->playMusic("15 Dragon Quest 1 - The Dragon Lord");
	else
		Audio::instance()->playMusic("14 Dragon Quest 1 - A Monster Draws Near");
	//Audio::instance()->playSound("33 Dragon Quest 1 - Confirmation");
	//Audio::instance()->pauseMusic();
	return menu;
}

void Battle_Menu::battle(Hero* hero, Monster* monster) {
	Attack* picked_attack = monster->pick_attack();
	if (hero->getHp() >=picked_attack->getDamage()) {
		if (hero->getRage()) {
			if (monster->getHp() <= hero->getWeapon()->getDamage()+1) {
				monster_death = true;
				hero->addCoins(monster->getMoney());
			}
			else
				monster->hit(hero->getWeapon()->getDamage()+1);
		}
		else {
			if (monster->getHp() <= hero->getWeapon()->getDamage()) {
				monster_death = true;
				hero->addCoins(monster->getMoney());
			}
			else
				monster->hit(hero->getWeapon()->getDamage());
		}
	}
	
	if (!monster_death) {
		if (hero->getHp() <= picked_attack->getDamage()) {
			hero_death = true;
			hero->turnDeath();
		}
		else 
			hero->damage_hp(picked_attack->getDamage());
	}
	Dialogue_Menu* monster_death_menu = new Dialogue_Menu({ 1.5,10 }, 13, monster, monster_death, hero_death, picked_attack);
	Game::instance()->pushScene(monster_death_menu);

}
void Battle_Menu::Spellbattle(Hero* hero, Monster* monster, Spell* spell) {
	Attack* picked_attack = monster->pick_attack();
	spell->task();

	if (!monster_death) {
		if (hero->getHp() <= picked_attack->getDamage()) {
			hero_death = true;
			hero->turnDeath();
		}
		else
			hero->damage_hp(picked_attack->getDamage());
	}
	Dialogue_Menu* monster_death_menu = new Dialogue_Menu({ 1.5,10 }, 13, monster, monster_death, hero_death, picked_attack,spell);
	Game::instance()->pushScene(monster_death_menu);

}
void Battle_Menu::Itembattle(Hero* hero, Monster* monster, Item* item) {
	Attack* picked_attack = monster->pick_attack();
	item->task();

	if (!monster_death) {
		if (hero->getHp() <= picked_attack->getDamage()) {
			hero_death = true;
			hero->turnDeath();
		}
		else
			hero->damage_hp(picked_attack->getDamage());
	}
	Dialogue_Menu* monster_death_menu = new Dialogue_Menu({ 1.5,10 }, 13, monster, monster_death, hero_death, picked_attack, item);
	Game::instance()->pushScene(monster_death_menu);
}
void Battle_Menu::increaseA(int n) {
	_menuBackground->setColor(Color(0, 0, 0, n/2));
	_hudBackground->setColor(Color(0, 0, 0, n/2));
	_fieldBackground->setColor(Color(0, 0, 0, n/2));
}
void Battle_Menu::decreaseA(int n) {
	_menuBackground->setColor(Color(0, 0, 0, n));
	_hudBackground->setColor(Color(0, 0, 0, n));
	_fieldBackground->setColor(Color(0, 0, 0, n));
}
