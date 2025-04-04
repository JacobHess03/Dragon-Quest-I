#include "Chest.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "collisionUtils.h"

using namespace agp;

Chest::Chest(Scene* scene, PointF pos, Item* item,bool on)
	  :StaticObject(scene, RectF(pos.x, pos.y, 18, 17), nullptr) {
	  drop = item;
	  opened = false;
	  active_item = on;
	  _sprites["locked_chest"] = SpriteFactory::instance()->get("chest_1");
	  _sprites["opened_chest"] = SpriteFactory::instance()->get("chest_2");
}
void Chest::update(float dt) {
	StaticObject::update(dt);
	if (opened)
		_sprite = _sprites["opened_chest"];
	else
		_sprite = _sprites["locked_chest"];
}
bool Chest::hit(Hero* hero) {
	RectF dialogue_area = RectF(rect().pos.x - 1, rect().pos.y - 1, 19, 19);
	return (dialogue_area.intersects(hero->rect()) && !opened);
}
std::string Chest::getDialogue() {
	if (drop != nullptr)
		return ("You found " + this->drop->getName() + "!");
	else
		return "";
}