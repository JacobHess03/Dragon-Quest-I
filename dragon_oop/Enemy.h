// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "DynamicObject.h"

namespace agp
{
	class Enemy;
}

// Enemy
// - base class for all enemies
class agp::Enemy : public DynamicObject
{
	private:

		bool _smashable;

	public:

		Enemy(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);

		// actions
		//virtual void stomp();					// mario jumps on top of the enemy
		//virtual void kick(bool right = true);	// mario kicks from one side
		virtual void smash();					// hit by invincible mario, fireball, shell, or block bump

		// extends logic hit (+smashed, +hurt Mario)
		virtual bool hit(CollidableObject* what, Direction fromDir);

		virtual std::string name() override { return strprintf("Enemy[%d]", _id); }
};