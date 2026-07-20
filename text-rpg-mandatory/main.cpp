#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "Player.h"
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

#include "Monster.h"
#include "Slime.h"
#include "Goblin.h"
#include "Owk.h"
#include "Ogre.h"
#include "Dragon.h"

#include "Inventory.h"

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

void setpotion(int count, int* p_HPPotion, int* p_MPPotion)
{
	*p_HPPotion = count;
	*p_MPPotion = count;
}

// 몬스터----------------------------------------------------------------


void MonsterBattle(string CharacterName, Player* player, Monster* monster, Inventory<Item>& inventory)
{
	cout << "[ 전투 시작! ] " << CharacterName << "(" << player->getJob() << ") vs " << monster->getName() << endl;
	cout << endl;
	while (1)
	{
		cout << "--- 플레이어 턴 ---" << endl;
		cout << "1. 공격" << endl;
		cout << "2. 아이템 사용" << endl;
		int PlayerTurnNum;
		cout << endl;
		cout << "선택: ";
		cin >> PlayerTurnNum;
		cout << endl;

		switch (PlayerTurnNum)
		{
		case 1:
		{
			if (player->getHp() > 0 && monster->getHp() > 0)
			{
				int SlimepreHp = monster->getHp();
				player->attack(monster);

				if (monster->getHp() > 0)
				{
					cout << monster->getName() << " HP: " << SlimepreHp << " -> " << monster->getHp() << endl;
				}
				else
				{
					cout << monster->getName() << " HP: " << SlimepreHp << " -> 0 (사망)" << endl;
					cout << endl;
					cout << "★ 전투 승리!" << endl;

					int GetExp = player->getExp() + monster->getexpReward();
					player->setExp(GetExp);
					cout << "  -> 경험치 +" << monster->getexpReward()
						<< " 획득! (현재 경험치: " << player->getExp() << "/" << player->getmaxExp() << ")" << endl;

					while (player->getExp() >= player->getmaxExp())
					{
						int level = player->getlevel();
						int playerlevel = player->getlevel() + 1;
						player->setlevel(playerlevel);

						int remainExp = player->getExp() - player->getmaxExp();
						player->setExp(remainExp);

						int addMaxExp = player->getmaxExp() + 100;
						player->setmaxExp(addMaxExp);

						cout << "...레벨업 조건 충족" << endl;
						cout << "  -> 레벨업! Lv." << level << " -> Lv." << player->getlevel() << endl;

						player->setMaxHp(player->getMaxHp() + 10);
						player->setHp(player->getMaxHp());
						player->setMaxHp(player->getMaxMp() + 10);
						player->setHp(player->getMaxMp());
						player->setPower(player->getPower() + 5);
						cout << "  -> HP + 10, MP + 5, 공격력 + 5 증가!" << endl;
						cout << endl;
					}

					cout << "  -> " << monster->getDropItemName() << " 획득!" << endl;
					cout << "  -> 인벤토리에 저장되었습니다." << endl;
					Item DropItem{ monster->getDropItemName(), monster->getDropItemPrice() };
					inventory.AddItem(DropItem);
					
					cout << "-> 클리어!" << endl;
					cout << endl;
					return; // 전투 승리로 함수 종료 (몬스터 턴으로 안 넘어감)
				}
			}
			break;
		}
		case 2:
		{
			int UseItemNum;
			cout << " [인벤토리] " << endl;
			cout << endl;
			if (inventory.getSize() == 0)
			{
				cout << "인벤토리가 비어있습니다." << endl;
			}
			for (int i = 1; i <= inventory.getSize(); i++)
			{
				cout << i << ". " << inventory[i - 1].name << " (" << inventory[i - 1].price << ")" << endl;
			}
			cout << endl;
			cout << "사용할 아이템 번호: ";
			cin >> UseItemNum;

			if (UseItemNum < 1 || UseItemNum > inventory.getSize())
			{
				cout << "잘못된 번호입니다. 다시 선택해주세요" << endl;
			}

			if (inventory[UseItemNum - 1].name == "HP 포션")
			{
				int PrevHp = player->getHp();
				player->setHp(min(player->getHp() + 50, player->getMaxHp()));

				cout << "* HP 포션 사용! HP 50 회복 (" << PrevHp << " -> " << player->getHp() << ")" << endl;

				inventory.RemoveItem(UseItemNum - 1);
			}
			else if (inventory[UseItemNum - 1].name == "MP 포션")
			{
				int PrevMp = player->getMp();
				player->setMp(min(player->getMp() + 50, player->getMaxMp()));

				cout << "* MP 포션 사용! MP 50 회복 (" << PrevMp << " -> " << player->getMp() << ")" << endl;

				inventory.RemoveItem(UseItemNum - 1);
			}
			else
			{
				cout << "사용할 수 없는 아이템입니다." << endl;
			}
			break;
		}
		}

		// 여기 도달했다면 = 아직 몬스터가 살아있는 상태 (승리로 return 못 했으면 여기로 옴)
		cout << endl;
		cout << "--- " << monster->getName() << " 턴 --- " << endl;
		monster->attack();

		int PlayerpreHp = player->getHp();
		int Slimedamage = monster->getPower() - player->getDefence();
		if (Slimedamage <= 0) { Slimedamage = 1; }
		int PlayercurrentHp = player->getHp() - Slimedamage;
		cout << player->getName() << "에게 " << Slimedamage << "데미지!" << endl;
		player->setHp(PlayercurrentHp);

		if (player->getHp() > 0)
		{
			cout << player->getName() << " HP: " << PlayerpreHp << " -> " << player->getHp() << endl;
		}
		else
		{
			cout << player->getName() << " HP: " << PlayerpreHp << " -> " << player->getHp() << " (사망)" << endl;
			cout << endl;
			cout << "★ 전투 패배!" << endl;
			cout << "  -> 플레이어가 사망하였습니다." << endl;
			exit(0); // switch/loop 밖이므로 break 대신 return
		}
		cout << endl;
	}
}



// ----------------------------------------------------------------------



struct PotionRecipe
{
	string name;
	vector<string> material;
	vector<int> material_num;
};

struct AlchemyWorkshop
{

};

struct Dungeon
{
	string name;
	int hp;
	int power;
	int roomNum;
};


// 포션 레시피
vector<PotionRecipe> potionRecipe;
// 1. HP 포션
PotionRecipe hpPotion;

// 2. 스태미나포션
PotionRecipe staminaPotion;
//----------------------------

void ShowAllRecipes()
{
	if (potionRecipe.size() == 0)
	{
		cout << "레시피가 존재하지 않습니다." << endl;
		cout << endl;
	}
	else
	{
		cout << "전체 레시피" << endl;
		for (int i = 0; i < potionRecipe.size(); i++)
		{
			cout << "-> " << potionRecipe[i].name << ": " << potionRecipe[i].material[0] << " x" << potionRecipe[i].material_num[0];

			if (potionRecipe[i].material.size() != 2)
			{
				cout << endl;
			}
			else
			{
				cout << ", " << potionRecipe[i].material[1] << " x" << potionRecipe[i].material_num[1] << endl;
			}

			cout << endl;
		}
	}
}

void SearchByName(string name)
{
	int count = 0;
	for (int i = 0; i < potionRecipe.size(); i++)
	{
		if (name == potionRecipe[i].name)
		{
			count++;
			cout << "-> " << potionRecipe[i].name << ": " << potionRecipe[i].material[0] << " x" << potionRecipe[i].material_num[0];

			if (potionRecipe[i].material.size() != 2)
			{
				cout << endl;
				cout << endl;
			}
			else
			{
				cout << ", " << potionRecipe[i].material[1] << " x" << potionRecipe[i].material_num[1] << endl;
				cout << endl;
			}
		}
	}
	if (count == 0)
	{
		cout << "찾을 수 없습니다." << endl;
		cout << endl;
	}
}

void SearchByMaterial(string name)
{
	int count = 0;
	for (int i = 0; i < potionRecipe.size(); i++)
	{
		for (int j = 0; j < potionRecipe[i].material.size(); j++)
		{
			if (name == potionRecipe[i].material[j])
			{
				count++;
				cout << "-> " << potionRecipe[i].name << ": " << potionRecipe[i].material[0] << " x" << potionRecipe[i].material_num[0];

				if (potionRecipe[i].material.size() != 2)
				{
					cout << endl;
					cout << endl;
				}
				else
				{
					cout << ", " << potionRecipe[i].material[1] << " x" << potionRecipe[i].material_num[1] << endl;
					cout << endl;
				}
			}
		}
	}
	if (count == 0)
	{
		cout << "찾을 수 없습니다." << endl;
		cout << endl;
	}
}
// 재고 관리 + 포션 지급 / 반환 ---------------------------------------------
int MAX_STOCK = 3;

void DispensePotion(map<string, int>& potion, string name)
{
	auto it = potion.find(name);
	
	if (it != potion.end())
	{
		if (it->second == 0)
		{
			cout << "-> " << name << "지급 실패: 재고 없음!" << endl;
		}
		else
		{
			it->second--;
			cout << "-> " << name << "지급   (재고: " << it->second << ")" << endl;
		}
	}
	else
	{
		cout << "일치하는 이름의 포션이 없습니다." << endl;
	}

	cout << endl;
}

void ReturnPotion(map<string, int>& potion, string name)
{
	auto it = potion.find(name);

	if (it != potion.end())
	{
		if (it->second == MAX_STOCK)
		{
			cout << "재고가 꽉 차 있습니다." << endl;
		}
		else
		{
			it->second++;
			cout << "-> 공병 변환   (재고: " << it->second << ")" << endl;
		}
	}

	cout << endl;
}

void GetStock(map<string, int>& potion, string name)
{
	auto it = potion.find(name);

	if (it != potion.end())
	{
		cout << name << " 재고: " << it->second << endl;
	}
	else
	{
		cout << "일치하는 이름의 포션이 존재하지 않습니다." << endl;
	}

	cout << endl;
}
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
	int HP_Potion;
	int MP_Potion;
	setpotion(5, &HP_Potion, &MP_Potion);
	int UpgradeNum;
	bool isGameeStart = false;

	cout << "* HP 포션 5개, MP 포션 5개가 기본 지급되었습니다." << endl;
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
			if (HP_Potion == 0)
			{
				cout << "* 보유하신 HP 포션이 부족합니다." << endl;
				cout << "" << endl;
				break;
			}

			HP_Potion--;
			stat[0] += 20;
			cout << "* HP가 20 증가했습니다. (현재 HP: " << stat[0] << " / " << "HP 포션 차감 : 남은 포션 " << HP_Potion << "개)" << endl;
			cout << "" << endl;
			break;
		}
		case 2:
		{
			if (MP_Potion == 0)
			{
				cout << "* 보유하신 MP 포션이 부족합니다." << endl;
				cout << "" << endl;
				break;
			}

			MP_Potion--;
			stat[1] += 20;
			cout << "* MP가 20 증가했습니다. (현재 MP: " << stat[1] << " / " << "MP 포션 차감: 남은 포션 " << MP_Potion;
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

	
	while (1)
	{
		cout << "선택: ";
		cin >> ClassNum;

		if (ClassNum == 1 || ClassNum == 2 || ClassNum == 3 || ClassNum == 4)
		{
			break;
		}
		else
		{
			cout << "직업을 다시 선택해 주세요!" << endl;
		}
	}
		cout << "" << endl;
		Player* player = nullptr;

		switch (ClassNum)
		{
		case 1:
		{
			player = new Warrior(CharacterName, stat[0], stat[1], stat[0], stat[1], stat[2], stat[3], 0, 100, 1);
			cout << "* 거대한 대검을 내려친다!" << endl;
			player->printPlayerStatus();
			break;
		}
		case 2:
		{
			player = new Mage(CharacterName, stat[0], stat[1], stat[0], stat[1], stat[2], stat[3], 0, 100, 1);
			cout << "* 파이어볼을 발사한다!" << endl;
			player->printPlayerStatus();
			break;
		}
		case 3:
		{
			player = new Thief(CharacterName, stat[0], stat[1], stat[0], stat[1], stat[2], stat[3], 0, 100, 1);
			cout << "* 재빠른 화살을 날린다!" << endl;
			player->printPlayerStatus();
			break;
		}
		case 4:
		{
			player = new Archer(CharacterName, stat[0], stat[1], stat[0], stat[1], stat[2], stat[3], 0, 100, 1);
			cout << "* 날카로운 단검으로 찌른다!" << endl;
			player->printPlayerStatus();
			break;
		}
		}
	
	// 게임 실행

		// 포션 레시피
		// 1. HP포션
		hpPotion.name = "HP포션";
		hpPotion.material.push_back("허브");
		hpPotion.material_num.push_back(1);
		hpPotion.material.push_back("맑은 물");
		hpPotion.material_num.push_back(1);
		potionRecipe.push_back(hpPotion);

		// 2. 스태미나포션
		staminaPotion.name = "스태미나포션";
		staminaPotion.material.push_back("허브");
		staminaPotion.material_num.push_back(1);
		staminaPotion.material.push_back("베리");
		staminaPotion.material_num.push_back(1);
		potionRecipe.push_back(staminaPotion);

		Inventory<Item> inventory(3, 0);

		Item HP_Potions{ "HP 포션", 50 };
		Item MP_Potions{ "MP 포션", 50 };

		inventory.AddItem(HP_Potions);
		inventory.AddItem(MP_Potions);

		map<string, int> potionStock_;
		potionStock_["HP 포션"] = MAX_STOCK;
		potionStock_["MP 포션"] = MAX_STOCK;

		vector<Dungeon> dungeon;

		bool SlimeRoom = true;
		bool GoblinRoom = false;
		bool OwkRoom = false;
		bool OgreRoom = false;
		bool DragonRoom = false;

		bool SlimeRoomClear = false;
		bool GoblinRoomClear = false;
		bool OwkRoomClear = false;
		bool OgreRoomClear = false;
		
		while (1)
		{
			int MainMenu;
			int InvenNum = 1;


			cout << " === 메인 메뉴 === " << endl;
			cout << "1. 던전 입장" << endl;
			cout << "2. 인벤토리 확인" << endl;
			cout << "3. 포션 제작소" << endl;
			cout << "4. 게임 종료" << endl;
			cout << endl;

			

			while (1)
			{
				cout << "선택: ";
				cin >> MainMenu;

				if (ClassNum == 1 || ClassNum == 2 || ClassNum == 3 || ClassNum == 4)
				{
					break;
				}
				else
				{
					cout << "다시 선택해 주세요!" << endl;
				}
			};

			cout << endl;

			switch (MainMenu)
			{
			case 1: // 던전 입장
			{
				bool IsBattle = true;
				bool IsUseItem = true;
				cout << "던전 입장을 선택하셨습니다." << endl;
				cout << "던전에 입장합니다." << endl;
				cout << endl;

				cout << "[ 던전 1층 ]" << endl;

				cout << endl;

				Slime* slime = new Slime("슬라임", 200, 10, 30, "슬라임의 끈적한 젤리", 10, 20);
				dungeon.push_back({ slime->getName(), slime->getHp(), slime->getPower(), 1 });

				Goblin* goblin = new Goblin("고블린", 100, 30, 10, "고블린의 녹슨 단검", 30, 30);
				dungeon.push_back({ goblin->getName(), goblin->getHp(), goblin->getPower(), 2 });

				Owk* owk = new Owk("오크", 300, 40, 30, "오크의 날카로운 쌍도끼", 100, 40);
				dungeon.push_back({ owk->getName(), owk->getHp(), owk->getPower(), 3 });

				Ogre* ogre = new Ogre("오우거", 500, 50, 50, "오우거의 내단", 5000, 50);
				dungeon.push_back({ ogre->getName(), ogre->getHp(), ogre->getPower(), 4 });

				Dragon* dragon = new Dragon("드래곤", 1000, 100, 100, "드래곤 하트", 10000, 100);

				cout << "입장할 던전룸을 선택하세요." << endl;
				cout << endl;

				cout << dungeon[0].roomNum << "번 방: " << dungeon[0].name << "(HP " << dungeon[0].hp << ", 공격력 " << dungeon[0].power << ")" << endl;
				cout << dungeon[1].roomNum << "번 방: " << dungeon[1].name << "(HP " << dungeon[1].hp << ", 공격력 " << dungeon[1].power << ")" << endl;
				cout << dungeon[2].roomNum << "번 방: " << dungeon[2].name << "(HP " << dungeon[2].hp << ", 공격력 " << dungeon[2].power << ")" << endl;
				cout << dungeon[3].roomNum << "번 방: " << dungeon[3].name << "(HP " << dungeon[3].hp << ", 공격력 " << dungeon[3].power << ")" << endl;

				

				while (!DragonRoom)
				{
					cout << endl;
					cout << "입장할 던전룸: ";
					int DungeonRoomNum;
					cin >> DungeonRoomNum;

					switch (DungeonRoomNum)
					{
						case 1:
						{
							if (SlimeRoomClear)
							{
								cout << "이미 클리어 했습니다." << endl;
								cout << endl;
								break;
							}

							cout << endl;
							MonsterBattle(CharacterName, player, slime, inventory);
							SlimeRoomClear = true;
							GoblinRoom = true;
							break;
						}
						case 2:
						{
							if (GoblinRoomClear)
							{
								cout << "이미 클리어 했습니다." << endl;
								cout << endl;
								break;
							}

							if (GoblinRoom)
							{
								cout << endl;
								MonsterBattle(CharacterName, player, goblin, inventory);
								GoblinRoomClear = true;
								OwkRoom = true;
								break;
							}
							else
							{
								cout << "이전 방을 먼저 클리어 해주세요" << endl;
								cout << endl;
								break;
							}
							break;
						}
						case 3:
						{
							if (OwkRoomClear)
							{
								cout << "이미 클리어 했습니다." << endl;
								cout << endl;
								break;
							}

							if (OwkRoom)
							{
								cout << endl;
								MonsterBattle(CharacterName, player, owk, inventory);
								OwkRoomClear = true;
								OgreRoom = true;
								break;
							}
							else
							{
								cout << "이전 방을 먼저 클리어 해주세요" << endl;
								cout << endl;
								break;
							}
							break;
						}
						case 4:
						{
							if (OgreRoomClear)
							{
								cout << "이미 클리어 했습니다." << endl;
								cout << endl;
								break;
							}

							if (OgreRoom)
							{
								cout << endl;
								MonsterBattle(CharacterName, player, ogre, inventory);
								OgreRoomClear = true;
								DragonRoom = true;
								break;
							}
							else
							{
								cout << "이전 방을 먼저 클리어 해주세요" << endl;
								cout << endl;
								break;
							}
							break;
						}
					}
				}
					cout << endl;

					cout << "모든 던전룸 클리어 완료!" << endl;
					cout << "★ 보스방 개방!" << endl;
					cout << "보스 드래곤 등장! " << endl;
					cout << endl;
					MonsterBattle(CharacterName, player, dragon, inventory);
					cout << endl;

					cout << "드래곤을 처치했습니다!" << endl;

					cout << "던전을 클리어 하셨습니다." << endl;
					cout << "게임을 종료합니다." << endl;

					delete slime;
					delete goblin;
					delete owk;
					delete ogre;
					delete dragon;
					delete player;
					
					exit(0);
					
					break;
				}
				case 2: // 인벤토리 확인
				{
					cout << "인벤토리 확인을 선택하셨습니다." << endl;
					cout << endl;
					cout << "[ 인벤토리 (" << inventory.getSize() << "/10) ]" << endl;

					inventory.PrintAllItems();
					
					cout << endl;
					cout << "인벤토리 확인이 끝났습니다." << endl;
					cout << "메인 메뉴로 돌아갑니다." << endl;
					cout << endl;

					break;
				}
				case 3: // 포션 제작소
				{
					cout << "포션 제작소를 선택하셨습니다." << endl;
					cout << "포션 제작소에 입장합니다." << endl;
					cout << endl;

					cout << "=== 포션 제작소 ===" << endl;
					cout << "1. 전체 레시피 보기" << endl;
					cout << "2. 포션 이름으로 검색" << endl;
					cout << "3. 재료로 검색" << endl;
					cout << "4. 포션 재고 관리" << endl;
					cout << "0. 돌아가기" << endl;
					cout << endl;

					bool IsRunning = true;
					while (IsRunning)
					{
						int PotionNum;
						cout << "포션 제작소 번호 선택: ";
						cin >> PotionNum;
						cout << endl;

						switch (PotionNum)
						{
						case 1:
						{
							ShowAllRecipes();
							break;
						}
						case 2:
						{
							string SearchPotionName = "";
							cout << "검색할 포션 이름: ";
							cin >> SearchPotionName;

							SearchByName(SearchPotionName);
							break;
						}
						case 3:
						{
							string SearchMaterialName = "";
							cout << "검색할 재료: ";
							cin >> SearchMaterialName;

							SearchByMaterial(SearchMaterialName);
							break;
						}
						case 4:
						{
							string PotionStock = "";
							cout << "관리할 포션 이름: ";
							
							// 이 코드 전에 메뉴 선택 등 때문에 cin >>을 썼으면 
							// 버퍼에 엔터(\n) 찌꺼기가 남아있을 수 있어서 비워주고
							cin.ignore(); 
							
							// getline을 사용 (띄어쓰기 포함해서 한 줄 통째로 저장됨)
							getline(cin, PotionStock);
							bool isCheckStock = true;

							while (isCheckStock)
							{
								cout << "1. 포션 출고" << endl;
								cout << "2. 포션 입고" << endl;
								cout << "3. 포션 재고 확인" << endl;
								cout << "4. 돌아가기" << endl;

								int StockNum;
								cout << "재고 관리 번호 선택: ";
								cin >> StockNum;

								cout << endl;

								switch (StockNum)
								{
									case 1:
									{
										DispensePotion(potionStock_, PotionStock);
										break;
									}
									case 2:
									{
										ReturnPotion(potionStock_, PotionStock);
										break;
									}
									case 3:
									{
										GetStock(potionStock_, PotionStock);
										break;
									}
									case 4:
									{
										isCheckStock = false;
										break;
									}
								}
							}
							break;
						}
						case 0:
						{
							cout << "메인 메뉴로 돌아갑니다." << endl;
							cout << endl;
							IsRunning = false;
							break;
						}
						}
					}
					
					break;
				}
				case 4: // 게임 종료
				{
					delete player;
					exit(0);
				}
			}
		}

	// -----------------------------------------------------------------------
	// 
	// 
	// 
	// 
	// 








	

	
}