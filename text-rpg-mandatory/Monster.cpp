#include "Monster.h"

Monster::Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward)
{
	this->name = name;
	this->hp = hp;
	this->power = power;
	this->defence = defence;
	this->dropItemName = dropItemName;
	this->dropItemPrice = dropItemPrice;
	this->expReward = expReward;
}