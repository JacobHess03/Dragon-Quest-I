// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Trigger.h"

using namespace agp;

Trigger::Trigger(Scene* scene, const RectF& rect, CollidableObject* watched, std::function<void()> task) :
	CollidableObject(scene, rect, nullptr)
{
	_task = task;
	_watched = watched;
	_compenetrable = false;
}



// extends logic collision (+trigger behavior)
bool Trigger::hit(CollidableObject* what, Direction fromDir)
{
	if (what == _watched )
	{
		_task();
		return true;
	}
	else
		return false;
}