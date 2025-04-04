#pragma once
#include <map>
#include <vector>
#include <list>
#include "geometryUtils.h"
#include "graphicsUtils.h"
#include <functional>

namespace agp
{
	class Spell;
}
//spell class
class agp::Spell {
	private:
		std::string spell_name;
		int mp_cost;
		int _cost;
		std::function<void()> spell_task;
		bool _fight;
	public:
		Spell(const std::string name, int mpcost, int cost, std::function<void()> task,bool fight);
		const std::string getName() { return spell_name; }
		void task() { spell_task(); }
		int getCost() { return mp_cost; }
		int getMoneyCost() { return _cost; }
		bool getFight() { return _fight; }
};