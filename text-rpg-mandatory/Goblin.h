#ifndef Goblin_H_
#define Goblin_H_

#include <iostream>
#include <string>
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

	void attack();

};
#endif