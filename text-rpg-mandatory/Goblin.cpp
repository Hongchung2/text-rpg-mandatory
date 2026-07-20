#include "Goblin.h"
Goblin::Goblin(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward) : Monster(name, hp, power, defence, dropItemName, dropItemPrice, expReward)
{

}
void Goblin::attack()
{
	cout << "고블린의 기습 찌르기!" << endl;
}