#pragma once
#include <map>
#include <vector>
#include <list>
#include "geometryUtils.h"
#include "graphicsUtils.h"
#include <functional>

namespace agp
{
	class Weapon;
}
//weapon class
class agp::Weapon {
	private:
		std::string weapon_name;
		int _damage;
		int _cost;

	public:
		Weapon(const std::string name, int damage,int cost);
		int getDamage() { return _damage; }
		int getCost() { return _cost; }
		std::string getName() { return weapon_name; }
		void addDamage(int n) { _damage += n; }
		

};