#ifndef Owk_H_
#define Owk_H_

#include <iostream>
#include <string>
#include "Monster.h"

class Owk : public Monster
{
public:
	Owk(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

	void attack();

};
#endif