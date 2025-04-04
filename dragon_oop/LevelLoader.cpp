// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "LevelLoader.h"
#include "SpriteFactory.h"
#include "RenderableObject.h"
#include "StaticObject.h"
#include "GameScene.h"
#include "Hero.h"
#include "Enemy.h"
#include <iostream>

using namespace agp;

LevelLoader* LevelLoader::instance()
{
	static LevelLoader uniqueInstance;
	return &uniqueInstance;
}

LevelLoader::LevelLoader()
{	
	loaded_levels = { load("kings_room"),load("radatome_castle"),load("overworld"),load("level_1"),load("dragonlord_castle_s"),load("level_8") };
}


GameScene* LevelLoader::load(const std::string& name) {
	SpriteFactory* spriteLoader = SpriteFactory::instance();
	if (name == "kings_room") {
		GameScene* world = new GameScene(RectF(0, 0, 240, 320), 1 / 100.0f);
		world->setBackgroundColor(Color(1, 70, 255));
		world->setCurrentMap(name);


		// map
		new RenderableObject(world, RectF(0, 0, 240, 320), spriteLoader->get("kings_room"));
		RenderableObject* _arch = new RenderableObject(world, RectF(103, 223, 33, 9), spriteLoader->get("arch"));
		RenderableObject* _col1 = new RenderableObject(world, RectF(81, 176, 12, 22), spriteLoader->get("colomn"));
		RenderableObject* _col2 = new RenderableObject(world, RectF(145, 176, 12, 22), spriteLoader->get("colomn"));
		_arch->setLayer(2);
		_col1->setLayer(2);
		_col2->setLayer(2);

		//collider
		new StaticObject(world, RectF(0, 0, 16, 320), nullptr);//mura esterne
		new StaticObject(world, RectF(0, 288, 240, 32), nullptr);
		new StaticObject(world, RectF(224, 0, 16, 320), nullptr);
		new StaticObject(world, RectF(0, 0, 240, 22), nullptr);
		new StaticObject(world, RectF(0, 224, 105, 22), nullptr);//mura interne
		new StaticObject(world, RectF(136, 224, 105, 22), nullptr);
		new StaticObject(world, RectF(66, 49, 45, 9), nullptr);//testiera trono
		new StaticObject(world, RectF(130, 49, 45, 9), nullptr);
		new StaticObject(world, RectF(81, 198, 14, 5), nullptr);//base colonne
		new StaticObject(world, RectF(145, 198, 14, 5), nullptr);
		new StaticObject(world, RectF(66, 58, 9, 21), nullptr);//braccioli trono
		new StaticObject(world, RectF(102, 58, 9, 21), nullptr);
		new StaticObject(world, RectF(130, 58, 9, 21), nullptr);
		new StaticObject(world, RectF(166, 58, 9, 21), nullptr);
		//characters
		world->addNpc(PointF(80, 58), "king");
		world->addNpc(PointF(144, 135), "counselor_L");
		world->addNpc(PointF(95, 189), "guard_1");
		world->addNpc(PointF(127, 189), "guard_2");
		
		// hero
		Hero* _hero = new Hero(world, PointF(112, 160));
		world->setPlayer(_hero);
		
		_hero->setLayer(1);
		//trigger
		world->addTrigger(RectF(116, 276, 4, 4),"radatome_castle");
		//chests
		
		world->addChest(PointF(95, 99), new Item("1 Key",2, [_hero]() {
			_hero->addKey(1);
			},false), true);
		world->addChest(PointF(111, 99), new Item("200 Coins", 2, [_hero]() {
			_hero->addCoins(200);
			}, false), true);
		world->addChest(PointF(127, 99), new Item("Torch", 2, [_hero]() {
			_hero->addItem("Torch");
			}, false), false);
		//door
		world->addDoor(PointF(103, 232), true, "radatomecastle_door", PointF(35, 24));
		return world;
	}
	else if (name == "overworld")
	{
		GameScene* world = new GameScene(RectF(0, 0, 600, 505), 1 / 100.0f);
		world->setBackgroundColor(Color(1, 70, 255));
		world->setCurrentMap(name);


		//map
		new RenderableObject(world, RectF(0, 0, 600, 535), spriteLoader->get("overworld"));


		//collider
		new StaticObject(world, RectF(223, 411, 32, 1), nullptr);
		new StaticObject(world, RectF(254, 411, 1, 16), nullptr);
		new StaticObject(world, RectF(254, 427, 66, 1), nullptr);
		new StaticObject(world, RectF(321, 411, 1, 16), nullptr);
		new StaticObject(world, RectF(321, 411, 32, 1), nullptr);
		new StaticObject(world, RectF(353, 395, 1, 16), nullptr);
		new StaticObject(world, RectF(353, 395, 32, 1), nullptr);
		new StaticObject(world, RectF(385, 379, 1, 16), nullptr);
		new StaticObject(world, RectF(385, 379, 16, 1), nullptr);
		new StaticObject(world, RectF(401, 347, 1, 32), nullptr);
		new StaticObject(world, RectF(401, 347, 1, 32), nullptr);
		new StaticObject(world, RectF(385, 337, 16, 1), nullptr);
		new StaticObject(world, RectF(385, 331, 1, 7), nullptr);
		new StaticObject(world, RectF(385, 331, 16, 1), nullptr);
		new StaticObject(world, RectF(401, 315, 1, 16), nullptr);
		new StaticObject(world, RectF(401, 315, 16, 1), nullptr);
		new StaticObject(world, RectF(417, 283, 1, 32), nullptr);
		new StaticObject(world, RectF(402, 273, 16, 1), nullptr);
		new StaticObject(world, RectF(401, 250, 1, 24), nullptr);
		new StaticObject(world, RectF(401, 250, 16, 1), nullptr);
		new StaticObject(world, RectF(417, 218, 1, 32), nullptr);
		new StaticObject(world, RectF(401, 210, 16, 1), nullptr);
		new StaticObject(world, RectF(401, 202, 1, 8), nullptr);
		new StaticObject(world, RectF(401, 202, 16, 1), nullptr);
		new StaticObject(world, RectF(417, 186, 16, 1), nullptr);
		new StaticObject(world, RectF(433, 154, 1, 32), nullptr);
		new StaticObject(world, RectF(433, 154, 16, 1), nullptr);
		new StaticObject(world, RectF(457, 138, 1, 16), nullptr);
		new StaticObject(world, RectF(353, 130, 96, 1), nullptr);
		new StaticObject(world, RectF(369, 146, 32, 1), nullptr);
		new StaticObject(world, RectF(369, 130, 1, 16), nullptr);
		new StaticObject(world, RectF(401, 130, 1, 16), nullptr);
		new StaticObject(world, RectF(304, 114, 48, 1), nullptr);
		new StaticObject(world, RectF(354, 114, 1, 16), nullptr);
		new StaticObject(world, RectF(304, 114, 1, 80), nullptr);
		new StaticObject(world, RectF(288, 114, 1, 48), nullptr);
		new StaticObject(world, RectF(288, 186, 1, 24), nullptr);
		new StaticObject(world, RectF(288, 100, 16, 1), nullptr);
		new StaticObject(world, RectF(288, 193, 16, 1), nullptr);
		new StaticObject(world, RectF(288, 185, 16, 1), nullptr);
		new StaticObject(world, RectF(272, 84, 16, 1), nullptr);
		new StaticObject(world, RectF(192, 68, 80, 1), nullptr);
		new StaticObject(world, RectF(176, 84, 16, 1), nullptr);
		new StaticObject(world, RectF(192, 68, 1, 17), nullptr);
		new StaticObject(world, RectF(272, 68, 1, 104), nullptr);
		new StaticObject(world, RectF(272, 162, 16, 1), nullptr);
		new StaticObject(world, RectF(272, 154, 16, 1), nullptr);
		new StaticObject(world, RectF(209, 146, 63, 1), nullptr);
		new StaticObject(world, RectF(209, 138, 63, 1), nullptr);
		new StaticObject(world, RectF(177, 146, 16, 1), nullptr);
		new StaticObject(world, RectF(177, 138, 16, 1), nullptr);
		new StaticObject(world, RectF(177, 90, 1, 48), nullptr);
		new StaticObject(world, RectF(161, 98, 16, 1), nullptr);
		new StaticObject(world, RectF(145, 116, 16, 1), nullptr);
		new StaticObject(world, RectF(161, 178, 16, 1), nullptr);
		new StaticObject(world, RectF(145, 162, 16, 1), nullptr);
		new StaticObject(world, RectF(161, 170, 16, 1), nullptr);
		new StaticObject(world, RectF(145, 154, 16, 1), nullptr);
		new StaticObject(world, RectF(161, 154, 1, 16), nullptr);
		new StaticObject(world, RectF(145, 122, 1, 32), nullptr);
		new StaticObject(world, RectF(177, 186, 32, 1), nullptr);
		new StaticObject(world, RectF(177, 194, 32, 1), nullptr);
		new StaticObject(world, RectF(177, 170, 1, 16), nullptr);
		new StaticObject(world, RectF(208, 170, 1, 16), nullptr);
		new StaticObject(world, RectF(208, 170, 15, 1), nullptr);
		new StaticObject(world, RectF(208, 178, 15, 1), nullptr);
		new StaticObject(world, RectF(240, 170, 32, 1), nullptr);
		new StaticObject(world, RectF(240, 178, 32, 1), nullptr);
		new StaticObject(world, RectF(224, 202, 16, 1), nullptr);
		new StaticObject(world, RectF(224, 210, 16, 1), nullptr);
		new StaticObject(world, RectF(256, 202, 32, 1), nullptr);
		new StaticObject(world, RectF(256, 210, 32, 1), nullptr);
		new StaticObject(world, RectF(160, 218, 64, 1), nullptr);
		new StaticObject(world, RectF(160, 226, 64, 1), nullptr);
		new StaticObject(world, RectF(145, 203, 16, 1), nullptr);
		new StaticObject(world, RectF(145, 211, 16, 1), nullptr);
		new StaticObject(world, RectF(144, 164, 1, 48), nullptr);
		new StaticObject(world, RectF(160, 100, 1, 16), nullptr);
		new StaticObject(world, RectF(223, 395, 1, 16), nullptr);
		new StaticObject(world, RectF(207, 395, 16, 1), nullptr);
		new StaticObject(world, RectF(207, 379, 1, 16), nullptr);
		new StaticObject(world, RectF(191, 379, 16, 1), nullptr);
		new StaticObject(world, RectF(191, 347, 1, 32), nullptr);
		new StaticObject(world, RectF(175, 347, 16, 1), nullptr);
		new StaticObject(world, RectF(175, 331, 1, 16), nullptr);
		new StaticObject(world, RectF(159, 331, 16, 1), nullptr);
		new StaticObject(world, RectF(159, 235, 1, 96), nullptr);
		new StaticObject(world, RectF(159, 307, 16, 1), nullptr);
		new StaticObject(world, RectF(175, 283, 1, 24), nullptr);
		new StaticObject(world, RectF(159, 283, 16, 1), nullptr);
		//AddNpc
		world->addNpc(PointF(430, 135), "knight_L");
		world->addNpc(PointF(175, 120), "knight_R");
		

		// hero
		Hero* _hero = new Hero(world, PointF(312, 342));
		world->setPlayer(_hero);
		//sellers
		world->addSeller(PointF(270, 186), "spellseller_L1", true, _hero);
		world->addSeller(PointF(175, 170), "itemseller_R1", false, _hero);
		//trigger
		world->addTrigger(RectF(316, 332, 8, 8),"radatome_castle");
		world->addTrigger(RectF(221, 112, 8, 8), "level_1");
		//monsters
		world->addMonster("Slime");
		
		return world;
	}
	else if (name == "radatome_castle")
	{
		GameScene* world = new GameScene(RectF(0, 0, 496, 496), 1 / 100.0f);
		world->setBackgroundColor(Color(1, 70, 255));
		world->setCurrentMap(name);
		// terrain radatome_castle
		new RenderableObject(world, RectF(0, 0, 496, 496), spriteLoader->get("radatome_castle"));


		new StaticObject(world, RectF(0, 0, 16, 0), nullptr);
		new StaticObject(world, RectF(18, 0, 111, 8), nullptr);
		new StaticObject(world, RectF(113, 0, 16, 56), nullptr);
		new StaticObject(world, RectF(113, 48, 64, 10), nullptr);//muro laterale in alto a sx simmetrico centrale
		new StaticObject(world, RectF(256, 0, 16, 56), nullptr);

		new StaticObject(world, RectF(257, 97, 128, 8), nullptr); // muro tutto a dx con porta in alto
		new StaticObject(world, RectF(256, 0, 112, 8), nullptr);
		new StaticObject(world, RectF(352, 0, 16, 104), nullptr);




		new StaticObject(world, RectF(208, 48, 64, 10), nullptr);//muro laterale in alto a dx simmetrico centrale
		new StaticObject(world, RectF(113, 81, 158, 8), nullptr); //muro interno orizzontale centrale alto
		new StaticObject(world, RectF(113, 81, 100, 8), nullptr); //muro interno orizzontale centrale alto
		new StaticObject(world, RectF(113, 81, 15, 187), nullptr);//muro interno lungo di sx 
		new StaticObject(world, RectF(257, 81, 15, 187), nullptr); //muro interno lungo di dx
		new StaticObject(world, RectF(257, 258, 80, 10), nullptr);
		new StaticObject(world, RectF(305, 273, 48, 16), nullptr); //vasi stanza a dx centrale
		new StaticObject(world, RectF(241, 305, 15, 32), nullptr); //muretto in linea d'aria vicina al vaso
		new StaticObject(world, RectF(256, 305, 16, 8), nullptr); //blocco di muro in linea d'aria vicina al vaso
		new StaticObject(world, RectF(273, 385, 96, 10), nullptr); //muro orizz vicino tavoletto in basso a dx
		new StaticObject(world, RectF(273, 385, 15, 26), nullptr); //muretti verticali 1,2,3
		new StaticObject(world, RectF(273, 433, 15, 24), nullptr); //muretti verticali 1,2,3
		new StaticObject(world, RectF(321, 385, 15, 62), nullptr); //muretti verticali 1,2,3

		new StaticObject(world, RectF(353, 274, 16, 250), nullptr);  //muro laterale dx che affaccia sul mare




		new StaticObject(world, RectF(127, 0, 128, 0), nullptr);
		new StaticObject(world, RectF(16, 8, 16, 96), nullptr);
		new StaticObject(world, RectF(18, 97, 62, 8), nullptr);
		new StaticObject(world, RectF(0, 97, 16, 158), nullptr);
		new StaticObject(world, RectF(0, 177, 80, 8), nullptr);
		new StaticObject(world, RectF(80, 97, 16, 40), nullptr);
		new StaticObject(world, RectF(80, 160, 16, 98), nullptr); //collider con porta chiusa
		new StaticObject(world, RectF(16, 257, 80, 8), nullptr);
		new StaticObject(world, RectF(16, 257, 16, 208), nullptr); //muro ext sx affaccia sul mare 
		new StaticObject(world, RectF(16, 305, 48, 8), nullptr);
		new StaticObject(world, RectF(97, 305, 47, 8), nullptr);
		new StaticObject(world, RectF(129, 305, 15, 40), nullptr);
		new StaticObject(world, RectF(145, 337, 15, 120), nullptr); //ultimo muro inteno da sx basso
		new StaticObject(world, RectF(225, 337, 15, 120), nullptr); //ultimo muro inteno da dx basso
		new StaticObject(world, RectF(241, 305, 16, 32), nullptr); //ultimo muro inteno da dx basso
		//Piscina centrale
		new StaticObject(world, RectF(162, 250, 62, 8), nullptr);
		new StaticObject(world, RectF(162, 248, 2, 64), nullptr);
		new StaticObject(world, RectF(162, 312, 62, 8), nullptr);
		new StaticObject(world, RectF(222, 248, 2, 64), nullptr);
		//RenderableObject* piscina = new RenderableObject(world, RectF(162, 248, 4, 4), spriteLoader->get("piscina"));

		//piscina->setLayer(1);
		//poltrone di pietra
		new StaticObject(world, RectF(65, 49, 16, 15), nullptr);
		new StaticObject(world, RectF(304, 49, 16, 15), nullptr);
		new StaticObject(world, RectF(64, 353, 16, 15), nullptr);
		new StaticObject(world, RectF(112, 385, 16, 15), nullptr);

		//piscinetta in basso a dx

		new StaticObject(world, RectF(31, 400, 18, 16), nullptr);
		new StaticObject(world, RectF(47, 384, 34, 16), nullptr);
		new StaticObject(world, RectF(81, 400, 16, 34), nullptr);
		new StaticObject(world, RectF(97, 432, 16, 16), nullptr);
		//muretti finali
		new StaticObject(world, RectF(128, 145, 32, 8), nullptr);
		new StaticObject(world, RectF(225, 145, 32, 8), nullptr);
		new StaticObject(world, RectF(159, 417, 17, 8), nullptr);
		new StaticObject(world, RectF(209, 417, 16, 8), nullptr);
		//scale
		//new StaticObject(world, RectF(225, 113, 15, 8), nullptr);


		//tavolini e sedie 
		new StaticObject(world, RectF(49, 129, 16, 15), nullptr);
		new StaticObject(world, RectF(35, 131, 12, 13), nullptr);

		//casse basso sx
		new StaticObject(world, RectF(31, 273, 49, 8), nullptr);

		new StaticObject(world, RectF(225, 337, 95, 8), nullptr);
		new StaticObject(world, RectF(16, 449, 160, 8), nullptr); //muro orrizz basso sx
		new StaticObject(world, RectF(209, 449, 160, 8), nullptr); //muro orrizz basso dx
		new StaticObject(world, RectF(47, 450, 2, 50), nullptr); //collider laghetto in basso a sx

		new StaticObject(world, RectF(47, 496, 312, 2), nullptr); //collider laghetto in basso lungo per delimitare mappa
		new StaticObject(world, RectF(145, 16, 15, 16), nullptr); //alberi in alto 1, 2 ,3
		new StaticObject(world, RectF(177, 16, 30, 16), nullptr); //alberi in alto 1, 2 ,3
		new StaticObject(world, RectF(225, 16, 15, 16), nullptr); //alberi in alto 1, 2 ,3


		//new StaticObject(world, RectF(165, 449, 6, 10), nullptr); //lampada basso sx



		Hero* _hero = new Hero(world, PointF(210, 111));
		world->setPlayer(_hero);
		//trigger 
		world->addTrigger(RectF(225, 113, 15, 8), "kings_room");
		world->addTrigger(RectF(175, 466, 32, 1), "overworld");
		//AddNpc
		
		world->addNpc(PointF(225, 97), "guard_L1");
		world->addNpc(PointF(225, 124), "guard_L2");
		world->addNpc(PointF(275, 155), "towngirl_R");
		world->addNpc(PointF(310, 222), "townboy_D1");
		world->addNpc(PointF(165, 230), "castlegirl_U");
		world->addNpc(PointF(225, 230), "towngirl_L");
		world->addNpc(PointF(145, 32), "towngirl_R");
		world->addNpc(PointF(225, 300), "townboy_D1");
		world->addNpc(PointF(64, 330), "townboy_D2");
		world->addNpc(PointF(85, 365), "knight_U");
		world->addNpc(PointF(300, 315), "guard_R1");
		world->addNpc(PointF(158, 428), "guard_R2");
		world->addNpc(PointF(208, 428), "guard_L3");
		
		//sellers
		world->addSeller(PointF(292, 412), "spellseller_L", true, _hero);
		world->addSeller(PointF(47, 143), "itemseller_R", false, _hero);
		//door
		world->addDoor(PointF(305, 97), true, "radatomecastle_door2", PointF(16, 16));
		world->addDoor(PointF(80, 226), true, "radatomecastle_door2", PointF(16, 16));




		return world;
	}
	else if (name == "dragonlord_castle_s")
	{
		GameScene* world = new GameScene(RectF(890, 890, 350, 510), 1 / 100.0f);
		world->setBackgroundColor(Color(0, 0, 0));
		world->setCurrentMap(name);

		// terrain
		new RenderableObject(world, RectF(890, 890, 350, 510), spriteLoader->get("dragonlord_castle_s"));
		new StaticObject(world, RectF(1084, 890, 32, 117), nullptr);
		new StaticObject(world, RectF(1084, 890, 96, 24), nullptr);
		new StaticObject(world, RectF(1147, 890, 32, 440), nullptr);
		new StaticObject(world, RectF(988, 986, 128, 24), nullptr);
		new StaticObject(world, RectF(988, 986, 32, 254), nullptr);
		new StaticObject(world, RectF(988, 1178, 95, 32), nullptr);
		new StaticObject(world, RectF(1051, 1178, 32, 96), nullptr);
		new StaticObject(world, RectF(1051, 1242, 96, 32), nullptr);
		new StaticObject(world, RectF(986, 1305, 162, 25), nullptr);
		new StaticObject(world, RectF(1083, 1114, 64, 24), nullptr);
		new StaticObject(world, RectF(1052, 1049, 32, 89), nullptr);
		new StaticObject(world, RectF(1052, 1049, 128, 32), nullptr);
		new StaticObject(world, RectF(1115, 1115, 32, 160), nullptr);
		new StaticObject(world, RectF(1149, 1081, 96, 24), nullptr);
		new StaticObject(world, RectF(1211, 1082, 32, 320), nullptr);
		new StaticObject(world, RectF(890, 1369, 352, 32), nullptr);
		new StaticObject(world, RectF(893, 1082, 32, 320), nullptr);
		new StaticObject(world, RectF(893, 1082, 96, 24), nullptr);
		new StaticObject(world, RectF(955, 1082, 32, 248), nullptr);
		//scalette
		//new StaticObject(world, RectF(1132, 922, 16, 16), nullptr);
		//new StaticObject(world, RectF(924, 1114, 16, 16), nullptr);
		new StaticObject(world, RectF(1084, 890, 32, 117), nullptr);
		//new StaticObject(world, RectF(1099, 1225, 16, 16), nullptr);
		//new StaticObject(world, RectF(1195, 1114, 16, 16), nullptr);





		// hero
		Hero* _hero = new Hero(world, PointF(1114, 921));
		world->setPlayer(_hero);
		
		//trigger
		world->addTrigger(RectF(1140, 922, 8, 8), "level_1");
		world->addTeleport(RectF(924, 1114, 14, 16), PointF(1083, 1225));
		world->addTeleport(RectF(1099, 1225, 16, 16), PointF(938, 1114));
		world->addTrigger(RectF(1203, 1114, 8, 8), "level_8");
		//monsters
		world->addMonster("Rat");
		world->addMonster("Wizard");

		return world;
	}
	else if (name == "level_1") {

		GameScene* world = new GameScene(RectF(0, 0, 416, 447), 1 / 100.0f);
		world->setBackgroundColor(Color(1, 70, 255));
		world->setCurrentMap(name);

		// terrain
		new RenderableObject(world, RectF(0, 0, 416, 447), spriteLoader->get("level_1"));

		// collider
		new StaticObject(world, RectF(0, 0, 16, 449), nullptr);
		new StaticObject(world, RectF(0, 0, 416, 24), nullptr);
		new StaticObject(world, RectF(400, 0, 16, 449), nullptr);
		new StaticObject(world, RectF(47, 401, 144, 15), nullptr);
		new StaticObject(world, RectF(16, 369, 16, 16), nullptr);
		new StaticObject(world, RectF(31, 384, 16, 16), nullptr);
		new StaticObject(world, RectF(145, 385, 47, 65), nullptr);
		new StaticObject(world, RectF(225, 385, 47, 65), nullptr);

		new StaticObject(world, RectF(384, 369, 16, 16), nullptr);
		new StaticObject(world, RectF(368, 384, 16, 16), nullptr);
		new StaticObject(world, RectF(225, 401, 144, 15), nullptr);
		new StaticObject(world, RectF(48, 80, 16, 260), nullptr);
		new StaticObject(world, RectF(352, 144, 16, 196), nullptr);
		new StaticObject(world, RectF(352, 80, 16, 40), nullptr);
		new StaticObject(world, RectF(336, 80, 16, 24), nullptr);
		new StaticObject(world, RectF(288, 80, 16, 24), nullptr);
		new StaticObject(world, RectF(352, 24, 16, 16), nullptr);
		new StaticObject(world, RectF(368, 24, 32, 32), nullptr);
		new StaticObject(world, RectF(16, 24, 32, 32), nullptr);
		new StaticObject(world, RectF(48, 24, 16, 16), nullptr);
		new StaticObject(world, RectF(96, 24, 16, 16), nullptr);
		new StaticObject(world, RectF(112, 24, 32, 32), nullptr);

		new StaticObject(world, RectF(144, 24, 16, 128), nullptr);
		new StaticObject(world, RectF(272, 24, 16, 128), nullptr);

		new StaticObject(world, RectF(160, 128, 16, 136), nullptr);/*lato sx muri*/
		new StaticObject(world, RectF(256, 128, 16, 64), nullptr);

		new StaticObject(world, RectF(256, 192, 32, 120), nullptr);
		/*muri*/
		new StaticObject(world, RectF(176, 144, 32, 24), nullptr);
		new StaticObject(world, RectF(224, 144, 32, 24), nullptr);

		new StaticObject(world, RectF(176, 192, 32, 24), nullptr);
		new StaticObject(world, RectF(224, 192, 32, 24), nullptr);

		new StaticObject(world, RectF(176, 240, 32, 24), nullptr);
		new StaticObject(world, RectF(224, 240, 32, 24), nullptr);

		new StaticObject(world, RectF(144, 288, 112, 24), nullptr);
		new StaticObject(world, RectF(128, 176, 16, 164), nullptr);
		new StaticObject(world, RectF(64, 64, 32, 16), nullptr);
		new StaticObject(world, RectF(64, 80, 64, 24), nullptr);

		new StaticObject(world, RectF(64, 128, 16, 24), nullptr);
		new StaticObject(world, RectF(112, 128, 16, 24), nullptr);
		/*porta sx*/
		//new StaticObject(world, RectF(64, 176, 16, 24), nullptr);
		//new StaticObject(world, RectF(80, 176, 32, 24), nullptr);
		//new StaticObject(world, RectF(112, 176, 16, 24), nullptr);
		/*porta dx*/
		//new StaticObject(world, RectF(336, 176, 16, 24), nullptr);
		//new StaticObject(world, RectF(304, 176, 32, 24), nullptr);
		//new StaticObject(world, RectF(272, 176, 32, 24), nullptr);

		new StaticObject(world, RectF(64, 320, 16, 16), nullptr);
		new StaticObject(world, RectF(112, 320, 16, 16), nullptr);
		new StaticObject(world, RectF(64, 336, 64, 24), nullptr);

		new StaticObject(world, RectF(288, 320, 16, 16), nullptr);
		new StaticObject(world, RectF(336, 320, 16, 16), nullptr);
		new StaticObject(world, RectF(288, 336, 64, 24), nullptr);

		/*muretti nel ghiaccio*/
		new StaticObject(world, RectF(80, 224, 32, 24), nullptr);
		new StaticObject(world, RectF(80, 272, 32, 24), nullptr);
		new StaticObject(world, RectF(304, 224, 32, 24), nullptr);
		new StaticObject(world, RectF(304, 272, 32, 24), nullptr);

		new StaticObject(world, RectF(272, 312, 16, 28), nullptr);

		//new StaticObject(world, RectF(192, 448, 32, 0), nullptr);

		/*divanetti*/
		new StaticObject(world, RectF(304, 48, 32, 16), nullptr);

		new StaticObject(world, RectF(196, 52, 40, 24), nullptr);

		/*colonne*/
		new StaticObject(world, RectF(242, 362, 14, 4), nullptr);
		new StaticObject(world, RectF(226, 362, 14, 4), nullptr);
		new StaticObject(world, RectF(178, 362, 14, 4), nullptr);
		new StaticObject(world, RectF(162, 362, 14, 4), nullptr);

		RenderableObject* _col1 = new RenderableObject(world, RectF(240, 336, 16, 26), spriteLoader->get("col_lev_8"));
		RenderableObject* _col2 = new RenderableObject(world, RectF(224, 336, 16, 26), spriteLoader->get("col_lev_8"));
		RenderableObject* _col3 = new RenderableObject(world, RectF(176, 336, 16, 26), spriteLoader->get("col_lev_8"));
		RenderableObject* _col4 = new RenderableObject(world, RectF(160, 336, 16, 26), spriteLoader->get("col_lev_8"));

		//_col->setLayer(1);
		_col1->setLayer(1);
		_col2->setLayer(1);
		_col3->setLayer(1);
		_col4->setLayer(1);

		Hero* _hero = new Hero(world, PointF(201, 429));
		world->setPlayer(_hero);
		//boss
		world->addNpc(PointF(207, 60), "Dark Wizard");
		//door
		world->addDoor(PointF(80, 176), true, "level_1_door", PointF(32, 32));
		world->addDoor(PointF(304, 176), true, "level_1_door", PointF(32, 32));
		//trigger 
		world->addTrigger(RectF(192, 448, 32, 0), "overworld");
		world->addTrigger(RectF(104, 328, 8, 8), "dragonlord_castle_s");
		world->addTrigger(RectF(330, 328, 8, 8), "dragonlord_castle_s");

		//monsters
		world->addMonster("Rat");
		world->addMonster("Wizard");
		return world;

		}
else if (name == "level_8") {

	GameScene* world = new GameScene(RectF(0, 0, 527, 639), 1 / 100.0f);
	world->setBackgroundColor(Color(1, 70, 255));
	world->setCurrentMap(name);

	// terrain
	new RenderableObject(world, RectF(0, 0, 527, 639), spriteLoader->get("level_8"));

	// collaider
	new StaticObject(world, RectF(48, 32, 80, 24), nullptr);
	new StaticObject(world, RectF(32, 48, 16, 40), nullptr);
	new StaticObject(world, RectF(128, 48, 16, 40), nullptr);

	new StaticObject(world, RectF(16, 64, 16, 80), nullptr);
	new StaticObject(world, RectF(144, 48, 16, 104), nullptr);

	new StaticObject(world, RectF(32, 128, 16, 32), nullptr);
	new StaticObject(world, RectF(128, 128, 16, 40), nullptr);

	new StaticObject(world, RectF(48, 144, 16, 296), nullptr);
	new StaticObject(world, RectF(112, 144, 16, 40), nullptr);
	new StaticObject(world, RectF(96, 160, 16, 24), nullptr);

	new StaticObject(world, RectF(32, 416, 16, 40), nullptr);
	new StaticObject(world, RectF(16, 432, 16, 64), nullptr);
	new StaticObject(world, RectF(32, 496, 16, 32), nullptr);
	new StaticObject(world, RectF(48, 512, 16, 16), nullptr);
	new StaticObject(world, RectF(48, 528, 80, 16), nullptr);
	new StaticObject(world, RectF(112, 512, 16, 16), nullptr);

	new StaticObject(world, RectF(128, 496, 16, 32), nullptr);
	new StaticObject(world, RectF(144, 464, 16, 48), nullptr);
	new StaticObject(world, RectF(160, 480, 16, 128), nullptr);
	new StaticObject(world, RectF(192, 464, 16, 144), nullptr);
	new StaticObject(world, RectF(176, 592, 16, 16), nullptr);

	new StaticObject(world, RectF(208, 400, 16, 112), nullptr);
	new StaticObject(world, RectF(224, 496, 16, 32), nullptr);
	new StaticObject(world, RectF(240, 512, 16, 16), nullptr);
	new StaticObject(world, RectF(240, 528, 80, 16), nullptr);
	new StaticObject(world, RectF(304, 512, 16, 16), nullptr);
	new StaticObject(world, RectF(320, 496, 32, 32), nullptr);
	new StaticObject(world, RectF(336, 480, 96, 16), nullptr);

	new StaticObject(world, RectF(416, 496, 80, 16), nullptr);
	new StaticObject(world, RectF(480, 416, 16, 80), nullptr);
	new StaticObject(world, RectF(464, 416, 16, 24), nullptr);
	new StaticObject(world, RectF(416, 416, 16, 16), nullptr);
	new StaticObject(world, RectF(432, 416, 16, 24), nullptr);
	new StaticObject(world, RectF(336, 432, 96, 24), nullptr);

	new StaticObject(world, RectF(336, 416, 16, 16), nullptr);
	new StaticObject(world, RectF(320, 400, 16, 40), nullptr);
	new StaticObject(world, RectF(304, 400, 16, 24), nullptr);
	new StaticObject(world, RectF(240, 384, 80, 24), nullptr);
	new StaticObject(world, RectF(240, 400, 16, 24), nullptr);
	new StaticObject(world, RectF(224, 400, 16, 40), nullptr);

	new StaticObject(world, RectF(192, 352, 16, 72), nullptr);
	new StaticObject(world, RectF(208, 336, 16, 32), nullptr);
	new StaticObject(world, RectF(224, 336, 112, 16), nullptr);
	new StaticObject(world, RectF(304, 320, 16, 16), nullptr);
	new StaticObject(world, RectF(320, 304, 16, 32), nullptr);

	new StaticObject(world, RectF(336, 208, 16, 120), nullptr);
	new StaticObject(world, RectF(352, 192, 16, 40), nullptr);
	new StaticObject(world, RectF(368, 176, 16, 40), nullptr);
	new StaticObject(world, RectF(384, 160, 16, 40), nullptr);
	new StaticObject(world, RectF(400, 112, 16, 72), nullptr);
	new StaticObject(world, RectF(416, 144, 16, 48), nullptr);
	new StaticObject(world, RectF(448, 144, 16, 48), nullptr);
	new StaticObject(world, RectF(464, 128, 16, 40), nullptr);
	new StaticObject(world, RectF(480, 128, 16, 24), nullptr);
	new StaticObject(world, RectF(480, 48, 16, 80), nullptr);

	new StaticObject(world, RectF(464, 32, 16, 40), nullptr);
	new StaticObject(world, RectF(448, 16, 16, 40), nullptr);
	new StaticObject(world, RectF(416, 16, 16, 40), nullptr);
	new StaticObject(world, RectF(432, 16, 16, 24), nullptr);
	new StaticObject(world, RectF(400, 32, 16, 56), nullptr);
	new StaticObject(world, RectF(384, 16, 16, 40), nullptr);
	new StaticObject(world, RectF(256, 16, 132, 24), nullptr);

	new StaticObject(world, RectF(320, 40, 16, 8), nullptr);
	new StaticObject(world, RectF(256, 40, 16, 8), nullptr);
	new StaticObject(world, RectF(240, 32, 16, 56), nullptr);
	new StaticObject(world, RectF(160, 48, 80, 24), nullptr);
	new StaticObject(world, RectF(240, 112, 16, 88), nullptr);
	new StaticObject(world, RectF(256, 112, 48, 24), nullptr);
	new StaticObject(world, RectF(304, 96, 16, 72), nullptr);
	new StaticObject(world, RectF(320, 80, 16, 40), nullptr);
	new StaticObject(world, RectF(336, 96, 16, 72), nullptr);
	new StaticObject(world, RectF(320, 144, 16, 24), nullptr);
	new StaticObject(world, RectF(352, 112, 48, 24), nullptr);
	new StaticObject(world, RectF(176, 176, 64, 24), nullptr);/*muro sx bauli*/
	new StaticObject(world, RectF(256, 160, 16, 40), nullptr);
	new StaticObject(world, RectF(272, 176, 16, 56), nullptr);
	new StaticObject(world, RectF(288, 192, 16, 40), nullptr);
	new StaticObject(world, RectF(304, 208, 16, 24), nullptr);
	new StaticObject(world, RectF(160, 176, 16, 248), nullptr);
	new StaticObject(world, RectF(96, 224, 64, 24), nullptr);
	new StaticObject(world, RectF(96, 248, 16, 176), nullptr);

	new StaticObject(world, RectF(112, 400, 16, 40), nullptr);
	new StaticObject(world, RectF(144, 400, 16, 40), nullptr);

	/*poltrone(?)*/
	new StaticObject(world, RectF(131, 370, 12, 12), nullptr);
	new StaticObject(world, RectF(131, 338, 12, 12), nullptr);
	new StaticObject(world, RectF(131, 306, 12, 12), nullptr);
	new StaticObject(world, RectF(131, 274, 12, 12), nullptr);

	new StaticObject(world, RectF(176, 288, 16, 40), nullptr);
	new StaticObject(world, RectF(192, 288, 96, 24), nullptr);
	new StaticObject(world, RectF(272, 256, 32, 32), nullptr);
	new StaticObject(world, RectF(304, 256, 16, 24), nullptr);

	new StaticObject(world, RectF(512, 400, 0, 144), nullptr);/*spiaggia dx*/
	new StaticObject(world, RectF(496, 400, 16, 0), nullptr);
	new StaticObject(world, RectF(496, 384, 0, 16), nullptr);
	new StaticObject(world, RectF(480, 384, 16, 0), nullptr);
	new StaticObject(world, RectF(480, 368, 0, 16), nullptr);
	new StaticObject(world, RectF(480, 368, 16, 0), nullptr);

	new StaticObject(world, RectF(496, 336, 0, 32), nullptr);
	new StaticObject(world, RectF(480, 336, 16, 0), nullptr);
	new StaticObject(world, RectF(480, 336, 0, 16), nullptr);
	new StaticObject(world, RectF(464, 352, 16, 0), nullptr);
	new StaticObject(world, RectF(464, 320, 0, 32), nullptr);
	new StaticObject(world, RectF(448, 320, 16, 0), nullptr);
	new StaticObject(world, RectF(448, 304, 0, 16), nullptr);

	new StaticObject(world, RectF(448, 304, 32, 0), nullptr);
	new StaticObject(world, RectF(480, 288, 0, 16), nullptr);
	new StaticObject(world, RectF(480, 288, 16, 0), nullptr);
	new StaticObject(world, RectF(496, 240, 0, 48), nullptr);
	new StaticObject(world, RectF(464, 240, 32, 0), nullptr);
	new StaticObject(world, RectF(464, 224, 0, 16), nullptr);
	new StaticObject(world, RectF(464, 224, 16, 0), nullptr);
	new StaticObject(world, RectF(480, 192, 0, 32), nullptr);
	new StaticObject(world, RectF(480, 192, 16, 0), nullptr);
	new StaticObject(world, RectF(496, 160, 0, 32), nullptr);

	new StaticObject(world, RectF(496, 544, 16, 0), nullptr);
	new StaticObject(world, RectF(496, 544, 0, 16), nullptr);
	new StaticObject(world, RectF(416, 560, 80, 0), nullptr);
	new StaticObject(world, RectF(416, 544, 0, 16), nullptr);
	new StaticObject(world, RectF(400, 544, 16, 0), nullptr);
	new StaticObject(world, RectF(400, 496, 0, 48), nullptr);

	new StaticObject(world, RectF(384, 416, 0, 16), nullptr);
	new StaticObject(world, RectF(384, 416, 16, 0), nullptr);
	new StaticObject(world, RectF(400, 384, 0, 32), nullptr);
	new StaticObject(world, RectF(400, 384, 16, 0), nullptr);
	new StaticObject(world, RectF(416, 336, 0, 48), nullptr);
	new StaticObject(world, RectF(416, 336, 16, 0), nullptr);
	new StaticObject(world, RectF(432, 320, 0, 16), nullptr);
	new StaticObject(world, RectF(416, 320, 16, 0), nullptr);
	new StaticObject(world, RectF(416, 272, 0, 48), nullptr);
	new StaticObject(world, RectF(416, 272, 16, 0), nullptr);
	new StaticObject(world, RectF(432, 272, 0, 16), nullptr);
	new StaticObject(world, RectF(432, 288, 32, 0), nullptr);
	new StaticObject(world, RectF(464, 272, 0, 16), nullptr);
	new StaticObject(world, RectF(464, 272, 16, 0), nullptr);
	new StaticObject(world, RectF(480, 256, 0, 16), nullptr);

	new StaticObject(world, RectF(448, 256, 32, 0), nullptr);
	new StaticObject(world, RectF(448, 240, 0, 16), nullptr);
	new StaticObject(world, RectF(416, 240, 32, 0), nullptr);
	new StaticObject(world, RectF(416, 224, 0, 16), nullptr);
	new StaticObject(world, RectF(400, 224, 16, 0), nullptr);
	new StaticObject(world, RectF(400, 224, 0, 16), nullptr);
	new StaticObject(world, RectF(384, 240, 16, 0), nullptr);
	new StaticObject(world, RectF(384, 240, 0, 32), nullptr);
	new StaticObject(world, RectF(368, 272, 16, 0), nullptr);
	new StaticObject(world, RectF(368, 256, 0, 16), nullptr);
	new StaticObject(world, RectF(352, 256, 16, 0), nullptr);

	new StaticObject(world, RectF(192, 224, 16, 16), nullptr);
	new StaticObject(world, RectF(208, 224, 16, 16), nullptr);
	new StaticObject(world, RectF(224, 224, 16, 16), nullptr);
	new StaticObject(world, RectF(192, 240, 16, 16), nullptr);
	new StaticObject(world, RectF(192, 256, 16, 16), nullptr);
	new StaticObject(world, RectF(208, 256, 16, 16), nullptr);
	new StaticObject(world, RectF(224, 256, 16, 16), nullptr);
	new StaticObject(world, RectF(240, 256, 16, 16), nullptr);
	new StaticObject(world, RectF(240, 240, 16, 16), nullptr);

	new StaticObject(world, RectF(260, 452, 44, 22), nullptr);


	/*porta camera dei bauli*/
	new StaticObject(world, RectF(304, 232, 16, 24), nullptr);

	/*colonne*/
	new StaticObject(world, RectF(178, 106, 14, 4), nullptr);
	new StaticObject(world, RectF(210, 106, 14, 4), nullptr);
	new StaticObject(world, RectF(178, 154, 14, 4), nullptr);
	new StaticObject(world, RectF(210, 154, 14, 4), nullptr);

	RenderableObject* _col1 = new RenderableObject(world, RectF(176, 80, 16, 26), spriteLoader->get("col_lev_8"));
	RenderableObject* _col2 = new RenderableObject(world, RectF(208, 80, 16, 26), spriteLoader->get("col_lev_8"));
	RenderableObject* _col3 = new RenderableObject(world, RectF(176, 128, 16, 26), spriteLoader->get("col_lev_8"));
	RenderableObject* _col4 = new RenderableObject(world, RectF(208, 128, 16, 26), spriteLoader->get("col_lev_8"));

	//_col->setLayer(1);
	_col1->setLayer(1);
	_col2->setLayer(1);
	_col3->setLayer(1);
	_col4->setLayer(1);

	//AddNpc
	world->addNpc(PointF(175 + 16 * 6, 550 - 16 * 5), "Dragonlord");
	Hero* _hero = new Hero(world, PointF(176, 556));
	//Hero* _hero = new Hero(world, PointF(129, 270));
	world->setPlayer(_hero);
	//door
	world->addDoor(PointF(304, 225), true, "level_8_door", PointF(14, 32));
	//trigger 
	world->addTrigger(RectF(176,576,16,16),"dragonlord_castle_s");
	//monsters
	world->addMonster("Rat");
	world->addMonster("Wizard");
	return world;
	}


		else
		{
			std::cerr << "Unrecognized game scene name \"" << name << "\"\n";
			return nullptr;
		}
}
