#include <iostream>

using namespace std;

// 스탯 함수
void printStatus(string name, int stat[])
{
	cout << "" << endl;

	cout << "===========================" << endl;
	cout << "   " << name << "의 현재 능력치" << endl;
	cout << "===========================" << endl;

	cout << "HP: " << stat[0] << "       MP: " << stat[1] << endl;
	cout << "공격력: " << stat[2] << "   방어력: " << stat[3] << endl;
	cout << "===========================" << endl;
	cout << "" << endl;

}

// 전직 시스템
class Player
{
protected:
	string name = "";
	string job = "";
	int level;
	int hp;
	int mp;
	int power;
	int defence;

public:
	Player(string name, int hp, int mp, int power, int defence) {
		this->name = name;
		this->hp = hp;
		this->mp = mp;
		this->power = power;
		this->defence = defence;
	}

	virtual void attack() = 0;
	virtual ~Player() {}

	void setName(string name)
	{
		this->name = name;
	}

	void setHp(int hp)
	{
		this->hp = hp;
	}

	void setMp(int mp)
	{
		this->mp = hp;
	}

	void setPower(int power)
	{
		this->power = power;
	}

	void setDefence(int defence)
	{
		this->defence = defence;
	}

	string getName() { return name; }
	int getHp() { return hp; }
	int getMp() { return mp; }
	int getPower() { return power; }
	int getDefence() { return defence; }
	
	void printPlayerStatus()
	{
		cout << "-------------------------------------" << endl;
		cout << "닉네임: " << name << "  | 직업: " << job << "  | Lv.1" << endl;
		cout << "HP: " << hp << "  | MP: " << mp << "  | 공격력: " << power << "  | 방어력: " << defence << endl;
		cout << "-------------------------------------" << endl;
		cout << "" << endl;
	}
};

class Warrior : public Player
{
public:

	Warrior(string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power, defence)
	{
		job = "전사";
		hp += 30;
	}
	void attack()
	{
		cout << "* 전사로 전직하였습니다. (hp +30)" << endl;
		cout << "* 거대한 대검을 내려친다!" << endl;
		cout << "" << endl;
	}
};

class Mage : public Player
{
public:

	Mage(string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power, defence)
	{
		job = "마법사";
		mp += 30;
	}
	void attack()
	{
		cout << "* 마법사로 전직하였습니다. (mp +30)" << endl;
		cout << "* 뜨꺼운 파이어볼을 발사한다!" << endl;
		cout << "" << endl;
	}
};

class Thief : public Player
{
public:

	Thief(string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power, defence)
	{
		job = "도적";
		power += 30;
	}
	void attack()
	{
		cout << "* 도적으로 전직하였습니다. (power +30)" << endl;
		cout << "* 날카로운 단검으로 찌른다!" << endl;
		cout << "" << endl;
	}
};

class Archer : public Player
{
public:

	Archer(string name, int hp, int mp, int power, int defence) : Player(name, hp, mp, power, defence)
	{
		job = "궁수";
		power += 30;
	}
	void attack()
	{
		cout << "* 궁수로 전직하였습니다. (power +30)" << endl;
		cout << "* 재빠른 화살을 쏜다!" << endl;
		cout << "" << endl;
	}
};
int main()
{
	// 캐릭터 생성 화면--------------------------------
	string CharacterName = "";
	const int SIZE = 4;
	int stat[SIZE] = { 0 };

	cout << "==============================" << endl;
	cout << "   [ 던전 탈출 텍스트 RPG]" << endl;
	cout << "==============================" << endl;

	cout << "용사의 이름을 입력해주세요: ";
	cin >> CharacterName;
	cout << "" << endl;

	while (true)
	{
		cout << "HP와 MP를 입력해주세요: ";
		cin >> stat[0] >> stat[1];

		if (stat[0] < 50 || stat[1] < 50)
		{
			cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
		}
		else if (stat[0] >= 50 && stat[1] >= 50)
		{
			break;
		}
	}
	
	cout << "" << endl;

	while (true)
	{
		cout << "공격력과 방어력을 입력해주세요: ";
		cin >> stat[2] >> stat[3];

		if (stat[2] < 50 || stat[3] < 50)
		{
			cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
		}
		else if (stat[2] >= 50 && stat[3] >= 50)
		{
			break;
		}
	}
	

	// 스탯 함수 호출
	printStatus(CharacterName, stat);
	// ----------------------------------------------------

	// 스탯 관리 메뉴
	int HP_Posion = 5;
	int MP_Posion = 5;
	int UpgradeNum;
	bool isGameeStart = false;

	cout << "* HP 포션 5개, MP 포션  5개가 기본 지급되었습니다." << endl;
	cout << "===========================" << endl;
	cout << "" << endl;

	cout << "<캐릭터 강화>" << endl;
	cout << "1. HP UP    " << "2. MP UP    " << "3. 공격력 2배" << endl;
	cout << "4. 방어력 2배  " << "5. 현재 능력치  " << "0. 게임 시작" << endl;
	cout << "===========================" << endl;
	cout << "" << endl;

	while (!isGameeStart)
	{
		cout << "번호를 선택해주세요: ";
		cin >> UpgradeNum;

		cout << "" << endl;

		switch (UpgradeNum)
		{
		case 1: 
		{
			if (HP_Posion == 0)
			{
				cout << "* 보유하신 HP 포션이 부족합니다." << endl;
				cout << "" << endl;
				break;
			}

			HP_Posion--;
			stat[0] += 20;
			cout << "* HP가 20 증가했습니다. (현재 HP: " << stat[0] << " / " << "HP 포션 차감 : 남은 포션 " << HP_Posion << "개)" << endl;
			cout << "" << endl;
			break;
		}
		case 2:
		{
			if (MP_Posion == 0)
			{
				cout << "* 보유하신 MP 포션이 부족합니다." << endl;
				cout << "" << endl;
				break;
			}

			MP_Posion--;
			stat[1] += 20;
			cout << "* MP가 20 증가했습니다. (현재 MP: " << stat[1] << " / " << "MP 포션 차감: 남은 포션 " << HP_Posion << "개)" << endl;
			cout << "" << endl;
			break;
		}
		case 3:
		{
			stat[2] *= 2;
			cout << "* 공격력이 2배 증가했습니다. (현재 공격력: " << stat[2] << ")" << endl;
			cout << "" << endl;
			break;
		}
		case 4:
		{
			stat[3] *= 2;
			cout << "* 방어력이 2배 증가했습니다. (현재 방어력: " << stat[3] << ")" << endl;
			cout << "" << endl;
			break;
		}
		case 5:
		{
			printStatus(CharacterName, stat);
			break;
		}
		case 0:
		{
			isGameeStart = true;
			cout << "게임을 시작합니다!" << endl;
			cout << " " << endl;
			break;
		}
		}
	}
	cout << "" << endl;
	// --------------------------------------------------------

	// 전직 시스템----------------------------------------------
	int ClassNum;

	cout << "<전직 시스템>" << endl;
	cout << "" << endl;
	cout << CharacterName << "님, 직업을 선택해주세요!" << endl;
	cout << "" << endl;
	cout << "1. 전사   " << "2. 마법사   " << "3. 도적   " << "4. 궁수" << endl;
	cout << "" << endl;

	cout << "선택: ";
	cin >> ClassNum;

	cout << "" << endl;
	Player* player = nullptr;

	switch (ClassNum)
	{
	case 1:
	{
		player = new Warrior(CharacterName, stat[0], stat[1], stat[2], stat[3]);
		player->attack();
		player->printPlayerStatus();
		break;
	}
	case 2:
	{
		player = new Mage(CharacterName, stat[0], stat[1], stat[2], stat[3]);
		player->attack();
		player->printPlayerStatus();
		break;
	}
	case 3:
	{
		player = new Thief(CharacterName, stat[0], stat[1], stat[2], stat[3]);
		player->attack();
		player->printPlayerStatus();
		break;
	}
	case 4:
	{
		player = new Archer(CharacterName, stat[0], stat[1], stat[2], stat[3]);
		player->attack();
		player->printPlayerStatus();
		break;
	}
	}

	// 마지막 프로그램 종료 시--------------
	delete player;
	// -----------------------------------
}