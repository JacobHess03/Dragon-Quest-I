#include "Hero.h"
#include "Audio.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "Dialogue_Menu.h"
#include "Game.h"
#include <iostream>

using namespace agp;

Hero::Hero(Scene* scene, PointF pos)
	: DynamicObject(scene, RectF( pos.x, pos.y, 16, 16 ), nullptr)
{
	health_points = max;
	mana_points = max;
	coins = 0;
	keys = 0;
	_collider.adjust(1.5, 1, 0, 0);
	_walking = false; 
	_x_vel_last_nonzero = 0;
	items = {};
	spells = {};
	weapons = {};
	weapon_equipped = new Weapon("Shabby Sword", 3,2);
	addWeapon(weapon_equipped);
	
	_sprites["walk_right"] = SpriteFactory::instance()->get("walk_right");
	_sprites["walk_left"] = SpriteFactory::instance()->get("walk_left");
	_sprites["walk_up"]= SpriteFactory::instance()->get("walk_up");
	_sprites["walk_down"] = SpriteFactory::instance()->get("walk_down");
	

}

void Hero::resize(bool stretch, bool horizontally)
{
	_rect.adjust(0, 0,
		(horizontally ? (stretch ? -0.1f : +0.1f) : 0),
		(horizontally ? 0 : (stretch ? -0.1f : +0.1f)));

	_collider = { 0, 0, _rect.size.x, _rect.size.y };
}

void Hero::update(float dt)
{
	DynamicObject::update(dt);
	//state logic
	//_walking = _vel.x != 0;
	//for link walking is when vel has a componet != 0 (componet x or component y)
	_walking = (_vel.x != 0 || _vel.y != 0);

	//animations
	if ((_walking && (this->_x_dir == Direction::RIGHT))||this->last_dir==Direction::RIGHT)
		_sprite = _sprites["walk_right"];
	else if ((_walking && (this->_x_dir == Direction::LEFT)) || this->last_dir == Direction::LEFT)
		_sprite = _sprites["walk_left"];
	else if ((_walking && (this->_y_dir == Direction::UP)) || this->last_dir == Direction::UP)
		_sprite = _sprites["walk_up"];
	else if ((_walking && (this->_y_dir == Direction::DOWN)) || this->last_dir == Direction::DOWN)
		_sprite = _sprites["walk_down"];
	else
		_sprite = _sprites["walk_down"];
}
void Hero::teleport(const PointF spawn) {
	this->setPos(spawn);
}
void Hero::addWeapon(Weapon* weapon) {
	weapons[weapons.size()]=weapon;
}
void Hero::addSpell(Spell* spell) {
	spells[spells.size()] = spell;
}
void Hero::addItem(Item* item) {
	items[items.size()] = item;
}
void Hero::removeItem(int n) {
	items.erase(n);
}
void Hero::turnDeath() {
	if (death)
		death = false;
	else
		death = true;
}
int Hero::getBattleSpells() {
	int i = 0;
	for (auto spell : spells) {
		if (spell.second->getFight())
			i++;
	}
	return i;
}
int Hero::getBattleItems() {
	int i = 0;
	for (auto item : items) {
		if (item.second->getFight())
			i++;
	}
	return i;
}
void Hero::stop() {
		_vel.x = 0;
		_vel.y = 0;
		_x_dir = Direction::NONE;
		_y_dir = Direction::NONE;
		last_dir = Direction::NONE;
		
}
void Hero::addItem(const std::string name) {
	if (name == "Health Potion")
		items[items.size()] = new Item("Health Potion",2, [this]() {
		health_points += 3;
		if (health_points > max)
			health_points = max;
			}, true);
	else if (name =="Mana Potion")
		items[items.size()] = new Item("Mana Potion", 2, [this]() {
		mana_points += 3;
		if (mana_points > max)
			mana_points = max;
			}, true);
	else if (name == "Torch")
		items[items.size()] = new Item("Torch",2,[this]() {
		dark_off = true;
			}, false);
}
void Hero::addSpell(const std::string name) {
	if (name == "Life")
		spells[spells.size()]=new Spell("Life", 3,2, [this]() {
		if (mana_points >= 3) {
			health_points += 3;
			if (health_points > max)
				health_points = max;
			decreaseMp(3);
		}
		else
			Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");

			}, true);
	else if (name == "Rage")
		spells[spells.size()]=new Spell("Rage", 2,2, [this]() {
		if (mana_points >= 2) {
			rage = true;
			decreaseMp(2);
		}
		else
			Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");

			}, true);
	else if (name == "Light")
		spells[spells.size()]=new Spell("Light", 1,2, [this]() {
		if (mana_points >= 1) {
			dark_off = true;
			decreaseMp(1);
			Audio::instance()->playSound("43 Dragon Quest 1 - Cast A Spell");
		}
		else
			Audio::instance()->playSound("27 Dragon Quest 1 - Barrier");
			}, false);
}
void Hero::addWeapon(const std::string name) {
	if (name == "Shabby Sword")
		weapons[weapons.size()] = new Weapon("Shabby Sword", 1,2);
	else if (name=="Excalibur")
		weapons[weapons.size()] = new Weapon("Excalibur", 4,2);
	else if (name=="Iron Sword")
		weapons[weapons.size()] = new Weapon("Iron Sword", 2, 2);


}
bool Hero::checkWeapon(Weapon* weapon) {
	bool on = false;
	for (auto _weapon : weapons) {
		if (_weapon.second->getName() == weapon->getName())
			on = true;
	}
	return on;
}

int Hero::checkItem(Item* item) {
	int count = 1;
	for (auto _item : items) {
		if (_item.second->getName() == item->getName())
			count++;
	}
	std::cout << count;
	return count;

}

bool Hero::checkSpell(Spell* spell) {
	bool on = false;
	for (auto _spell : spells) {
		if (_spell.second->getName() == spell->getName())
			on = true;
	}
	return on;
}