// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "SpriteFactory.h"
#include "SDL_image.h"
#include "graphicsUtils.h"
#include "Window.h"
#include "AnimatedSprite.h"
#include "TiledSprite.h"
#include "FilledSprite.h"
#include "Game.h"
#include <iostream>

using namespace agp;

// utility function: move rect within sprite
RectI moveBy(RectI srcRect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	RectI dstRect = srcRect;
	dstRect.pos = { srcRect.pos.x + x * dx + x * border_x, srcRect.pos.y + y * dy + y * border_y };
	return dstRect;
}

// utility function: load texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filepath, const Color& mask = {0,0,0,0})
{
	// load from file
	SDL_Surface* surf = IMG_Load(filepath.c_str());
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s: %s", filepath.c_str(), SDL_GetError());
		return nullptr;
	}

	// set transparent color
	if(mask.a)
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, mask.r, mask.g, mask.b));

	// create texture from surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if (!tex)
	{
		SDL_Log("Failed to convert surface to texture for %s: %s", filepath.c_str(), SDL_GetError());
		return nullptr;
	}

	return tex;
}

SpriteFactory* SpriteFactory::instance()
{
	static SpriteFactory uniqueInstance;
	return &uniqueInstance;
}

SpriteFactory::SpriteFactory()
{
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return;
	}

	SDL_Renderer* renderer = Game::instance()->window()->renderer();
	_spriteSheets["hero"] = loadTexture(renderer, "Sprites/Characters.png");
	_spriteSheets["font"] = loadTexture(renderer, "Sprites/font.png", { 255, 255, 255 });
	_spriteSheets["hud"] = loadTexture(renderer, "Sprites/sorted font 2_2.png");
	_spriteSheets["castle"] = loadTexture(renderer, "Maps/Radatome Castle.png");
	_spriteSheets["world"] = loadTexture(renderer, "Maps/World Map.png");
	_spriteSheets["monsters"] = loadTexture(renderer, "Sprites/Monsters.png", { 255,255,255 });
	_spriteSheets["dark_castle"] = loadTexture(renderer, "Maps/Dragonlord_s Castle.png", { 0,0,0 });
	_spriteSheets["Dragonlord_s Castle"] = loadTexture(renderer, "Maps/Dragonlord_s Castle.png");
	_spriteSheets["background"] = loadTexture(renderer, "Maps/Battle Backgrounds.png");
	_spriteSheets["Radatome_Caste_Scheme"] = loadTexture(renderer, "Maps/Radatome Castle Scheme.png");
	_spriteSheets["Logo"] = loadTexture(renderer, "Sprites/Logo animation.png", { 255,255,255 });
	_spriteSheets["Font"]= loadTexture(renderer, "Sprites/sorted font 2.png");
	//mappa per la sprite della porta 
	_spriteSheets["Radatome_Caste_Scheme"] = loadTexture(renderer, "Maps/Radatome Castle Scheme.png");
	_spriteSheets["Doors"] = loadTexture(renderer, "Sprites/Doors.png");


}

// anchors

//kings_room
static RectI kings_room(550, 225, 240, 320);
//characters
static RectI hero(0, 0, 18, 17);
//monsters
static RectI green_dragon(0, 0, 54, 61);
static RectI half_green_dragon(0, 0, 27, 61);
static RectI purple_slug(0, 62, 46, 46);
static RectI yellow_golem(232, 114, 60, 60);
static RectI axe_warrior(54, 176, 60, 60);
static RectI wizard(0, 300, 50, 50);
static RectI dragonlord(230, 353, 65, 60);
static RectI true_dragonlord(0, 420, 82, 114);
//font
static RectI zero(8, 8, 7, 7);
static RectI hud_minusc_letter(0, 100, 60, 60);
static RectI hud_maiusc_letter(0, 7, 60, 60);
static RectI hud_number(0, 195, 60, 60);
//kings room layer fix
static RectI arch(653, 448, 33, 9);
static RectI col(631, 400, 12, 22);
//overworld
static RectI world(640, 710, 600, 535);
//castle
static RectI radatome_castle(16, 48, 496, 496);
//level 6
static RectI dragonlord_castle_s(890, 890, 350, 510);
//level 1
static RectI level_1(107, 219, 416, 447);
//level8
static RectI level_8(2066, 813, 527, 639);
//col in level 8
static RectI col_lev_8(2242, 893, 16, 26);
//bordo menu
static RectI borderMenu(1020, 397, 60, 60);
//fight background
static RectI background(516,0,130,113);

//logo
static RectI logo(6, 6, 217, 71);
//door radatome castle
static RectI radatomecastle_door(712, 297, 32, 25);
//door radatome castle 2
static RectI radatomecastle_door2(59, 16, 16, 16);
//door dragonlord_s castle
static RectI level_1_door(0, 0, 32, 32);
//door level 8
static RectI level_8_door(91, 0, 14, 32);




Sprite* SpriteFactory::get(const std::string& id)
{
	std::vector< RectI> rects;

	// king's room
	if (id == "kings_room")
		return new Sprite(_spriteSheets["castle"], kings_room);
	else if (id == "arch")
		return new Sprite(_spriteSheets["castle"], arch);
	else if (id == "colomn")
		return new Sprite(_spriteSheets["castle"], col);
	// overworld
	else if (id == "overworld")
		return new Sprite(_spriteSheets["world"], world);
	//castle
	else if (id == "radatome_castle")
		return new Sprite(_spriteSheets["castle"], radatome_castle);
	//dungeon level
	else if (id == "dragonlord_castle_s")
		return new Sprite(_spriteSheets["dark_castle"], dragonlord_castle_s);
	//dungeon entrance
	else if (id == "level_1")
		return new Sprite(_spriteSheets["Dragonlord_s Castle"], level_1);
	//dungeon final room
	else if (id == "level_8")
		return new Sprite(_spriteSheets["Dragonlord_s Castle"], level_8);
	else if (id == "col_lev_8")
		return new Sprite(_spriteSheets["Dragonlord_s Castle"], col_lev_8);
	//chest sprites
	else if (id == "chest_1")
		return new Sprite(_spriteSheets["hero"], moveBy(hero, 5, 11, 29, 29));
	else if (id == "chest_2")
		return new Sprite(_spriteSheets["hero"], moveBy(hero, 6, 11, 29, 29));
	//monsters
	else if (id == "yellow_ghost")
		return new Sprite(_spriteSheets["monsters"], moveBy(green_dragon, 0, 2, 54, 56));
	else if (id == "yellow_ghost_half")
		return new Sprite(_spriteSheets["monsters"], moveBy(half_green_dragon, 0, 2, 54, 56));
	else if (id == "yellow_golem")
		return new Sprite(_spriteSheets["monsters"], yellow_golem);
	else if (id == "blue_slime")
		return new Sprite(_spriteSheets["monsters"], moveBy(green_dragon, 1, 1, 234, 234, 3, 0));
	else if (id == "red_wizard")
		return new Sprite(_spriteSheets["monsters"], moveBy(wizard, 1, 0, 60, 60));
	else if (id == "yellow_wizard")
		return new Sprite(_spriteSheets["monsters"], moveBy(wizard, 2, 0, 60, 60));
	else if (id == "yellow_rat")
		return new Sprite(_spriteSheets["monsters"], moveBy(green_dragon, 1, 1, 355, 289));
	else if (id == "dragonlord")
		return new Sprite(_spriteSheets["monsters"], dragonlord);
	else if (id == "true_dragonlord_standing")
		return new Sprite(_spriteSheets["monsters"], true_dragonlord);
	//background
	else if (id == "slime_background")
		return new Sprite(_spriteSheets["background"], background);
	else if (id == "dungeon_background")
		return new Sprite(_spriteSheets["background"], moveBy(background,0, 1, 0, 114));
	else if (id =="rock_background")
		return new Sprite(_spriteSheets["background"], moveBy(background, -4, 2, 129, 114));
	else if(id=="final_background")
		return new Sprite(_spriteSheets["background"], moveBy(background, -3, 2, 129, 114, - 0.5, 0));
	//door sprits
	else if (id == "radatomecastle_door")
		return new Sprite(_spriteSheets["Radatome_Caste_Scheme"], radatomecastle_door);
	else if (id == "radatomecastle_door2")
		return new Sprite(_spriteSheets["Doors"], radatomecastle_door2);
	else if (id == "level_1_door")
		return new Sprite(_spriteSheets["Doors"], level_1_door);
	else if (id == "level_8_door")
		return new Sprite(_spriteSheets["Doors"], level_8_door);
	//main menu
	else if (id == "logo") {
		return new Sprite(_spriteSheets["Logo"], logo);
	}
	else if (id == "slime_token") {
		return new Sprite(_spriteSheets["Font"], moveBy(hud_number, 10, 2, 60, 70, 8, 33));
	}

	


	
	// animated sprites

	//hero
	if (id == "walk_right")
	{
		rects.push_back(moveBy(hero, 3, 0, 29, 29));
		rects.push_back(moveBy(hero, 3, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 5);
	}
	else if (id == "walk_left") {
		rects.push_back(moveBy(hero, 1, 0, 29, 29));
		rects.push_back(moveBy(hero, 1, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 5);
	}
	else if (id == "walk_up") {
		rects.push_back(moveBy(hero, 2, 0, 29, 29));
		rects.push_back(moveBy(hero, 2, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 5);
	}
	else if (id == "walk_down") {
		rects.push_back(hero);
		rects.push_back(moveBy(hero, 0, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 5);
	}
	//others
	else if (id == "counselor_down") {
		rects.push_back(moveBy(hero, 4, 4, 29, 29));
		rects.push_back(moveBy(hero, 4, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "counselor_left") {
		rects.push_back(moveBy(hero, 5, 4, 29, 29));
		rects.push_back(moveBy(hero, 5, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "counselor_up") {
		rects.push_back(moveBy(hero, 6, 4, 29, 29));
		rects.push_back(moveBy(hero, 6, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "counselor_right") {
		rects.push_back(moveBy(hero, 7, 4, 29, 29));
		rects.push_back(moveBy(hero, 7, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "guard_down") {
		rects.push_back(moveBy(hero, 0, 6, 29, 29));
		rects.push_back(moveBy(hero, 0, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "guard_left") {
		rects.push_back(moveBy(hero, 1, 6, 29, 29));
		rects.push_back(moveBy(hero, 1, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "guard_up") {
		rects.push_back(moveBy(hero, 2, 6, 29, 29));
		rects.push_back(moveBy(hero, 2, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "guard_right") {
		rects.push_back(moveBy(hero, 3, 6, 29, 29));
		rects.push_back(moveBy(hero, 3, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "king_standing") {
		rects.push_back(moveBy(hero, 11, 10, 29, 29));
		rects.push_back(moveBy(hero, 11, 11, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "knight_down") {
		rects.push_back(moveBy(hero, 4, 6, 29, 29));
		rects.push_back(moveBy(hero, 4, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "knight_left") {
		rects.push_back(moveBy(hero, 5, 6, 29, 29));
		rects.push_back(moveBy(hero, 5, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "knight_up") {
		rects.push_back(moveBy(hero, 6, 6, 29, 29));
		rects.push_back(moveBy(hero, 6, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "knight_right") {
		rects.push_back(moveBy(hero, 7, 6, 29, 29));
		rects.push_back(moveBy(hero, 7, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castlegirl_down") {
		rects.push_back(moveBy(hero, 8, 6, 29, 29));
		rects.push_back(moveBy(hero, 8, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castlegirl_left") {
		rects.push_back(moveBy(hero, 9, 6, 29, 29));
		rects.push_back(moveBy(hero, 9, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castlegirl_up") {
		rects.push_back(moveBy(hero, 10, 6, 29, 29));
		rects.push_back(moveBy(hero, 10, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castlegirl_right") {
		rects.push_back(moveBy(hero, 11, 6, 29, 29));
		rects.push_back(moveBy(hero, 11, 7, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "townboy_down") {
		rects.push_back(moveBy(hero, 0, 8, 29, 29));
		rects.push_back(moveBy(hero, 0, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "townboy_left") {
		rects.push_back(moveBy(hero, 1, 8, 29, 29));
		rects.push_back(moveBy(hero, 1, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "townboy_up") {
		rects.push_back(moveBy(hero, 2, 8, 29, 29));
		rects.push_back(moveBy(hero, 2, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "townboy_right") {
		rects.push_back(moveBy(hero, 3, 8, 29, 29));
		rects.push_back(moveBy(hero, 3, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "towngirl_down") {
		rects.push_back(moveBy(hero, 4, 8, 29, 29));
		rects.push_back(moveBy(hero, 4, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "towngirl_left") {
		rects.push_back(moveBy(hero, 5, 8, 29, 29));
		rects.push_back(moveBy(hero, 5, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "towngirl_up") {
		rects.push_back(moveBy(hero, 6, 8, 29, 29));
		rects.push_back(moveBy(hero, 6, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "towngirl_right") {
		rects.push_back(moveBy(hero, 7, 8, 29, 29));
		rects.push_back(moveBy(hero, 7, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castleboy_down") {
		rects.push_back(moveBy(hero, 8, 8, 29, 29));
		rects.push_back(moveBy(hero, 8, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castleboy_left") {
		rects.push_back(moveBy(hero, 9, 8, 29, 29));
		rects.push_back(moveBy(hero, 9, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castleboy_up") {
		rects.push_back(moveBy(hero, 10, 8, 29, 29));
		rects.push_back(moveBy(hero, 10, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "castleboy_right") {
		rects.push_back(moveBy(hero, 11, 8, 29, 29));
		rects.push_back(moveBy(hero, 11, 9, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}

	else if (id == "spellseller_down") {
		rects.push_back(moveBy(hero, 0, 2, 29, 29));
		rects.push_back(moveBy(hero, 0, 3, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "spellseller_left") {
		rects.push_back(moveBy(hero, 1, 2, 29, 29));
		rects.push_back(moveBy(hero, 1, 3, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "spellseller_up") {
		rects.push_back(moveBy(hero, 2, 2, 29, 29));
		rects.push_back(moveBy(hero, 2, 3, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "spellseller_right") {
		rects.push_back(moveBy(hero, 3, 2, 29, 29));
		rects.push_back(moveBy(hero, 3, 3, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "itemseller_down")
	{
		rects.push_back(moveBy(hero, 0, 4, 29, 29));
		rects.push_back(moveBy(hero, 0, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "itemseller_left")
	{
		rects.push_back(moveBy(hero, 1, 4, 29, 29));
		rects.push_back(moveBy(hero, 1, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "itemseller_up")
	{
		rects.push_back(moveBy(hero, 2, 4, 29, 29));
		rects.push_back(moveBy(hero, 2, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "itemseller_right")
	{
		rects.push_back(moveBy(hero, 3, 4, 29, 29));
		rects.push_back(moveBy(hero, 3, 5, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}

	else if (id == "hero_princess_down") {
		rects.push_back(moveBy(hero, 4, 0, 29, 29));
		rects.push_back(moveBy(hero, 4, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "hero_princess_left") {
		rects.push_back(moveBy(hero, 5, 0, 29, 29));
		rects.push_back(moveBy(hero, 5, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "hero_princess_up") {
		rects.push_back(moveBy(hero, 6, 0, 29, 29));
		rects.push_back(moveBy(hero, 6, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "hero_princess_right") {
		rects.push_back(moveBy(hero, 7, 0, 29, 29));
		rects.push_back(moveBy(hero, 7, 1, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}

	else if (id == "dragonlord_standing") {
		rects.push_back(moveBy(hero, 5, 10, 29, 29));
		rects.push_back(moveBy(hero, 6, 10, 29, 29));
		return new AnimatedSprite(_spriteSheets["hero"], rects, 4);
	}
	else if (id == "dragon_fire")
	{
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(true_dragonlord);
		rects.push_back(moveBy(true_dragonlord, 1, 0, 85, 7));
		rects.push_back(moveBy(true_dragonlord, 1, 0, 166, 7));
		rects.push_back(moveBy(true_dragonlord, 1, 0, 248, 7));
		rects.push_back(moveBy(true_dragonlord, 1, 0, 330, 7));
		rects.push_back(moveBy(true_dragonlord, 0, 1, 85, 142));
		rects.push_back(moveBy(true_dragonlord, 1, 1, 83, 142));
		rects.push_back(moveBy(true_dragonlord, 1, 1, 165, 142));
		rects.push_back(moveBy(true_dragonlord, 1, 1, 250, 142));
		return new AnimatedSprite(_spriteSheets["monsters"], rects, 10);
	}
	else if (id=="logo_animation"){
		rects.push_back(logo);
		rects.push_back(moveBy(logo,1,1,224,1));
		rects.push_back(moveBy(logo, 1, 1, 448, 1));
		rects.push_back(moveBy(logo, 1, 1, 2, 83));
		rects.push_back(moveBy(logo, 1, 1, 448, 1));
		rects.push_back(moveBy(logo, 1, 1, 224, 1));
		rects.push_back(logo);
		rects.push_back(logo);
		rects.push_back(logo);
		rects.push_back(logo);
		rects.push_back(logo);
		rects.push_back(logo);
		rects.push_back(logo);
		return new AnimatedSprite(_spriteSheets["Logo"], rects, 8);


	}
	else
	{
		std::cerr << "Cannot find sprite \"" << id << "\"\n";
		return nullptr;
	}
}

Sprite* SpriteFactory::getText(std::string text, const Vec2Df& size, int fillN, char fillChar, bool enabled)
{
	std::vector< RectI> tiles;

	if (fillN)
		while (text.size() != fillN)
			text = fillChar + text;

	RectI& minusc_letter_anchor = hud_minusc_letter;
	RectI& maiusc_letter_anchor = hud_maiusc_letter;
	RectI& number_anchor = hud_number;

	for (auto& c : text)
	{
		if (isdigit(c))
			tiles.push_back(moveBy(number_anchor, c - '0', 0, 60, 60, 8, 8));

		if (isalpha(c))
			if (isupper(c))
				tiles.push_back(moveBy(maiusc_letter_anchor, c - 'A', 0, 60, 60, 8, 8));
			else
				tiles.push_back(moveBy(minusc_letter_anchor, c - 'a', 0, 60, 60, 8, 8));
		else if (c == '.')
			tiles.push_back(moveBy(number_anchor, 11, 0, 60, 60, 8, 8));
		else if (c == ',')
			tiles.push_back(moveBy(number_anchor, 12, 0, 60, 60, 8, 8));
		else if (c == '?')
			tiles.push_back(moveBy(number_anchor, 18, 0, 60, 60, 8, 8));
		else if (c == '!')
			tiles.push_back(moveBy(number_anchor, 19, 0, 60, 60, 8, 8));
		else if (c == '@')
			tiles.push_back(moveBy(number_anchor, 1, 2, 60, 60, 8, 33));
		else if (c == '_')
			tiles.push_back(moveBy(number_anchor, 21, 0, 60, 60, 8, 8));
		else if (c == '*')
			tiles.push_back(moveBy(number_anchor, 22, 0, 60, 60, 8, 8));
		else if (c == '#')
			tiles.push_back(moveBy(number_anchor, 23, 0, 60, 60, 8, 8));
		else if (c == '$')
			tiles.push_back(moveBy(number_anchor, 24, 0, 60, 60, 8, 8));
		else if (c == '%')
			tiles.push_back(moveBy(number_anchor, 25, 0, 60, 60, 8, 8));
		else if (c == '&')
			tiles.push_back(moveBy(number_anchor, 0, 1, 60, 60, 8, 33));
		else if (c == '(')
			tiles.push_back(moveBy(number_anchor, 1, 1, 60, 60, 8, 33));
		else if (c == ')')
			tiles.push_back(moveBy(number_anchor, 2, 1, 60, 60, 8, 33));
		else if (c == '+')
			tiles.push_back(moveBy(number_anchor, 3, 1, 60, 60, 8, 33));
		else if (c == '-')
			tiles.push_back(moveBy(number_anchor, 4, 1, 60, 60, 8, 33));
		else if (c == '/')
			tiles.push_back(moveBy(number_anchor, 5, 1, 60, 60, 8, 33));
		else if (c == ':')
			tiles.push_back(moveBy(number_anchor, 6, 1, 60, 60, 8, 33));
		else if (c == ';')
			tiles.push_back(moveBy(number_anchor, 7, 1, 60, 60, 8, 33));
		else if (c == '<')
			tiles.push_back(moveBy(number_anchor, 8, 1, 60, 70, 8, 33));
		else if (c == '=')
			tiles.push_back(moveBy(number_anchor, 9, 1, 60, 60, 8, 33));
		else if (c == '>')
			tiles.push_back(moveBy(number_anchor, 10, 1, 60, 70, 8, 33));
		else if (c == '[')
			tiles.push_back(moveBy(number_anchor, 11, 1, 60, 60, 8, 33));
		else if (c == ']')
			tiles.push_back(moveBy(number_anchor, 13, 1, 60, 60, 8, 33));
		else if (c == '^')
			tiles.push_back(moveBy(number_anchor, 14, 1, 60, 60, 8, 33));
		else if (c == '{')
			tiles.push_back(moveBy(number_anchor, 16, 1, 60, 60, 8, 33));
		else if (c == '|')
			tiles.push_back(moveBy(number_anchor, 17, 1, 60, 60, 8, 33));
		else if (c == '}')
			tiles.push_back(moveBy(number_anchor, 18, 1, 60, 60, 8, 33));
		/**/
		else if (c==' ')
			tiles.push_back(moveBy(hud_maiusc_letter, 30, 60, 8, 8));	// empty space
	}

	return new TiledSprite(_spriteSheets["hud"], tiles, size);
}
Sprite* SpriteFactory::getMenu(const Point& sizeMenu, const Vec2Df& size) {

	std::vector< RectI> tiles;


	//angolo sx alto
	tiles.push_back(moveBy(borderMenu, 1, 0, 60, 60, 8, 8));
	//bordo superiore
	for (int i = 2; i < sizeMenu.x; i++) {
		tiles.push_back(borderMenu);

	}
	//angolo dx alto
	tiles.push_back(moveBy(borderMenu, 4, 0, 60, 60, 8, 8));

	//bordi laterali
	for (int i = 2; i < sizeMenu.y; i++) {
		tiles.push_back(moveBy(borderMenu, 2, 0, 60, 60, 8, 8));

		for (int j = 2; j < sizeMenu.x; j++)
			tiles.push_back(moveBy(borderMenu, 0, 1, 60, 60, 8, 8));

		tiles.push_back(moveBy(borderMenu, 3, 0, 60, 60, 8, 8));
	}

	//angolo sx basso
	tiles.push_back(moveBy(borderMenu, 5, 0, 60, 60, 8, 8));
	//bordo inferiore
	for (int i = 2; i < sizeMenu.x; i++) {
		tiles.push_back(moveBy(borderMenu, 6, 0, 60, 60, 8, 8));

	}
	//angolo dx basso
	tiles.push_back(moveBy(borderMenu, 8, 0, 60, 60, 8, 8));

	return new TiledSprite(_spriteSheets["hud"], tiles, size);
	;

}
