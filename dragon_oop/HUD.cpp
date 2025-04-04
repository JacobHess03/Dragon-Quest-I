// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "HUD.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"

using namespace agp;

HUD::HUD(const RectF& r,Hero* hero)
	: UIScene(r)
{
	setBackgroundColor(Color(0, 0, 0, 0));

	_hp = hero->getHp();
	_mp = hero->getMp();
	damage = hero->getWeapon()->getDamage();
	_hero = hero;
	_blocking = false;

	//RenderableObject* background = new RenderableObject(this, r, Color(0, 0, 0, 0));
	new RenderableObject(this, RectF(2, 0.7, 1.6, 1.6), SpriteFactory::instance()->getText("Hero", { 0.3f, 0.3f }));
	new RenderableObject(this, RectF(0.8, 1.3, 0.5, 0.5), SpriteFactory::instance()->getText("Hp", { 0.3f, 0.3f }));
	new RenderableObject(this, RectF(1.4, 1.3, 0.3, 0.3), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
	new RenderableObject(this, RectF(2.7, 1.3, 0.5, 0.5), SpriteFactory::instance()->getText("Mp", { 0.3f, 0.3f }));
	new RenderableObject(this, RectF(3.2, 1.3, 0.3, 0.3), SpriteFactory::instance()->getText(":", { 0.3f, 0.3f }));
	new RenderableObject(this, RectF(1.1, 1.8, 2.1, 0.3), SpriteFactory::instance()->getText("Damage:",{0.3,0.3}));
	

	
	Health_Points = new RenderableObject(this, RectF(1.7, 1.3, 0.7, 0.5), SpriteFactory::instance()->getText(std::to_string(_hp), {0.3f, 0.3f}));
	Mana_Points = new RenderableObject(this, RectF(3.5, 1.3, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(_mp), { 0.3f, 0.3f }));
	Damage= new RenderableObject(this, RectF(3.2, 1.8, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(hero->getWeapon()->getDamage()), { 0.3f, 0.3f }));


	// setup view (specific for super mario bros)
	_view = new View(this, _rect);
	_view->setFixedAspectRatio(Game::instance()->aspectRatio());
	_view->setRect(RectF(0, 0, 16, 15));
}

// extends update logic (+time management)
void HUD::update(float timeToSimulate)
{
	UIScene::update(timeToSimulate);
	updateInt();
	Health_Points->setSprite(SpriteFactory::instance()->getText(std::to_string(_hp), { 0.3f, 0.3f }));
	Mana_Points->setSprite(SpriteFactory::instance()->getText(std::to_string(_mp), { 0.3f, 0.3f }));
	Damage->setSprite(SpriteFactory::instance()->getText(std::to_string(damage), { 0.3f, 0.3f }));
	if (!_active)
		return;
}
void HUD::updateInt() {
	_hp = _hero->getHp();
	_mp = _hero->getMp();
	if (_hero->getRage()) {
		damage = _hero->getWeapon()->getDamage() +1;
	}
	else 
		damage = _hero->getWeapon()->getDamage();
}