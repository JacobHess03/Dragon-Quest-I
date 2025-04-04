// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScene.h"
#include "RenderableObject.h"
#include "Hero.h"

namespace agp
{
	class HUD;
}

// HUD
// - implements (as an example) the Super Mario Bros's HUD
class agp::HUD : public UIScene
{
	protected:

		// raw data
		int _hp;
		int _mp;
		int damage;
		Hero* _hero;
		

		// rendering
		RenderableObject* Health_Points;
		RenderableObject* Mana_Points;
		RenderableObject* Damage;
	public:
		HUD(const RectF& r,Hero* hero);
		virtual ~HUD() {};

		// extends update logic (+time management)
		virtual void update(float timeToSimulate) override;
		void updateInt();
};