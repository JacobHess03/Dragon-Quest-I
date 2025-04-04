#include "Dialogue_Menu.h"
#include "SpriteFactory.h"
#include "Game.h"
#include "Audio.h"


using namespace agp;

Dialogue_Menu::Dialogue_Menu(const PointF& position, float width,Npc* character)
	:UIScene(RectF(0, 0,50,40))
{
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground=new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255, 255, 255, 255));
	_blocking = true;
	_character = character;
	battle_dialogue = {};
	dialogue_counter = 1;
	words = nullptr;
	on = 0;
	sound = false;
	hero_sound = "";
	monster_sound = "";
	victory = false;
	addText(_character->getDialogue()[0]);
}
Dialogue_Menu::Dialogue_Menu(const PointF& position, float width, std::vector<std::string> dialogue)
	:UIScene(RectF(0, 0, 50, 40))
{
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground = new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255,255,255,255));
	_blocking = true;
	_character = nullptr;
	battle_dialogue = dialogue;
	dialogue_counter = 1;
	words = nullptr;
	on = 3;
	sound = false;
	hero_sound = "";
	monster_sound = "";
	victory = false;
	addText(battle_dialogue[0]);
}

Dialogue_Menu::Dialogue_Menu(const PointF& position, float width, Chest* chest)
	:UIScene(RectF(0, 0, 50, 40)) 
{
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground = new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255, 255, 255, 255));
	_blocking = true;
	_character = nullptr;
	battle_dialogue = {};
	dialogue_counter = 1;
	words = nullptr;
	on = 1;
	sound = false;
	hero_sound = "";
	monster_sound = "";
	victory = false;
	addText(chest->getDialogue());
}
Dialogue_Menu::Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack)
	:UIScene(RectF(0, 0, 50, 40))
{
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground = new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255, 255, 255, 255));
	_blocking = true;
	_character = nullptr;
	dialogue_counter = 1;
	monster_sound = "";
	hero_sound = "";
	victory = false;
		if (monster_attack->getSpell() == false && monster_attack->getPhysical() == true) {
			monster_sound = "38 Dragon Quest 1 - Receive Damage (2)";
			hero_sound = "34 Dragon Quest 1 - Hit";
			if (hero_dead)
				battle_dialogue = { "Hero attacks!" ,monster->getName() + " attacks!","You lost!" };
			else if (monster_dead) {
				victory = true;
				std::string drop = std::to_string(monster->getMoney());
				battle_dialogue = { "Hero attacks!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
			}
			else 
				battle_dialogue = { "Hero attacks!" ,monster->getName() + " attacks!" };
			
		}
		else if (monster_attack->getSpell() == true && monster_attack->getPhysical() == true) {
			monster_sound = "46 Dragon Quest 1 - Breathe Fire";
			hero_sound = "34 Dragon Quest 1 - Hit";

			if (hero_dead)
				battle_dialogue = { "Hero attacks!" ,monster->getName() + " attacks you" ,"with "+ monster_attack->getName() + " !","You lost !"};
			else if (monster_dead) {
				victory = true;
				std::string drop = std::to_string(monster->getMoney());
				battle_dialogue = { "Hero attacks!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
			}
			else
				battle_dialogue = { "Hero attacks!" ,monster->getName() + " attacks you" ,"with "+ monster_attack->getName() + " !"};
		}
		else {
			monster_sound = "43 Dragon Quest 1 - Cast A Spell";
			hero_sound = "34 Dragon Quest 1 - Hit";
			if (monster_dead) {
				victory = true;
				std::string drop = std::to_string(monster->getMoney());
				battle_dialogue = { "Hero attacks!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins"};
			}
			else
				battle_dialogue = { "Hero attacks!",monster->getName() + "uses a spell that makes " , monster_attack->getName() + " !" };
		}
	words = nullptr;
	on = 2;
	addText(battle_dialogue[0]);
	Audio::instance()->playSound(hero_sound);
}
Dialogue_Menu::Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack, Spell* spell)
	:UIScene(RectF(0, 0, 50, 40)) {
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground = new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255, 255, 255, 255));
	_blocking = true;
	_character = nullptr;
	dialogue_counter = 1;
	monster_sound = "";
	hero_sound = "";
	victory = false;
	if (monster_attack->getSpell() == false && monster_attack->getPhysical() == true) {
		monster_sound = "38 Dragon Quest 1 - Receive Damage (2)";
		hero_sound = "43 Dragon Quest 1 - Cast A Spell";
		if (hero_dead)
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell" ,monster->getName() + " attacks!","You lost!" };
		else if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell" ,monster->getName() + " attacks!" };

	}
	else if (monster_attack->getSpell() == true && monster_attack->getPhysical() == true) {
		monster_sound = "46 Dragon Quest 1 - Breathe Fire";
		hero_sound = "43 Dragon Quest 1 - Cast A Spell";

		if (hero_dead)
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell" ,monster->getName() + " attacks you with " + monster_attack->getName() + " !","You lost !" };
		else if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell" ,monster->getName() + " attacks you with " + monster_attack->getName() + " !" };
	}
	else {
		monster_sound = "43 Dragon Quest 1 - Cast A Spell";
		hero_sound = "43 Dragon Quest 1 - Cast A Spell";
		if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero casts the " + spell->getName() + " spell",monster->getName() + "uses a spell that makes " + monster_attack->getName() + " !" };
	}
	words = nullptr;
	on = 2;
	addText(battle_dialogue[0]);
	Audio::instance()->playSound(hero_sound);

}
Dialogue_Menu::Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack, Item* item)
	:UIScene(RectF(0, 0, 50, 40)) {
	DialogueRect = { position.x, position.y, width, 2 };
	DialogueBackground = new RenderableObject(this, DialogueRect, Color(0, 0, 0, 255));
	DialogueBackground->setBorderColor(Color(255, 255, 255, 255));
	_blocking = true;
	_character = nullptr;
	dialogue_counter = 1;
	monster_sound = "";
	hero_sound = "";
	victory = false;
	if (monster_attack->getSpell() == false && monster_attack->getPhysical() == true) {
		monster_sound = "38 Dragon Quest 1 - Receive Damage (2)";
		hero_sound = "44 Dragon Quest 1 - Open Treasure";
		if (hero_dead)
			battle_dialogue = { "Hero uses "+item->getName()+ "!",monster->getName() + " attacks!","You lost!"};
		else if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero uses " + item->getName() + "!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero uses " + item->getName() + "!" ,monster->getName() + " attacks!" };

	}
	else if (monster_attack->getSpell() == true && monster_attack->getPhysical() == true) {
		monster_sound = "46 Dragon Quest 1 - Breathe Fire";
		hero_sound = "44 Dragon Quest 1 - Open Treasure";

		if (hero_dead)
			battle_dialogue = { "Hero uses " + item->getName() + "!" ,monster->getName() + " attacks you with " + monster_attack->getName() + " !","You lost !" };
		else if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero uses " + item->getName() + "!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero uses " + item->getName() + "!" ,monster->getName() + " attacks you with " + monster_attack->getName() + " !" };
	}
	else {
		monster_sound = "43 Dragon Quest 1 - Cast A Spell";
		hero_sound = "44 Dragon Quest 1 - Open Treasure";
		if (monster_dead) {
			victory = true;
			std::string drop = std::to_string(monster->getMoney());
			battle_dialogue = { "Hero uses " + item->getName() + "!",monster->getName() + " defeated!","The enemy dropped: " + drop + " coins" };
		}
		else
			battle_dialogue = { "Hero uses " + item->getName() + "!",monster->getName() + "uses a spell that makes " + monster_attack->getName() + " !" };
	}
	words = nullptr;
	on = 2;
	addText(battle_dialogue[0]);
	Audio::instance()->playSound(hero_sound);

}
void Dialogue_Menu::event(SDL_Event& evt) 
{
	UIScene::event(evt);
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.scancode == SDL_SCANCODE_A) {
			if (on == 0) {
				if (_character != nullptr) {
					if (dialogue_counter < _character->getDialogue().size()) {
						words->setSprite(SpriteFactory::instance()->getText(_character->getDialogue()[dialogue_counter], { 0.4f, 0.4f }));
						dialogue_counter++;
					}
					else
						Game::instance()->popSceneLater();
				}
				else {
					if (dialogue_counter < battle_dialogue.size()) {
						words->setSprite(SpriteFactory::instance()->getText(battle_dialogue[dialogue_counter], { 0.4f, 0.4f }));
						dialogue_counter++;
					}
				}
			}
		
			else if (on == 2) {
				if (dialogue_counter < battle_dialogue.size()) {
					words->setSprite(SpriteFactory::instance()->getText(battle_dialogue[dialogue_counter], { 0.4f, 0.4f }));
					dialogue_counter++;
					if (!victory && dialogue_counter==2)
						Audio::instance()->playSound(monster_sound);
				}
				else {
					Game::instance()->popSceneLater();
					Game::instance()->popSceneLater();
				}
			}
			else if (on == 3) {
				if (dialogue_counter < battle_dialogue.size()) {
					words->setSprite(SpriteFactory::instance()->getText(battle_dialogue[dialogue_counter], { 0.4f, 0.4f }));
					dialogue_counter++;
				}
				else
					Game::instance()->popSceneLater();
			}
			else 
				Game::instance()->popSceneLater();
		}
	}
}
void Dialogue_Menu::addText(const std::string row) {
	words=new RenderableObject(this, RectF(this->DialogueRect.left()+0.5, 10.7f, 12, 1), SpriteFactory::instance()->getText(row, {0.4f, 0.4f}));
}
Dialogue_Menu* Dialogue_Menu::menu(Npc* cha) {
	Dialogue_Menu* menu = new Dialogue_Menu({ 1.5,10 }, 13, cha);
	return menu;
}
Dialogue_Menu* Dialogue_Menu::menu(Chest* che) {
	Dialogue_Menu* menu = new Dialogue_Menu({ 1.5,10 }, 13, che);
	return menu;
}
Dialogue_Menu* Dialogue_Menu::menu(std::vector<std::string> dialogue) {
	Dialogue_Menu* menu = new Dialogue_Menu({ 1.5,10 }, 13, dialogue);
	return menu;
}
Dialogue_Menu* Dialogue_Menu::menu(const PointF& pos ,std::vector<std::string> dialogue) {
	Dialogue_Menu* menu = new Dialogue_Menu(pos, 13, dialogue);
	menu->removeBorder();
	return menu;
}
Dialogue_Menu* Dialogue_Menu::commands() {
	std::vector<std::string> dialogue = { "Bla","Bla" };
	Dialogue_Menu* menu = Dialogue_Menu::menu(dialogue);
	

	//commads visualtization

	new RenderableObject(menu, RectF(0, 0, 500, 500), Color(0, 0, 0, 255));
	//arrow up
	RenderableObject* up = new RenderableObject(menu, RectF(2.5, 1, 1.4, 1.4), Color(0, 0, 0, 255));
	up->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.7, 1.2, 1, 1), SpriteFactory::instance()->getText("^"));
	RenderableObject* uptext = new RenderableObject(menu, RectF(4.1, 1.5, 2.8, 1), SpriteFactory::instance()->getText("Move up", { 0.4,0.4 }));
	//arrow down
	RenderableObject* down = new RenderableObject(menu, RectF(8.5, 1, 1.4, 1.4), Color(0, 0, 0, 255));
	down->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(8.7, 1.3, 1.4, 1.4), SpriteFactory::instance()->getText("@"));
	RenderableObject* downtext = new RenderableObject(menu, RectF(10.1, 1.5, 3.6, 1), SpriteFactory::instance()->getText("Move down", { 0.4,0.4 }));
	//arrow left
	RenderableObject* left = new RenderableObject(menu, RectF(2.5, 3, 1.4, 1.4), Color(0, 0, 0, 255));
	left->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.6, 3.2, 1, 1), SpriteFactory::instance()->getText("<"));
	RenderableObject* lefttext = new RenderableObject(menu, RectF(4.1, 3.5, 3.6, 1), SpriteFactory::instance()->getText("Move left", { 0.4,0.4 }));
	//arrow right
	RenderableObject* right = new RenderableObject(menu, RectF(8.5, 3, 1.4, 1.4), Color(0, 0, 0, 255));
	right->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(8.7, 3.2, 1.4, 1.4), SpriteFactory::instance()->getText(">"));
	RenderableObject* righttext = new RenderableObject(menu, RectF(10.1, 3.5, 4, 1), SpriteFactory::instance()->getText("Move right", { 0.4,0.4 }));
	//a botton
	RenderableObject* a = new RenderableObject(menu, RectF(2.5, 5, 1.4, 1.4), Color(0, 0, 0, 255));
	a->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.85, 5.35, 0.7, 0.7), SpriteFactory::instance()->getText("A",{0.7,0.7}));
	RenderableObject* atext = new RenderableObject(menu, RectF(4.1, 5.5, 7.2, 1), SpriteFactory::instance()->getText("Interact with NPCs", { 0.4,0.4 }));
	//s botton
	RenderableObject* s = new RenderableObject(menu, RectF(2.5, 7, 1.4, 1.4), Color(0, 0, 0, 255));
	s->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.85, 7.35, 0.7, 0.7), SpriteFactory::instance()->getText("S", { 0.7,0.7 }));
	RenderableObject* stext = new RenderableObject(menu, RectF(4.1, 7.5, 10.4, 1), SpriteFactory::instance()->getText("Interact with doors/chests", { 0.4,0.4 }));
	//z botton
	RenderableObject* z = new RenderableObject(menu, RectF(2.5, 9, 1.4, 1.4), Color(0, 0, 0, 255));
	z->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.85, 9.35, 0.7, 0.7), SpriteFactory::instance()->getText("Z", { 0.7,0.7 }));
	RenderableObject* ztext = new RenderableObject(menu, RectF(4.1, 9.5, 6.8, 1), SpriteFactory::instance()->getText("Pop up pause menu", { 0.4,0.4 }));
	//enter botton
	RenderableObject* enter = new RenderableObject(menu, RectF(2.5, 11, 1.8, 1.4), Color(0, 0, 0, 255));
	enter->setBorderColor(Color(255, 255, 255, 255));
	new RenderableObject(menu, RectF(2.7, 11.6, 1.5, 1), SpriteFactory::instance()->getText("Enter", { 0.3,0.3 }));
	RenderableObject* entertext = new RenderableObject(menu, RectF(4.5, 11.5, 7.6, 1), SpriteFactory::instance()->getText("Select inside menus", { 0.4,0.4 }));
	//text
	RenderableObject* text = new RenderableObject(menu, RectF(2.5, 13, 11.6, 1), SpriteFactory::instance()->getText("To exit commands press A twice", { 0.4,0.4 }));
	return menu;
}
Dialogue_Menu *Dialogue_Menu::tips() {
	std::vector<std::string> dialogue = { "Bla","Bla" };
	Dialogue_Menu* menu = Dialogue_Menu::menu(dialogue);

	new RenderableObject(menu, RectF(0, 0, 500, 500), Color(0, 0, 0, 255));
	RenderableObject* item_merchant = new RenderableObject(menu, RectF(2.5, 5, 1.4, 1.4), SpriteFactory::instance()->get("itemseller_right"));
	RenderableObject* text1 = new RenderableObject(menu, RectF(4.1, 5, 12, 1), SpriteFactory::instance()->getText("This merchant sells very useful", { 0.3,0.3 }));
	RenderableObject* text2 = new RenderableObject(menu, RectF(4.1, 5.5, 12, 1), SpriteFactory::instance()->getText("items to help the hero such as", { 0.3,0.3 }));
	RenderableObject* text3= new RenderableObject(menu, RectF(4.1, 6, 12, 1), SpriteFactory::instance()->getText("weapons and very treaky tools", { 0.3,0.3 }));

	RenderableObject* spell_merchant = new RenderableObject(menu, RectF(2.5, 8, 1.4, 1.4), SpriteFactory::instance()->get("spellseller_right"));
	RenderableObject* text4 = new RenderableObject(menu, RectF(4.1, 8, 12, 1), SpriteFactory::instance()->getText("This merchant sells very useful", { 0.3,0.3 }));
	RenderableObject* text5 = new RenderableObject(menu, RectF(4.1, 8.5, 12, 1), SpriteFactory::instance()->getText("spells to help you out in your", { 0.3,0.3 }));
	RenderableObject* text6 = new RenderableObject(menu, RectF(4.1, 9, 12, 1), SpriteFactory::instance()->getText("adventure", { 0.3,0.3 }));

	new RenderableObject(menu, RectF(0.5, 2, 20.8, 1), SpriteFactory::instance()->getText("Make sure to pay them a visit during your journey!",{0.3,0.3}));
	new RenderableObject(menu, RectF(4, 13, 11.6, 1), SpriteFactory::instance()->getText("To exit tips press A twice", { 0.3,0.3 }));

	return menu;
}