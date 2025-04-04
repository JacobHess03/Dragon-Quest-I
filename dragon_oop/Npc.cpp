#include"Npc.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "collisionUtils.h"


using namespace agp;

Npc::Npc(Scene* scene, PointF pos, const std::string name)
	:StaticObject(scene, RectF(pos.x, pos.y, 18, 17), nullptr)
{
	_name = name;
	if (_name == "king")
		_dialogue = { "Welcome hero", "We have been waiting for you", "You have a fundamental task:", "save the princess","from the dragon lord",
"Do not be afraid along the way you will","find everything you need", "may the strength of the kingdom","be with you" };
	else if (_name == "counselor_L")
		_dialogue = { "Remember to open the chests","to get the coins","May blessing of the king","be with you" };
	else if (_name == "guard_1" || _name == "guard_2")
		_dialogue = { "May the force be with you", "Keep your guard up" };
	else if (_name == "guard_L1" || _name == "guard_L2" || _name == "guard_L3")
		_dialogue = { "May the force be with you", "Keep your guard up" };
	else if (_name == "guard_R1" || _name == "guard_R2")
		_dialogue = { "May the force be with you", "Keep your guard up" };
	else if (_name == "knight_R")
		_dialogue = { "Before entering make sure you ","have everything you need","Do not forget the torch", "It s very dark in there"};
	else if (_name == "knight_L")
		_dialogue = { "You cannot cross", "the bridge is disused" };
	else if (_name == "knight_U")
		_dialogue = { "I am glad to have you","on the team","Watch out for monsters","in the tall grass" };
	else if (_name == "castlegirl_U")
		_dialogue = { "For any potions or weapons","you can ask the merchants" };
	else if (_name == "townboy_D1" || _name == "townboy_D2")
		_dialogue = { "To recover HP", "buy the health potion" };
	else if (_name == "towngirl_L")
		_dialogue = { "For spells", "you can ask the wizards" };
	else if (_name == "towngirl_R")
		_dialogue = { "Before a trip", "do not forget", "to buy the potions" };
	else if (_name == "spellseller_L")
		_dialogue = { "You can buy from me", "every kind of potion and magic available" };
	else if (_name == "spellseller_L1")
		_dialogue = { "You buy the potion you need", "before the fight" };
	else if (_name == "itemseller_R1")
		_dialogue = { "You buy the weapon","you need against","the dragon lord" };
	else if (_name == "itemseller_R")
		_dialogue = { "You can buy from me", "any type of weapon available" };
	else if (_name == "Dark Wizard")
		_dialogue = { "Welcome to my lord s castle","You thought I was him right?","You can reach him only with","this key","Fight right now and prepare to die!" };
	else if (_name == "Dragonlord")
		_dialogue = { "I was finally waiting for you", "the taste of defeat is upon you", "the princess will never","be yours. Fight now!" };
	else if (_name == "princess_D")
		_dialogue = { "Thank you very much","hero","as a reward you can be part of the royal family","you and your descendants" };

	_sprites["king_standing"] = SpriteFactory::instance()->get("king_standing");
	_sprites["counselor_left"] = SpriteFactory::instance()->get("counselor_left");
	_sprites["guard_down"] = SpriteFactory::instance()->get("guard_down");
	_sprites["guard_left"] = SpriteFactory::instance()->get("guard_left");
	_sprites["guard_right"] = SpriteFactory::instance()->get("guard_right");
	_sprites["knight_right"] = SpriteFactory::instance()->get("knight_right");
	_sprites["knight_left"] = SpriteFactory::instance()->get("knight_left");
	_sprites["knight_up"] = SpriteFactory::instance()->get("knight_up");
	_sprites["castlegirl_up"] = SpriteFactory::instance()->get("castlegirl_up");
	_sprites["towngirl_left"] = SpriteFactory::instance()->get("towngirl_left");
	_sprites["towngirl_right"] = SpriteFactory::instance()->get("towngirl_right");
	_sprites["townboy_down"] = SpriteFactory::instance()->get("townboy_down");
	_sprites["spellseller_left"] = SpriteFactory::instance()->get("spellseller_left");
	_sprites["spellseller_right"] = SpriteFactory::instance()->get("spellseller_right");
	_sprites["itemseller_right"] = SpriteFactory::instance()->get("itemseller_right");
	_sprites["wizard"] = SpriteFactory::instance()->get("red_wizard");
	_sprites["strong_wizard"] = SpriteFactory::instance()->get("yellow_wizard");
	_sprites["dragonlord_standing"] = SpriteFactory::instance()->get("dragonlord_standing");
	_sprites["hero_princess_down"] = SpriteFactory::instance()->get("hero_princess_down");

	if (_name == "Dragonlord" || _name == "Dark Wizard")
		fight = true;
}

void Npc::update(float dt) {
	StaticObject::update(dt);

	if (_name == "king")
		_sprite = _sprites["king_standing"];
	else if (_name == "princess_D")
		_sprite = _sprites["hero_princess_down"];
	
	else if (_name == "Wizard")
		_sprite = _sprites["wizard"];
	else if (_name == "counselor_L")
		_sprite = _sprites["counselor_left"];
	else if (_name == "spellseller_L" || _name == "spellseller_L1")
		_sprite = _sprites["spellseller_left"];
	else if (_name == "spellseller_R")
		_sprite = _sprites["spellseller_right"];
	else if (_name == "itemseller_R" || _name == "itemseller_R1")
		_sprite = _sprites["itemseller_right"];
	else if (_name == "guard_1" || _name == "guard_2")
		_sprite = _sprites["guard_down"];
	else if (_name == "guard_R1" || _name == "guard_R2")
		_sprite = _sprites["guard_right"];
	else if (_name == "guard_L1" || _name == "guard_L2" || _name == "guard_L3")
		_sprite = _sprites["guard_left"];
	else if (_name == "knight_R")
		_sprite = _sprites["knight_right"];
	else if (_name == "knight_L")
		_sprite = _sprites["knight_left"];
	else if (_name == "knight_U")
		_sprite = _sprites["knight_up"];
	else if (_name == "castlegirl_U")
		_sprite = _sprites["castlegirl_up"];
	else if (_name == "towngirl_L")
		_sprite = _sprites["towngirl_left"];
	else if (_name == "towngirl_R")
		_sprite = _sprites["towngirl_right"];
	else if (_name == "townboy_D1" || _name == "townboy_D2")
		_sprite = _sprites["townboy_down"];
	else if (_name == "Dragonlord" || _name == "True dragonlord" || "Dark Wizard") {
		_sprite = _sprites["dragonlord_standing"];
	}

	if (defeated) {
		if (_name == "Dragonlord" && count == 0) {
			_name = "True dragonlord";
			_dialogue = { "You re strong enough to see my ","true form! Face me now Hero!!!" };
			defeated = false;
		}
		else if (_name == "True dragonlord" && count == 1) 
			count++;
	}

}

bool Npc::hit(Hero* hero) {
	RectF dialogue_area = RectF(rect().pos.x - 1, rect().pos.y - 1, 19, 19);
	return dialogue_area.intersects(hero->rect());
}