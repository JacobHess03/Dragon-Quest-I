#pragma once
#include "UIScene.h"
#include "RenderableObject.h"
#include "Npc.h"
#include "Chest.h"

namespace agp
{
	class Dialogue_Menu;
}

//Dialogue Menu
class agp::Dialogue_Menu : public UIScene {
private:
	int dialogue_counter;
	Npc* _character;
	std::vector<std::string> battle_dialogue;
	RectF DialogueRect;
	RenderableObject* DialogueBackground;
	RenderableObject* words;
	int on;
	bool sound;
	std::string monster_sound;
	std::string hero_sound;
	bool victory;
public:
	Dialogue_Menu(const PointF& position, float width, Npc* character);
	Dialogue_Menu(const PointF& position, float width, std::vector<std::string> dialogue);
	Dialogue_Menu(const PointF& position, float width, Chest* chest);
	Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack);
	Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack,Spell* spell);
	Dialogue_Menu(const PointF& position, float width, Monster* monster, bool monster_dead, bool hero_dead, Attack* monster_attack, Item* item);


	virtual ~Dialogue_Menu() {};
	virtual void event(SDL_Event& evt) override;
	void addText(const std::string row);
	void removeBorder() { DialogueBackground->setBorderColor(Color(0, 0, 0, 0)); }



		static Dialogue_Menu* menu(Npc* cha);
		static Dialogue_Menu* menu(Chest* che);
		static Dialogue_Menu* menu(std::vector<std::string>dialogue);
		static Dialogue_Menu* menu(const PointF& pos, std::vector<std::string>dialogue);
		static Dialogue_Menu* commands();
		static Dialogue_Menu* tips();
};