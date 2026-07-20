#ifndef Slime_H_
#define Slime_H_

#include <iostream>
#include <string>
#include "Monster.h"

class Slime : public Monster
{
public:
	Slime(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

	void attack();

};
#endif