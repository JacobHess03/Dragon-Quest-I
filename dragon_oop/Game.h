// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "geometryUtils.h"
#include <vector>
#include <map>




namespace agp
{
	class Game;
	class Scene;
	class Window;
	class HUD;
	class GameScene;
}

// Game (singleton)
// - implements game loop
// - contains the scenes stack
// - receives and dispatches events throughout scene stack
// - singleton access
class agp::Game
{ 
	private:

		// attributes
		Window* _window;
		std::vector<Scene*> _scenes;		// scenes stack
		int _scenesToPop;					// for popSceneLater
		bool _running;
		bool _reset;
		GameScene* actualGameScene;
		std::map<const std::string,GameScene*> maps;
		

		// helper functions
		void init();
		void destroy();
		void processEvents();
		//void update(float dt);	// directly implemented in the game loop
		//void render();			// directly implemented in the game loop

		// constructor inaccesible due to singleton
		Game();

	public: 
		
		// singleton
		static Game* instance();

		// getters
		Window* window() { return _window; }
		float aspectRatio() { return 1.216f; }
		GameScene* getActualGS() { return actualGameScene; }

		// scene stacks
		void pushScene(Scene* scene);
		void popScene();
		void popSceneLater() { _scenesToPop++; };
		void changeMap();

		// event dispatcher
		void dispatchEvent(SDL_Event& evt);

		// runs the game loop until the game is over
		void run();

		// game change states
		void quit() { _running = false; }		
		void reset() { _reset = true; }
		void gameover();
};