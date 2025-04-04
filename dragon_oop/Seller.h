#pragma once

#include "StaticObject.h"
#include <map>
#include "Hero.h"
#include "Npc.h"
#include "Spell.h"
#include "Weapon.h"


namespace agp
{
	class Seller;
}

class agp::Seller :public Npc
{
private:
	std::string _name;
	std::vector<std::string> _dialogue;
	std::map<std::string, Sprite*> _sprites;
	bool _on;

	//std::vector<Spell*> _spells;
	//std::vector<Weapon*> _weapons;
	Hero* _hero;

public:
	Seller(Scene* scene, PointF pos, const std::string name, bool on, Hero* hero);
	virtual ~Seller() {};
	virtual void update(float dt) override;
	bool hit(Hero* hero);
	std::vector<std::string> getDialogue() { return _dialogue; }
	std::vector<Spell*> _spells;
	std::vector<Weapon*> _weapons;
	std::vector<Item*> _items;
	bool getOn() { return _on; }



};
