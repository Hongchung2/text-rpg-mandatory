#include "Owk.h"
Owk::Owk(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward) : Monster(name, hp, power, defence, dropItemName, dropItemPrice, expReward)
{

}
void Owk::attack()
{
	cout << "¿ÀÅ©ÀÇ À°Åºµ¹Áø!" << endl;
}