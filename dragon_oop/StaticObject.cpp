// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "StaticObject.h"
#include "Scene.h"
#include "Audio.h"

using namespace agp;

StaticObject::StaticObject(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{	

}

bool StaticObject::hit(CollidableObject* what, Direction fromDir)
{
	_focused = true;
	Audio::instance()->playSound("42 Dragon Quest 1 - Bumping into Walls");
	return true;
}
