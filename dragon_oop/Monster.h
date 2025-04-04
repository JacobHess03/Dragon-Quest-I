#pragma once
#include "RenderableObject.h"
#include <map>
#include "StaticObject.h"
#include "Hero.h"

namespace agp
{
	class Monster;
	class Attack;
}

class agp::Monster :public StaticObject {
	private:
		std::string _name;
		int _hp;
		int _money;
		std::map<std::string, Sprite*> _sprites;
		std::vector<Attack*> attacks;
	public:
		Monster(Scene* scene, PointF pos, const std::string name);
		virtual ~Monster() {};
		virtual void update(float dt) override;
		std::string getName(){ return _name; }
		void hit(int damage) { _hp -= damage; }
		int getHp() { return _hp; }
		int getMoney() { return _money; }
		Attack* pick_attack();
};
class agp::Attack {
	private:
		std::string _attack_name;
		int _damage;
		bool _spell;
		bool _physical;
	public:
		Attack(const std::string name, int damage,bool spell,bool physical);
		std::string getName() { return _attack_name; }
		int getDamage() { return _damage; }
		bool getSpell() { return _spell; }
		bool getPhysical() { return _physical; }
		
};