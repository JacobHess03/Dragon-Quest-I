#pragma once
#include <map>
#include <vector>
#include <list>
#include "geometryUtils.h"
#include "graphicsUtils.h"
#include <functional>

namespace agp
{
	class Item;
}
//item class
class agp::Item {
	private:
		std::string item_name;
		std::function<void()> item_task;
		bool _fight;
		int _cost;
	public:
		Item(const std::string name,int cost,std::function<void()> task,bool fight);
		const std::string getName() { return item_name; }
		void task() { item_task(); }
		bool getFight() { return _fight; }
		int getCost() { return _cost; }

};