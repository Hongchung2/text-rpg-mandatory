#ifndef Ogre_H_
#define Ogre_H_

#include <iostream>
#include <string>
#include "Monster.h"

class Ogre : public Monster
{
public:
	Ogre(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);

	void attack();

};
#endif