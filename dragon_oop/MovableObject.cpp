// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "MovableObject.h"

using namespace agp;

MovableObject::MovableObject(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	RenderableObject(scene, rect, sprite, layer)
{
	// default movement (stand)
	_x_dir = Direction::NONE;
	_y_dir = Direction::NONE;
	_vel = { 0, 0 };
	last_dir = Direction::NONE;
	

	defaultPhysics();
}

void MovableObject::defaultPhysics()
{
	// super-mario-bros-like physics parameters
	/*_y_gravity = 0;
	_y_acc_jmp = 900;*/
	_y_acc = 1000;
	_y_vel_max = 60;
	_y_vel_min = 0.03f;

	_x_vel_max = 60;	
	_x_vel_min = 0.3f;
	_x_acc = 1000;		
	/*_x_dec_rel = 11;
	_x_dec_skd = 23;
	_y_dec_skd = 23;*/
}

void MovableObject::velClip(float vx, float vy)
{
	_vel.x = std::max(_vel.x, -vx);
	_vel.x = std::min(_vel.x, vx);
	_vel.y = std::max(_vel.y, -vy);
	_vel.y = std::min(_vel.y, vy);
}

void MovableObject::velAdd(Vec2Df amount)
{
	_vel += amount;

	// max velocity clipping 
	velClip(_x_vel_max, _y_vel_max);

	// min velocity clipping 
	if (_x_dir == Direction::NONE && std::abs(_vel.x) < _x_vel_min)
		_vel.x = 0; // checking _x_dir to allow skidding
	if (_y_dir == Direction::NONE && std::abs(_vel.y) < _y_vel_min)
		_vel.y = 0;
}


void MovableObject::moveX(Direction dir)
{
	
	if (_x_dir != dir) {
		_vel.x = 0;  // Instant velocuty change in x
		_x_dir = dir;
	}
}
//NUOVO
void MovableObject::moveY(Direction dir) {
	
	if (_y_dir != dir) {
		_vel.y = 0;  // Instant velocity change in y
		_y_dir = dir;
	}
}

void MovableObject::jump()
{
	if (!midair())
		velAdd(Vec2Df(0, -_y_acc_jmp));
}

bool MovableObject::skidding() const
{
	return (_x_dir == Direction::RIGHT && _vel.x < 0) ||
		(_x_dir == Direction::LEFT && _vel.x > 0);
}
//NUOVO
bool MovableObject::skiddingVertically() const {
	return (_y_dir == Direction::UP && _vel.y < 0) ||
		(_y_dir == Direction::DOWN && _vel.y > 0);
}

bool MovableObject::grounded() const
{
	return _vel.y == 0 && _prev_vel.y > 0;
}

bool MovableObject::falling() const
{
	return _vel.y > 0 && _prev_vel.y <= 0;
}

bool MovableObject::midair() const
{
	return _vel.y != 0 || (_vel.y == 0 && _prev_vel.y < 0);
}

void MovableObject::update(float dt)
{
	
	RenderableObject::update(dt);

	// velocity backup (useful to determine object state)
	
		_prev_vel = _vel;





		// apply horizontal accelerations and decelerations
		if (_x_dir == Direction::RIGHT && _vel.x >= 0) {
			last_dir = Direction::RIGHT;
			velAdd(Vec2Df(_x_acc * dt, 0));
		}

		else if (_x_dir == Direction::LEFT && _vel.x <= 0) {
			last_dir = Direction::LEFT;
			velAdd(Vec2Df(-_x_acc * dt, 0));
		}

		// apply vertical accelerations and decelerations
		if (_y_dir == Direction::UP && _vel.y <= 0) {
			last_dir = Direction::UP;
			velAdd(Vec2Df(0, -_y_acc * dt));
		}
		else if (_y_dir == Direction::DOWN && _vel.y >= 0) {
			last_dir = Direction::DOWN;
			velAdd(Vec2Df(0, _y_acc * dt));
		}
		// move
		_rect.pos += _vel * dt;
	
}