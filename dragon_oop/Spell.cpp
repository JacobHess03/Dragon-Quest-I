#include "Spell.h"

using namespace agp;

Spell::Spell(const std::string name, int mpcost, int cost, std::function<void()> task,bool fight) {
	spell_name = name;
	mp_cost = mpcost;
	_cost = cost;
	spell_task = task;
	_fight = fight;
}