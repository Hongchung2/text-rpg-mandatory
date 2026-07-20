#include "Player.h"


Player::Player(string name, int maxhp, int maxmp, int hp, int mp, int power, int defence, int exp, int maxExp, int level)
{
	this->name = name;
	this->maxhp = maxhp;
	this->maxmp = maxmp;
	this->hp = hp;
	this->mp = mp;
	this->power = power;
	this->defence = defence;
	this->exp = exp;
	this->maxExp = maxExp;
	this->level = level;
}

void Player::printPlayerStatus()
{
	cout << "-------------------------------------" << endl;
	cout << "닉네임: " << name << "  | 직업: " << job << "  | Lv: " << level << endl;
	cout << "HP: " << hp << "  | MP: " << mp << "  | 공격력: " << power << "  | 방어력: " << defence << endl;
	cout << "-------------------------------------" << endl;
	cout << "" << endl;
}