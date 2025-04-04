#pragma once

#include "DynamicObject.h"
#include "Item.h"
#include "Weapon.h"
#include "Spell.h"
#include <map>
#include "Monster.h"
#include <iostream>
namespace agp
{
	class Hero;
	class Monster;
}
struct PlayerStats {
	int hp=0;
	int mp=0;
	int coins=0;
	int keys=0;
	std::map<int, agp::Item*> items;
	std::map<int, agp::Weapon*> weapons;
	std::map<int, agp::Spell*> spells;
	agp::Weapon* weapon_equipped=nullptr;
};

class agp::Hero : public DynamicObject
{
	private:
		int health_points;
		int mana_points;
		int max = 10;
		int coins;
		int keys;
		bool _walking; 
		bool rage=false;
		std::map<std::string, Sprite*> _sprites;
		double _x_vel_last_nonzero;
		std::map<int,Item*> items;
		std::map<int,Weapon*> weapons;
		std::map<int,Spell*> spells;
		Weapon* weapon_equipped;
		bool death=false;
		bool dark_off = false;

		
	public:

		Hero(Scene* scene, PointF pos);
		virtual ~Hero() {};

		virtual void update(float dt) override;

		void resize(bool stretch, bool horizontally);
		

		virtual std::string name() { return strprintf("Hero[%d]", _id); }
		//utility function
		int getHp() { return health_points; }
		int getMp() { return mana_points; }
		bool getDeath() { return death; }
		void teleport(const PointF spawn);
		void addWeapon(Weapon* weapon);
		void addWeapon(const std::string name);
		void addSpell(Spell* spell);
		void addSpell(const std::string name);
		void addItem(Item* item);
		void addItem(const std::string name);
		void removeItem(int n);
		std::map<int,Item*> getItems() { return items; }
		std::map<int,Weapon*> getWeapons() { return weapons; }
		std::map<int,Spell*> getSpells() { return spells; }
		void addCoins(int n) { coins=coins+n; }
		int getCoins() { return coins; }
		int getKeys() { return keys; }
		void addKey(int key) { keys += key; };
		bool getWalking() { return _walking; }
		Weapon* getWeapon() { return weapon_equipped; }
		void damage_hp(int n) { health_points = health_points - n; }
		void decreaseMp(int n) { mana_points = mana_points - n; }
		void restore() { health_points = max; mana_points = max; }
		void equipWeapon(Weapon* weapon) { weapon_equipped = weapon; }
		//battle
		void turnDeath();
		int getBattleSpells();
		int getBattleItems();
		//transition
		void stop();
		void switchDark(bool on) { dark_off = on; }
		bool getDark() { return dark_off; }
		//rage spell
		bool getRage() { return rage; }
		void turnRage(bool on) { rage = on; }
		//seller menu
		bool Hero::checkWeapon(Weapon* weapon);
		int Hero::checkItem(Item* item);
		bool Hero::checkSpell(Spell* spell);
		
		PlayerStats saveData() {
			PlayerStats data;
			data.hp = health_points;
			data.mp = mana_points;
			data.keys = keys;
			data.coins = coins;
			data.items=items;
			data.spells = spells;
			data.weapons = weapons;
			data.weapon_equipped = weapon_equipped;
			return data;
		}
		void loadData(PlayerStats data) {
			health_points = data.hp;
			mana_points = data.mp;
			keys = data.keys;
			coins = data.coins;
			items = {};
			for (auto item : data.items) 
				addItem(item.second->getName());
			spells = {};
			for (auto spell : data.spells)
				addSpell(spell.second->getName());
			weapons = {};
			for (auto weapon : data.weapons)
				addWeapon(weapon.second->getName());
			weapon_equipped = data.weapon_equipped;

		}
		
};