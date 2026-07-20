#ifndef Warrior_H_
#define Warrior_H_

#include <iostream>
#include <string>
#include "Player.h"

class Warrior : public Player
{
public:

	Warrior(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level) : Player(name, maxhp, maxmp, hp, mp, power, defence, exp, maxExp, level)
	{
		job = "전사";
		maxhp += 30;
		hp += 30;
		cout << "* 전사로 전직하였습니다. (HP + 30)" << endl;
	}

	void attack(Monster* monster);
};

#endif