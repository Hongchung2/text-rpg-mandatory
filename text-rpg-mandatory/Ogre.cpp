#include "Ogre.h"
Ogre::Ogre(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward) : Monster(name, hp, power, defence, dropItemName, dropItemPrice, expReward)
{

}
void Ogre::attack()
{
	cout << "오우거의 밟아버리기!" << endl;
}