#ifndef Mage_H_
#define Mage_H_

#include <iostream>
#include <string>
#include "Player.h"

class Mage : public Player
{
public:

	Mage(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level) : Player(name, maxhp, maxmp, hp, mp, power, defence, exp, maxExp, level)
	{
		job = "마법사";
		maxhp += 30;
		mp += 30;
		cout << "* 마법사로 전직하였습니다. (MP + 30)" << endl;
	}
	
	void attack(Monster* monster);
};
#endif