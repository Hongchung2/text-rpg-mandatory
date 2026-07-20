#include "Slime.h"
Slime::Slime(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward) : Monster(name, hp, power, defence, dropItemName, dropItemPrice, expReward)
{
	
}
void Slime::attack()
{
	cout << "슬라임의 몸통 박치기!" << endl;
}