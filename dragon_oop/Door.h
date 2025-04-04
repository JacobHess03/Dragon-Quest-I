#pragma once

#include "StaticObject.h"
#include <map>
#include "Hero.h"
#include "Item.h"

namespace agp
{
	class Door;
}

class agp::Door :public StaticObject
{
private:
	std::map<std::string, Sprite*> _sprites;
	Item* drop;
	bool opened;
	bool active_item;
	std::string _name;
public:
	Door(Scene* scene, PointF pos, bool on, const std::string name, PointF dim);
	virtual ~Door() {};
	virtual void update(float dt) override;
	bool hit(Hero* hero);
	void switchOpen() { opened = true; }
	bool getOpened() { return opened; }
	Item* getDrop() { return drop; }
	bool getActive() { return active_item; }

};