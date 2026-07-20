#include "Warrior.h"
#include "Monster.h"

void Warrior::attack(Monster* monster)
{
	int Playerdamage = getPower() - monster->getDefence();
	if (Playerdamage <= 0) { Playerdamage = 1; }
	int SlimecurrentHp = monster->getHp() - Playerdamage;

	cout << "* 거대한 대검을 내려친다!" << endl;
	cout << monster->getName() << "에게 " << Playerdamage << " 데미지!" << endl;

	monster->setHp(SlimecurrentHp);

}
