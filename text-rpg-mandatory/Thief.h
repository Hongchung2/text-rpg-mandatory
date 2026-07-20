#ifndef Thief_H_
#define Thief_H_

#include <iostream>
#include <string>
#include "Player.h"

class Thief : public Player
{
public:

	Thief(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level) : Player(name, maxhp, maxmp, hp, mp, power, defence, exp, maxExp, level)
	{
		job = "도적";
		power += 30;
		cout << "* 도적으로 전직하였습니다. (POWER + 30)" << endl;
	}

	void attack(Monster* monster);
};
#endif