#include "Monster.h"
#include "Audio.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "Sprite.h"

using namespace agp;

Monster::Monster(Scene* scene, PointF pos, const std::string name)
	:StaticObject(scene, RectF(pos.x,pos.y, 16, 16),nullptr)
{
	_name = name;
	_hp = 0;
	_money = 0;
	attacks = {};
	_sprites["slime"] = SpriteFactory::instance()->get("blue_slime");
	_sprites["wizard"] = SpriteFactory::instance()->get("red_wizard");
	_sprites["rat"] = SpriteFactory::instance()->get("yellow_rat");
	_sprites["strong_wizard"] = SpriteFactory::instance()->get("yellow_wizard");
	_sprites["dragonlord"] = SpriteFactory::instance()->get("dragonlord");
	_sprites["true_dragonlord"] = SpriteFactory::instance()->get("true_dragonlord_standing");
	_sprites["dragon animation"] = SpriteFactory::instance()->get("dragon_fire");

	if (_name == "Slime") {
		_hp = 1;
		_money = 5;
		_rect = RectF(5.5, 6, 5, 5);
		_sprite = _sprites["slime"];
		attacks.push_back(new Attack("slime_attack", 1,false,true));
	}
	else if (_name == "Wizard" || _name=="Dark Wizard") {
		if (_name == "Wizard")
			_hp = 3;
		else
			_hp = 5;
		if (_name == "Wizard")
			_money = 20;
		else
			_money = 100;
		_rect = RectF(5.5, 5, 5, 5);
		if (_name == "Wizard")
			_sprite = _sprites["wizard"];
		else
			_sprite = _sprites["strong_wizard"];
		attacks.push_back(new Attack("fireball", 2,true,true));
		attacks.push_back(new Attack("wizard_attack", 1,false,true));
	}
	else if (_name == "Rat") {
		_hp = 2;
		_money = 20;
		_rect = RectF(5.5, 5, 5, 5);
		_sprite = _sprites["rat"];
		attacks.push_back(new Attack("rat_attack", 2,false,true));
	}
	else if (_name == "Dragonlord") {
		_hp = 5;
		_money = 100;
		_sprite = _sprites["dragonlord"];
		attacks.push_back(new Attack("firebane", 2,true,true));
		attacks.push_back(new Attack("dragonlord_attack", 1,false,true));
		_rect.size.x = 3;
		_rect.size.y = 3;
		_rect.pos = { 6.6,6 };
	}
	else if (_name == "True dragonlord") {
		_hp = 7;
		_money = 1000;
		_rect = RectF(5.5, 4, 5, 6);
		_sprite = _sprites["dragon animation"];
		attacks.push_back(new Attack("breath fire", 2,true,true));
		attacks.push_back(new Attack("intense flames", 3,true,true));
		attacks.push_back(new Attack("dragon_attack", 1,false,true));
	}
	
	
}
Attack::Attack(const std::string name, int damage,bool spell,bool physical) {
	_attack_name = name;
	_damage = damage;
	_spell = spell;
	_physical = physical;
}
void Monster::update(float dt) {
	StaticObject::update(dt);
}
Attack* Monster::pick_attack() {
	int n = -1;
	n = rand() % attacks.size();
	return attacks[n];
}