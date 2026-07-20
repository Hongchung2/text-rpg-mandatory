#include "Mage.h"
#include "Monster.h"

void Mage::attack(Monster* monster)
{
	int Playerdamage = getPower() - monster->getDefence();
	if (Playerdamage <= 0) { Playerdamage = 1; }
	int SlimecurrentHp = monster->getHp() - Playerdamage;

	cout << "* 파이어볼을 발사한다!" << endl;
	cout << monster->getName() << "에게 " << Playerdamage << " 데미지!" << endl;

	monster->setHp(SlimecurrentHp);
}