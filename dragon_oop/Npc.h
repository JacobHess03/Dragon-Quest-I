#pragma once

#include "StaticObject.h"
#include <map>
#include "Hero.h"


namespace agp
{
	class Npc;
}

class agp::Npc :public StaticObject
{
private:
	std::string _name;
	std::vector<std::string> _dialogue;
	std::map<std::string, Sprite*> _sprites;
	bool defeated = false;
	bool fight=false;
	int count = 0;
public:
	Npc(Scene* scene, PointF pos, const std::string name);
	virtual ~Npc() {};
	virtual void update(float dt) override;
	bool hit(Hero* hero);
	std::vector<std::string> getDialogue() { return _dialogue; }
	bool getFight() { return fight; }
	void setDefeat(bool on) { defeated = on; }
	const std::string getName() { return _name; }
	int getCount() { return count; }
};