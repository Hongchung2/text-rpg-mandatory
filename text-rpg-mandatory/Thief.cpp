# include "Thief.h"
# include "Monster.h"

void Thief::attack(Monster* monster)
{
	int Playerdamage_dis = (getPower() / 5) - monster->getDefence();
	if (Playerdamage_dis <= 0) { Playerdamage_dis = 1; }
	int Playerdamage = Playerdamage_dis * 5;
	int SlimecurrentHp = monster->getHp() - Playerdamage;

	cout << "* 날카로운 단검으로 찌른다!" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << monster->getName() << "에게 " << Playerdamage_dis << " 데미지! " << endl;
	}

	monster->setHp(SlimecurrentHp);
}