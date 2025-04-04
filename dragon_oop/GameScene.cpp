// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include <iostream>
#include "GameScene.h"
#include "CollidableObject.h"
#include "RenderableObject.h"
#include "View.h"
#include "SpriteFactory.h"
#include "Game.h"
#include "Menu.h"
#include "Dialogue_Menu.h"
#include "Pause_Menu.h"
#include "Battle_Menu.h"
#include "Hero.h"
#include "Audio.h"
#include "LevelLoader.h"
#include <random>


using namespace agp;

GameScene::GameScene(const RectF& r, float dt)
	: Scene(r)
	
{
	currentMap = { "" };
	newMap = { "" };
	activeTrigger = false;
	activeScheduler = false;
	swap = {};
	_dt = dt;
	_timeToSimulate = 0;
	_cameraZoomVel = 0.1f;
	ok_controls = false;
	transition_off = true;
	transition_on = false;
	_left_pressed = false;
	_right_pressed = false;
	_down_pressed = false; 
	_up_pressed = false; 
	transition = new RenderableObject(this, RectF(-100, -100, 1000, 1000), Color(0, 0, 0, 255));
	transition->setLayer(3);
	_hero = nullptr;
	characters = {};
	sellers = {};
	chests = {};
	doors = {};
	monsters = {};
	checkSchedule = nullptr;
	stophero = true;
	darkness = new RenderableObject(this, RectF(-100, -100, 1000, 1000), Color(0, 0, 0, 245));
	darkness->setVisible(false);
	darkness->setLayer(3);
	darkness_on = true;
	_boss = {};

		
	

	// setup view 
	_view = new View(this, _rect);
	_view->setFixedAspectRatio(1.216f);
	_view->setRect(RectF(0, 0, 255, 175));
}

void GameScene::update(float timeToSimulate)
{
	Scene::update(timeToSimulate);

	if (!_active)
		return;

	
	// controls
	if (ok_controls) {
		if (_right_pressed && !_left_pressed && !_up_pressed && !_down_pressed)
			_hero->moveX(Direction::RIGHT);
		else if (_left_pressed && !_right_pressed && !_up_pressed && !_down_pressed)
			_hero->moveX(Direction::LEFT);
		else
			_hero->moveX(Direction::NONE);

		if (_up_pressed && !_down_pressed)
			_hero->moveY(Direction::UP);
		else if (_down_pressed && !_up_pressed)
			_hero->moveY(Direction::DOWN);
		else
			_hero->moveY(Direction::NONE);
	}


	// physics
	_timeToSimulate += timeToSimulate;
	while (_timeToSimulate >= _dt)
	{
		for (auto& layer : _sortedObjects)
			for (auto& obj : layer.second)
				obj->update(_dt);

		_timeToSimulate -= _dt;
	}
	//camera movement
	_view->setX(_hero->rect().pos.x-120);
	_view->setY(_hero->rect().pos.y-60);
	//fight
	if(monsters.size() && _hero->getWalking() && !transition_off && !transition_on)
		checkBattle();
	if(checkSchedule!=nullptr)
		checkSchedule->update(timeToSimulate);
	//transition
	if (activeTrigger)
		ok_controls = false;
	if (transition_off) {
		if (off > 0) {
			if (off == 255) 
				Audio::instance()->playSound("30 Dragon Quest 1 - Stairs Down");
			transitionMod(off);
			off--;
		}
		if (off == 0) {
			transition_off = false;
			ok_controls = true;
		}
	}
	else
		ok_controls = true;
	if (transition_on) {
		if (on < 255) {
			if(on==0)
				Audio::instance()->playSound("29 Dragon Quest 1 - Stairs Up");
			transitionMod(on);
			on++;
		}
		else {
			transition_on = false;
			ok_controls = false;
			switchTrigger();
		}
	}
	if (stophero)
		_hero->stop();
	//gameover
	checkDeath();
	//dark levels
	darkResolve();
	if (_hero->getRage())
		_hero->turnRage(false);
	else 
		_hero->turnRage(false);
	//boss
	if (boss && lost==0) {
		_boss->setDefeat(true);
		if (_boss->getName() == "Dark Wizard" && midboss==0) {
			_boss->setRect(RectF(0, 0, 0, 0));
			std::vector<std::string> dialogue = { "You found a special key!","It may help you unlock the","castle's doors!" };
			Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
			midboss++;
			_hero->addKey(1);
		}
	}
	if(lost==0)
	checkVictory();
}

void GameScene::event(SDL_Event& evt)
{
	Scene::event(evt);
	if (ok_controls) {
		if (evt.type == SDL_KEYDOWN)
			stophero = false;
		if (evt.type == SDL_KEYDOWN && (evt.key.keysym.scancode == SDL_SCANCODE_Z || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			Game::instance()->pushScene(Pause_Menu::pauseMenu(_hero));
		else if (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_C && !evt.key.repeat)
		{
			ObjectsList allObjects = objects();
			for (auto& obj : allObjects)
				if (obj->to<CollidableObject*>())
					obj->to<CollidableObject*>()->toggleCollider();
		}
		else if (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_A) {
			Npc* npc = checkDialogue();
			if (npc != nullptr) {
				if (npc->getFight()) {
					_boss = npc;
					Game::instance()->pushScene(Battle_Menu::BattleMenu(npc->getName(), _hero, GetCurrent()));
					HUD* hud = new HUD({ 0.5,0.5,4,3 }, _hero);
					Game::instance()->pushScene(hud);
					Game::instance()->pushScene(Dialogue_Menu::menu(npc));
					boss = true;
					std::cout << npc->getName();
					if(npc->getName()=="True dragonlord")
						victory=true;
				}
				else
					Game::instance()->pushScene(Dialogue_Menu::menu(npc));
			}

			Seller* seller = checkSeller();
			if (seller != nullptr)
			{
				Game::instance()->pushScene(Pause_Menu::pauseMenuSeller(_hero, seller));
				std::vector<std::string> dialogue = { "Welcome to my shop" };
				Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));

			}
		}
		else if (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_S) {
			Door* door = checkDoor();
			Chest* chest = checkChest();
			if (door != nullptr) {
				if (_hero->getKeys() != 0) {
					door->switchOpen();
					_hero->addKey(-1);
					Audio::instance()->pauseMusic();
					Audio::instance()->playSound("45 Dragon Quest 1 - Open Door");
					Audio::instance()->resumeMusic();
				}
				else {
					if (currentMap == "level_8") {
						std::vector<std::string> dialogue = { "This is the room where the","dragonlord keeps the king s ","treasure!"};
						Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
						Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
					}
					else if (currentMap == "radatome_castle") {
						std::vector<std::string> dialogue = { "This is the room where the","king keeps the treasure that","the dragon lord didn t steal"};
						Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
						Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
					}
					else {
						std::vector<std::string> dialogue = { "You don't have enough keys!" };
						Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
						Game::instance()->pushScene(Dialogue_Menu::menu(dialogue));
					}
				}
			}
				
			if (chest != nullptr) {
				chest->switchOpen();
				if (chest->getActive()) {
					chest->getDrop()->task();
				}
				else
					_hero->addItem(chest->getDrop());
				Game::instance()->pushScene(Dialogue_Menu::menu(chest));
				Audio::instance()->playSound("45 Dragon Quest 1 - Open Door");
			}
		}
		// update control flags
		const Uint8* state = SDL_GetKeyboardState(0);
		_right_pressed = state[SDL_SCANCODE_RIGHT];
		_left_pressed = state[SDL_SCANCODE_LEFT];
		_up_pressed = state[SDL_SCANCODE_UP];
		_down_pressed = state[SDL_SCANCODE_DOWN];
	}
}

void GameScene::clearTrigger() {
	for (auto& obj : swap) {
		delete obj;
	}
}
void GameScene::addTrigger(const RectF& rect, const std::string name) {
	swap.push_back(new Trigger(this, rect, _hero, [this,name]() {
		this->setNewMap(name);
		transition_on = true;
		//this->switchTrigger();
		}));
}
void GameScene::addTeleport(const RectF& rect, PointF spawn) {
	swap.push_back(new Trigger(this, rect, _hero, [this,spawn]() {
		this->_hero->teleport(spawn);
		}));
}
void GameScene::addNpc(const PointF pos, const std::string name) {
	characters.push_back(new Npc(this, pos, name));
}
void GameScene::addChest(const PointF pos, Item* item,bool on ) {
	chests.push_back(new Chest(this, pos, item,on));
}
Npc* GameScene::checkDialogue() {
	for (auto& npc : characters) 
		if (npc->hit(_hero)) 
			return npc;
	return nullptr;
}
Chest* GameScene::checkChest() {
	for (auto& chest : chests)
		if (chest->hit(_hero))
			return chest;
	return nullptr;
}
void GameScene::switchTrigger() {
	if (activeTrigger)
		activeTrigger = false;
	else
		activeTrigger = true;
}
void GameScene::checkBattle() {
	std::string name= pick_Monster();
	if (!activeScheduler) {
		activeScheduler = true;
		checkSchedule=new Scheduler(1,[this,name]() {
			int n = 1;
			if (n==rand() % 10) {
				Game::instance()->pushScene(Battle_Menu::BattleMenu(name, _hero,GetCurrent()));
				HUD* hud = new HUD({ 0.5,0.5,4,3 }, _hero);
				Game::instance()->pushScene(hud);
			}
			activeScheduler = false;
			});
	}
}
const std::string GameScene::pick_Monster() {
	if (monsters.size()>0)
		return monsters[rand() % monsters.size()];
	else
		return "";
}
void GameScene::addMonster(const std::string name) {
	monsters.push_back(name);
}
void GameScene::addDoor(const PointF pos, bool on, const std::string name, PointF dim) {
	doors.push_back(new Door(this, pos, on, name, dim));
}

Door* GameScene::checkDoor() {
	for (auto& door : doors)
		if (door->hit(_hero))
			return door;
	return nullptr;
}
void GameScene::transitionMod(int n) {
	transition->setColor(Color(0, 0, 0, n ));
}
void GameScene::resetTransitionStart() {
	transition_off = true;
	transition_on = false;
	ok_controls = false;
	off = 255;
	on = 0;
	transition->setColor(Color(0, 0, 0, 255));
	stophero = true;
}
void GameScene::checkDeath() {
	if (_hero->getDeath()) {
		Game::instance()->pushScene(Pause_Menu::deathMenu());
		std::vector<std::string> dialogue = { "Stay determined hero!","What do you want to do?"};
		Game::instance()->pushScene(Dialogue_Menu::menu({3,10}, dialogue));
		_hero->turnDeath();
		lost++;
	}
}
void GameScene::darkResolve() {
	if (currentMap == "level_1" && darkness_on) {
		darkness->setVisible(true);
	}
	if (_hero->getDark()) {
		darkness_on = false;
		if (dark > 0) {
			darkness->setColor(Color(0, 0, 0, dark));
			dark--;
		}
		else {
			darkness->setVisible(false);
			
		}
	}
}
void GameScene::addSeller(const PointF pos, const std::string name, bool on, Hero* hero) {
	sellers.push_back(new Seller(this, pos, name, on, hero));
}

Seller* GameScene::checkSeller() {
	for (auto& seller : sellers)
		if (seller->hit(_hero))
			return seller;
	return nullptr;
}
void GameScene::checkVictory() {
	if (victory) {
		Game::instance()->pushScene(Pause_Menu::victory_menu());
		printf("victory");
		std::vector<std::string> dialogue = { "Congratulations!","You saved the princess and the kingdom!","You also retrieved the king s  treasure!","You ve been rewarded and now   you are","the kingdom keeper!","Thank you for playing!" };
		Game::instance()->pushScene(Dialogue_Menu::menu({ 1.5,10 }, dialogue));
	}
}