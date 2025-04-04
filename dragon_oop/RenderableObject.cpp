// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "RenderableObject.h"
#include "Scene.h"

using namespace agp;

RenderableObject::RenderableObject(Scene* scene, const RectF& rect, const Color& color, int layer)
	: Object(scene, rect, layer)
{
	_color = color;
	_flip = SDL_FLIP_NONE;
	_focused = false;
	_visible = true;
	_sprite = nullptr;
	_focusColor = { 255, 255, 0, 128 };
	_borderColor = { 0, 0, 0, 0 };
}

RenderableObject::RenderableObject(Scene* scene, const RectF& rect, Sprite* sprite, int layer)
	: Object(scene, rect, layer)
{
	_color = { 0,0,0,0 };
	_flip = SDL_FLIP_NONE;
	_sprite = sprite;
	_focused = false;
	_visible = true;
}

void RenderableObject::draw(SDL_Renderer* renderer, Transform camera)
{
	if (!_visible)
		return;

	SDL_FRect drawRect = RectF(camera(_rect.tl()), camera(_rect.br())).toSDLf();

	if (_sprite)
		_sprite->render(renderer, _rect, camera, 0, _flip);
	else
	{
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
		SDL_RenderFillRectF(renderer, &drawRect);
	}

	if (_borderColor.a)
	{
		SDL_SetRenderDrawColor(renderer, _borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
		SDL_RenderDrawRectF(renderer, &drawRect);
	}

	if (_focused)
	{
		SDL_SetRenderDrawColor(renderer, _focusColor.r, _focusColor.g, _focusColor.b, _focusColor.a);
		SDL_RenderFillRectF(renderer, &drawRect); 
		_focused = false;
	}
}

void RenderableObject::update(float dt)
{
	Object::update(dt);

	if (_sprite)
		_sprite->update(dt);
}

void RenderableObject::setSprite(Sprite* sprite) 
{ 
	if (_sprite)
		delete _sprite;

	_sprite = sprite; 
}