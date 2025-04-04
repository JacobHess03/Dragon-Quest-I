// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <iostream>
#include "Scene.h"
#include "Npc.h"
#include "Chest.h"
#include "Scheduler.h"
#include "Monster.h"
#include "Door.h"
#include "Seller.h"


namespace agp
{
	class GameScene;
	class Hero;
	class Trigger;
}

// GameScene (or World) class
// - specialized update(dt) to semifixed timestep
// - may provide more efficient access to game objects (e.g. quadtree)
// - can/should be customized for the specific game to implement (here, supermariobros-like)
class agp::GameScene : public Scene
{
private:

	std::string currentMap;		//to check the current map
	std::string newMap;
	bool activeTrigger;			//flag to activate the trigger
	std::vector<Trigger*>swap;
	std::vector<Npc*> characters;
	std::vector<Chest*> chests;
	std::vector<Door*> doors;
	std::vector<std::string> monsters;
	float _dt;					// time integration step
	float _timeToSimulate;		// time integration extent
	Hero* _hero;
	bool ok_controls;
	//transition
	RenderableObject* transition;
	bool transition_on;
	bool transition_off;
	int off = 255;
	int on = 0;
	bool stophero;
	//movement
	bool _right_pressed;
	bool _up_pressed;
	bool _down_pressed;
	bool _left_pressed;
	//battle
	bool activeScheduler;
	Scheduler* checkSchedule;
	//dark level
	RenderableObject* darkness;
	bool darkness_on;
	int dark = 245;
	//seller
	std::vector<Seller*> sellers;
	//boss
	Npc* _boss;
	bool boss=false;
	bool victory=false;
	int midboss = 0;
	int lost = 0;




	float _cameraZoomVel;		// camera zoom velocity (in [0,1] relative scale units)

public:

	GameScene(const RectF& r, float dt);
	virtual ~GameScene() {};

	// overrides scene object selection (+octree, NOT implemented)
	//virtual std::list<Object*> objects(const RectF& cullingRect) override;
	//to set currentMap  in LevelLoader
	void setCurrentMap(const std::string name) { currentMap = name; }
	//to set newMap in specific trigger
	void setNewMap(const std::string name) { newMap = name; }
	Hero* getHero() { return _hero; }
	//to turn on the trigger flag
	void switchTrigger();
	bool stateTrigger() { return activeTrigger; }
	void addTrigger(const RectF& rect, const std::string name);
	void addTeleport(const RectF& rect, PointF spawn);
	void clearTrigger();
	//map change
	const std::string GetCurrent() { return currentMap; }
	const std::string GetNew() { return newMap; }
	// implements game scene update logic (+semifixed timestep)
	virtual void update(float timeToSimulate) override;
	void setPlayer(Hero* hero) { _hero = hero; }
	// extends event handler (+camera translate/zoom, +brick creation/destroy, +pause menu)
	virtual void event(SDL_Event& evt) override;
	//characters
	void addNpc(const PointF pos, const std::string name);
	void addChest(const PointF pos, Item* item, bool on);
	Npc* checkDialogue();
	//chest
	Chest* checkChest();
	//door
	void addDoor(const PointF pos, bool on, const std::string name, PointF dim);
	Door* checkDoor();
	//monsters
	void checkBattle();
	void addMonster(const std::string name);
	const std::string pick_Monster();
	//transition
	void transitionMod(int n);
	void resetTransitionStart();
	//gameover
	void checkDeath();
	//dark level
	void darkResolve();
	//seller
	Seller* checkSeller();
	void addSeller(const PointF pos, const std::string name, bool on, Hero* hero);
	//boss
	void setBoss(Npc* npc) { _boss = npc; }
	void checkVictory();

	
};