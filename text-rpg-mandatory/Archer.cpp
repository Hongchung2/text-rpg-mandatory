#include "Archer.h"
#include "Monster.h"

void Archer::attack(Monster* monster)
{
	int Playerdamage_dis = (getPower() / 3) - monster->getDefence();
	if (Playerdamage_dis <= 0) { Playerdamage_dis = 1; }
	int Playerdamage = Playerdamage_dis * 3;
	int SlimecurrentHp = monster->getHp() - Playerdamage;

	cout << "* 재빠른 화살을 날린다!" << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << monster->getName() << "에게 " << Playerdamage_dis << " 데미지! " << endl;
	}

	monster->setHp(SlimecurrentHp);
}