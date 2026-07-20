#ifndef Dragon_H_
#define Dragon_H_

#include <iostream>
#include <string>
#include "Monster.h"

class Dragon : public Monster
{
public:
	Dragon(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

	void attack();

};
#endif