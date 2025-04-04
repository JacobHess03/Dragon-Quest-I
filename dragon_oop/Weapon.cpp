#include "Weapon.h"

using namespace agp;

Weapon::Weapon(const std::string name, int damage,int cost) {
	weapon_name = name;
	_damage = damage;
	_cost = cost;
}

