#pragma once

#include "StaticObject.h"
#include <map>
#include "Hero.h"
#include "Item.h"


namespace agp
{
	class Chest;
}

class agp::Chest :public StaticObject
{
	private:
		std::map<std::string, Sprite*> _sprites;
		Item* drop;
		bool opened;
		bool active_item;
	public:
		Chest(Scene* scene, PointF pos, Item* item,bool on);
		virtual ~Chest() {};
		virtual void update(float dt) override;
		bool hit(Hero* hero);
		std::string getDialogue();
		void switchOpen() { opened = true; }
		bool getOpened() { return opened; }
		Item* getDrop() { return drop; }
		bool getActive() { return active_item; }
};