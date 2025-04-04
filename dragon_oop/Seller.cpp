#include"Seller.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "collisionUtils.h"
#include "Hero.h"
#include "Audio.h"


using namespace agp;

Seller::Seller(Scene* scene, PointF pos, const std::string name, bool on, Hero* hero) :Npc(scene, pos, name)

{
	_on = on;

	if (_on) {

		_spells.push_back(new Spell("Life", 3, 50, [hero]() {

			hero->damage_hp(-4);
			hero->decreaseMp(3);

			},true));

		_spells.push_back(new Spell("Rage", 1, 50, [hero]() {

			hero->turnRage(true);
			hero->decreaseMp(1);

			},true));

		_spells.push_back(new Spell("Light", 1, 50, [hero]() {

			hero->switchDark(true);
			hero->decreaseMp(1);
			Audio::instance()->playSound("43 Dragon Quest 1 - Cast A Spell");

			},false));
	}
	else
	{
		//ARMI
		_weapons.push_back(new Weapon("Excalibur", 4, 1000));

		_weapons.push_back(new Weapon("Iron Sword", 2, 50));
		//ITEMS
		_items.push_back(new Item("Health Potion", 10, [hero]() {

			hero->damage_hp(-4);

			},true));

		_items.push_back(new Item("Mana Potion", 10, [hero]() {

			hero->decreaseMp(-3);

			},true));

		_items.push_back(new Item("Torch", 10, [hero]() {

			hero->switchDark(true);

			},true));

	}



	_name = name;
	_sprites["spellseller_left"] = SpriteFactory::instance()->get("spellseller_left");
	_sprites["spellseller_right"] = SpriteFactory::instance()->get("spellseller_right");
	_sprites["itemseller_right"] = SpriteFactory::instance()->get("itemseller_right");

}

void Seller::update(float dt) {
	StaticObject::update(dt);


	if (_name == "spellseller_L" || _name == "spellseller_L1")
		_sprite = _sprites["spellseller_left"];
	else if (_name == "spellseller_R")
		_sprite = _sprites["spellseller_right"];
	else if (_name == "itemseller_R" || _name == "itemseller_R1")
		_sprite = _sprites["itemseller_right"];

}

bool Seller::hit(Hero* hero) {
	RectF dialogue_area = RectF(rect().pos.x - 1, rect().pos.y - 1, 19, 19);
	return dialogue_area.intersects(hero->rect());
}