#ifndef Player_H_
#define Player_H_

#include <iostream>
#include <string>
#include "Monster.h"


class Player
{
protected:
	string name = "";
	string job = "";
	int level = 1;
	int exp;
	int maxExp;
	int maxhp;
	int maxmp;
	int hp;
	int mp;
	int power;
	int defence;

public:
	Player(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level);
	virtual void attack(Monster* monster) = 0;
	virtual ~Player() {}
	void printPlayerStatus();

	void setName(string name)
	{
		this->name = name;
	}
	
	void setMaxHp(int maxhp)
	{
		this->maxhp = maxhp;
	}

	void setMaxMp(int maxmp)
	{
		this->maxmp = maxmp;
	}

	void setHp(int hp)
	{
		this->hp = hp;
	}

	void setMp(int mp)
	{
		this->mp = mp;
	}

	void setPower(int power)
	{
		this->power = power;
	}

	void setDefence(int defence)
	{
		this->defence = defence;
	}

	void setJob(string job)
	{
		this->job = job;
	}

	void setExp(int exp)
	{
		this->exp = exp;
	}

	void setmaxExp(int maxExp)
	{
		this->maxExp = maxExp;
	}

	void setlevel(int level)
	{
		this->level = level;
	}

	string getName() { return name; }
	int getMaxHp() { return maxhp; }
	int getMaxMp() { return maxmp; }
	int getHp() { return hp; }
	int getMp() { return mp; }
	int getPower() { return power; }
	int getDefence() { return defence; }
	string getJob() { return job; }
	int getExp() { return exp; }
	int getmaxExp() { return maxExp; }
	int getlevel() { return level; }
};
#endif