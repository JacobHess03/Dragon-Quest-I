// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MovableObject.h"

namespace agp
{
	class CollidableObject;
}

// CollidableObject class.
// - defines a collider (default: object rect)
// - implements collision detection and resolution
// - defines logic collision (see hit method)
class agp::CollidableObject : public MovableObject
{
	protected:

		// collisions
		RectF _collider;			// in object coordinates
		bool _collidable;
		bool _compenetrable;
		bool _colliderVisible;
		const Color _colliderColor = { 255, 0, 0, 255 };

		// collision detection/resolution
		virtual void resolveCollisions(float dt);

	public:

		CollidableObject(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
		virtual ~CollidableObject() {}

		// getters/setters
		const RectF& collider() const { return _collider; }
		RectF sceneCollider() const;
		bool compenetrable() const { return _compenetrable; }
		bool collidable() const { return _collidable; }
		void toggleCollider() { _colliderVisible = !_colliderVisible; }

		// extends game logic (+collisions)
		virtual void update(float dt) override;

		// extends rendering (+collider)
		virtual void draw(SDL_Renderer* renderer, Transform camera) override;

		// defines acceptable collisions (default: any)
		virtual bool collidableWith(CollidableObject* obj) { return true; }

		// defines logic collision, i.e. what to do when two objects collide
		// from a game logic perspective (e.g. player dies if hit by enemy)
		// returns true if logic collision is resolved, false otherwise
		virtual bool hit(CollidableObject* what, Direction fromDir) { return true; }

		// euclidean distance between colliders
		virtual float distance(CollidableObject* obj) const;
};