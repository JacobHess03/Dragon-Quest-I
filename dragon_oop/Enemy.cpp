#include "Enemy.h"
#include "Hero.h"
#include "Audio.h"
#include "Scene.h"

using namespace agp;

Enemy::Enemy(Scene* scene, const RectF& rect, Sprite* sprite, int layer)
	: DynamicObject(scene, rect, sprite, layer)
{
	_smashable = true;
}

bool Enemy::hit(CollidableObject* what, Direction fromDir)
{
	Hero* mario= dynamic_cast<Hero*>(what);

	/*if (mario)
	{
		if (_smashable && mario->invincible())
			smash();
		else
			mario->hurt();

		return true;
	}*/

	return false;
}

void Enemy::smash()
{
	
	_vel.y = -8;
	_collidable = false;
	_flip = SDL_FLIP_VERTICAL;
	Audio::instance()->playSound("kick");

	schedule("die-smash", 2, [this]() {_scene->killObject(this); });
}