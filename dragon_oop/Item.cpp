#include "Item.h"

using namespace agp;

Item::Item(const std::string name,int cost,std::function<void()> task,bool fight) {
	item_name = name;
	item_task = task;
	_fight = fight;
	_cost = cost;
}
