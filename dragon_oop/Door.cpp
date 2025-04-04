#include "Door.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "collisionUtils.h"

using namespace agp;

Door::Door(Scene* scene, PointF pos, bool on, const std::string name, PointF dim)
	:StaticObject(scene, RectF(pos.x, pos.y, dim.x, dim.y), nullptr) {
	_name = name;
	opened = false;
	active_item = on;
	//1st map doors
	_sprites["locked_radatomecastle_door"] = SpriteFactory::instance()->get("radatomecastle_door");
	_sprites["opened_door"] = NULL;

	//2nd map doors
	_sprites["locked_radatomecastle_door2"] = SpriteFactory::instance()->get("radatomecastle_door2");;
	_sprites["opened_radatomecastle_door2"] = NULL;

	//4th map doors
	_sprites["locked_level_1_door"] = SpriteFactory::instance()->get("level_1_door");
	_sprites["opened_leve_1_door"] = NULL;

	//level 8
	_sprites["locked_level_8_door"] = SpriteFactory::instance()->get("level_8_door");
	_sprites["opened_level_8_door"] = NULL;


}
void Door::update(float dt) {
	StaticObject::update(dt);
	if (opened) {
		this->_compenetrable = true;

		if (_name == "radatomecastle_door")
			_sprite = _sprites["opened_door"];
		else if (_name == "radatomecastle_door2")
			_sprite = _sprites["opened_radatomecastle_door2"];
		else if (_name == "level_1_door")
			_sprite = _sprites["opened_level_1_door"];
		else if (_name == "level_8_door")
			_sprite = _sprites["opened_level_8_door"];
	}
	else
	{
		if (_name == "radatomecastle_door")
			_sprite = _sprites["locked_radatomecastle_door"];
		else if (_name == "radatomecastle_door2")
			_sprite = _sprites["locked_radatomecastle_door2"];
		else if (_name == "level_1_door")
			_sprite = _sprites["locked_level_1_door"];
		else if (_name == "level_8_door")
			_sprite = _sprites["locked_level_8_door"];


	}
}
bool Door::hit(Hero* hero) {
	RectF dialogue_area = RectF(rect().pos.x - 1, rect().pos.y - 1, 19, 19);
	return (dialogue_area.intersects(hero->rect()) && !opened);
}
