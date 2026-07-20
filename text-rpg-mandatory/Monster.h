#ifndef Monster_H_
#define Monster_H_

#include <iostream>
#include <string>

using namespace std;

class Monster
{
protected:
	string name = "";
	int hp;
	int power;
	int defence;

	string dropItemName = "";
	int dropItemPrice;

	int expReward;

public:
	Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward);
	virtual void attack() = 0;
	virtual ~Monster() {}

	void setName(string name) { this->name = name; }
	void setHp(int hp) { this->hp = hp; }
	void setPower(int power) { this->power = power; }
	void setDefence(int defence) { this->defence = defence; }
	void setDropItemName(string dropItemName) { this->dropItemName = dropItemName; }
	void setDropItemPrice(int dropItemPrice) { this->dropItemPrice = dropItemPrice; }
	void setexpReward(int expReward) { this->expReward = expReward; }

	string getName() { return name; }
	int getHp() { return hp; }
	int getPower() { return power; }
	int getDefence() { return defence; }
	string getDropItemName() { return dropItemName; }
	int getDropItemPrice() { return dropItemPrice; }
	int getexpReward() { return expReward; }
};
#endif // !MONSTER_H_
