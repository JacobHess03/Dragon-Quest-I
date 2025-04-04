// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <algorithm>
#include "Game.h"
#include "Window.h"
#include "GameScene.h"
#include "View.h"
#include "Object.h"
#include "timeUtils.h"
#include "stringUtils.h"
#include "SpriteFactory.h"
#include "LevelLoader.h"
#include "HUD.h"
#include "Menu.h"
#include "Audio.h"

using namespace agp;

Game* Game::instance()
{
	static Game uniqueInstance;
	return &uniqueInstance;
}

Game::Game()
{
	_scenesToPop = 0;
	_running = false;
	_reset = false;
	_window = new Window("Dragon Quest I", int(aspectRatio() * 600), 600);
	actualGameScene = nullptr;
}

void Game::init()
{
	maps["kings_room"] = LevelLoader::instance()->load("kings_room");
	maps["radatome_castle"] = LevelLoader::instance()->load("radatome_castle");
	maps["overworld"] = LevelLoader::instance()->load("overworld");
	maps["level_1"] = LevelLoader::instance()->load("level_1");
	maps["level_6"] = LevelLoader::instance()->load("dragonlord_castle_s");
	maps["level_8"] = LevelLoader::instance()->load("level_8");
	actualGameScene = maps["kings_room"];
	pushScene(actualGameScene);
	pushScene(Menu::mainMenu());
	
}

void Game::run()
{
	init();
	_running = true;

	FPS fps;
	Timer <float> frameTimer;

	while (_running)
	{
		processEvents();

		float frameTime = frameTimer.restart();
		for (auto& layer : _scenes)
			layer->update(frameTime);

		_window->render(_scenes);

		changeMap();
	}

	destroy();
}

void Game::destroy()
{
	for (auto scene : _scenes)
		delete scene;

	if(_window)
		delete _window;

	SDL_Quit();
}

void Game::processEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
		dispatchEvent(evt);

	// if there are scenes to be deleted, better to do this after event dispatching
	for (; _scenesToPop > 0; _scenesToPop--)
		popScene();
	// same for reset
	if (_reset)
	{
		_reset = false;
		for (auto scene : _scenes)
			delete scene;
		_scenes.clear();
		init();
	}
}

void Game::dispatchEvent(SDL_Event& evt)
{
	// window events are dispatched to all scenes for their views adjustments
	if (evt.type == SDL_WINDOWEVENT)
		for (auto& scene : _scenes)
			scene->event(evt);

	// all other events are dispatched from top to down through the scene stack
	// if a blocking layer is encountered, event propagation stops
	else if (_scenes.size())
	{
		for (int i = int(_scenes.size()) - 1; i >= 0; i--)
		{
			_scenes[i]->event(evt);
			if (_scenes[i]->blocking())
				break;
		}
	}
}

void Game::pushScene(Scene* scene)
{
	if(scene->blocking() && _scenes.size())
		for(auto & scene : _scenes)
			scene->setActive(false);

	_scenes.push_back(scene);
}

void Game::popScene()
{
	if (_scenes.size())
	{
		// last scene is blocking lower scenes
		if (_scenes.back()->blocking())
		{
			// reactivate lower scenes down to first blocking scene
			for (int i = int(_scenes.size()) - 2; i >= 0; i--)
			{
				_scenes[i]->setActive(true);
				if (_scenes[i]->blocking())
					break;
			}
		}

		delete _scenes.back();
		_scenes.pop_back();
	}
}

void Game::gameover()
{
	PlayerStats data = actualGameScene->getHero()->saveData();
	maps["level_1"] = LevelLoader::instance()->load("level_1");
	maps["level_8"] = LevelLoader::instance()->load("level_8");
	actualGameScene->setActive(true);
	actualGameScene = maps["radatome_castle"];
	_scenes[0] = actualGameScene;
	actualGameScene->getHero()->loadData(data);
	actualGameScene->getHero()->teleport({ 183,420 });
	actualGameScene->getHero()->restore();
}
void Game::changeMap() {
	if (actualGameScene->stateTrigger()) {
		//to castle
		if (actualGameScene->GetCurrent() == "kings_room" && actualGameScene->GetNew() == "radatome_castle") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["radatome_castle"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 180,113 });
			Audio::instance()->playMusic("04 Dragon Quest 1 - Peaceful Village");
		}
		//back kings room
		else if (actualGameScene->GetCurrent() == "radatome_castle" && actualGameScene->GetNew() == "kings_room") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["kings_room"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 130,260 });
			Audio::instance()->playMusic("02 Dragon Quest 1 - Tantegel Castle");
			

		}
		//to owerworld
		else if (actualGameScene->GetCurrent() == "radatome_castle" && actualGameScene->GetNew() == "overworld") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["overworld"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 316,350 });
			Audio::instance()->playMusic("05 Dragon Quest 1 - Kingdom of Alefgard");


		}
		//back castle
		else if (actualGameScene->GetCurrent() == "overworld" && actualGameScene->GetNew() == "radatome_castle") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["radatome_castle"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 183,420 });
			Audio::instance()->playMusic("04 Dragon Quest 1 - Peaceful Village");
		}
		//to level_1
		else if (actualGameScene->GetCurrent() == "overworld" && actualGameScene->GetNew() == "level_1") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["level_1"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 200,380 });
			Audio::instance()->playMusic("Dungeon_1");
		}
		//back overworld
		else if (actualGameScene->GetCurrent() == "level_1" && actualGameScene->GetNew() == "overworld") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["overworld"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 191, 120 });
			Audio::instance()->playMusic("04 Dragon Quest 1 - Peaceful Village");
		}
		//to level_6
		else if (actualGameScene->GetCurrent() == "level_1" && actualGameScene->GetNew() == "dragonlord_castle_s") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["level_6"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 1122, 938 });
			Audio::instance()->playMusic("Dungeon_6");

		}
		//back level_1
		else if (actualGameScene->GetCurrent() == "dragonlord_castle_s" && actualGameScene->GetNew() == "level_1") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["level_1"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 80, 304 });
			Audio::instance()->playMusic("Dungeon_1");


		}
		//to final level
		else if (actualGameScene->GetCurrent() == "dragonlord_castle_s" && actualGameScene->GetNew() == "level_8") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["level_8"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 176,470 });
			Audio::instance()->playMusic("Dungeon_8");
		}
		//back level_6
		else if (actualGameScene->GetCurrent() == "level_8" && actualGameScene->GetNew() == "dragonlord_castle_s") {
			Audio::instance()->pauseMusic();
			PlayerStats data = actualGameScene->getHero()->saveData();
			actualGameScene->resetTransitionStart();
			actualGameScene = maps["level_6"];
			_scenes[0] = actualGameScene;
			actualGameScene->switchTrigger();
			actualGameScene->getHero()->loadData(data);
			actualGameScene->getHero()->teleport({ 1187,1130 });
			Audio::instance()->playMusic("Dungeon_6");
		}
	}
}