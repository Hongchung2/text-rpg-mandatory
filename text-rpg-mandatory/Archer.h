#ifndef Archer_H_
#define Archer_H_

#include <iostream>
#include <string>
#include "Player.h"

class Archer : public Player
{
public:

	Archer(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level) : Player(name, maxhp, maxmp, hp, mp, power, defence, exp, maxExp, level)
	{
		job = "궁수";
		power += 30;
		cout << "* 궁수로 전직하였습니다. (POWER + 30)" << endl;
	}

	void attack(Monster* monster);
};
#endif