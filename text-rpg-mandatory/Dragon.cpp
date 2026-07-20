#include "Dragon.h"
Dragon::Dragon(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward) : Monster(name, hp, power, defence, dropItemName, dropItemPrice, expReward)
{

}
void Dragon::attack()
{
	cout << "드래곤의 강력한 브레스!" << endl;
}