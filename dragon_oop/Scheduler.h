// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2023 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <functional>

namespace agp
{
	class Scheduler;
}

// Scheduler class
// -  performs a given task with the given delay
class agp::Scheduler
{
	private:

		std::function<void()> _task;
		float _reverseTimer;

	public:

		Scheduler()
		{
			_task = []() {};
			_reverseTimer = 0;
		}

		Scheduler(float delaySeconds, std::function<void()> task)
		{
			_task = task;
			_reverseTimer = delaySeconds;
		}

		void update(float dt)
		{
			if (on())
			{
				_reverseTimer -= dt;
				if (_reverseTimer <= 0)
					_task();
			}
		}

		bool on() { return _reverseTimer > 0; }
};