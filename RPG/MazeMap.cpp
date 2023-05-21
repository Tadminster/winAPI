#include "MazeMap.h"

MazeMap::MazeMap(int c = 16, int r = 15) : cols(c), rows(r)
{
	this->map = new std::string * [cols];
	for (int i = 0; i < cols; i++)
		this->map[i] = new std::string[rows];
}

void MazeMap::createMap()
{
	const std::string maze_map[16][15] =
	{
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", "P", ".", ".", "?", "?", "H", ".", ".", "B", ".", ".", "."},
		{".", ".", ".", "?", ".", ".", "?", ".", ".", ".", ".", "?", ".", ".", "."},	// 5
		{".", ".", ".", "?", ".", "?", "?", "?", "?", "?", "?", "?", ".", ".", "."},
		{".", ".", ".", "?", "?", "?", ".", ".", "?", ".", ".", "?", ".", ".", "."},
		{".", ".", ".", ".", "?", ".", ".", ".", "?", ".", ".", "?", ".", ".", "."},
		{".", ".", ".", ".", "?", ".", ".", ".", "?", ".", ".", "?", ".", ".", "."},
		{".", ".", ".", ".", "?", ".", ".", ".", "?", ".", ".", "?", ".", ".", "."},	// 10
		{".", ".", ".", ".", "?", ".", ".", ".", "?", ".", ".", "?", ".", ".", "."},
		{".", ".", ".", "H", "?", "?", "?", "?", "?", ".", ".", "?", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", ".", "?", "?", "?", "?", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."},	// 15
		{".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", ".", "."}
	};

	for (int i = 0; i < this->cols; i++)
		for (int j = 0; j < this->rows; j++)
			this->map[i][j] = maze_map[i][j];
}

MazeMap::~MazeMap()
{
	for (int i = 0; i < rows; ++i)
		delete[] map[i];
	delete[] map;
}

/*  
 * \brief 
 * \param next_room 다음방
 * \param player 유저
 */
void MazeMap::startMapEvent(std::string& next_room, class RPG_Player* player)
{
	if (next_room != ".") // 벽이 아니면 SP 감소
		player->setSp(1, 2);

	if (next_room == "?")
	{
		MazeMap::enterQuestionMark(player);
	}
	else if (next_room == "B")
	{
		std::cout
			<< "[!] 보스방 입장" << std::endl
			<< "싸늘하다.. 가슴에 위기가 날아와 꽂힌다. ";
		MazeMap::battleEvent(player, 9);
	}
	else if (next_room == "H")
	{
		MazeMap::room_FountainOfRecovery(player);
	}
	
}

void MazeMap::enterQuestionMark(RPG_Player* player)
{
	ioSystem iosystem;
	int random = rand() % 100;
	
	// 테스트용 
	//random = 94;

	// 미확인 방 이벤트

	// 0~19 : 아무것도 없는 빈방.
	// 20~39 : 상자가 있는 방.
	// 40~59 : 몬스터가 있는 방.
	// 60~79 : 함정이 있는 방.
	// 80~89 : 회복의 샘
	// 90~94 : 상인의 방
	// 95~99 : 보물의 방

	if (random < 20)
	{
		// 0~19 : 아무것도 없는 빈방.
		std::cout 
			<< "아무것도 없는 빈방이다. 잠시 쉬었다 가자.." << std::endl
			<< "휴식으로 플레이어의 체력이 5, 기력이 10 회복되었습니다." << std::endl;
		player->setHp(5, 1);
		player->setSp(10, 1);
	}
	else if (random < 40)
	{
		// 20~39 : 상자가 있는 방.
		std::cout
			<< "허름한 상자가 하나 놓여있다." << std::endl
			<< "[1]열어본다 [2]무시한다: ";
		int PlayerInput{ iosystem.input_number(1, 2) };
		MazeMap::room_NormalChest(player, PlayerInput);
	}

	else if (random < 60)
	{
		// 40~59 : 몬스터가 있는 방.
		std::cout << "어두운 공간에서 무언가가 튀어나왔다." << std::endl;

		MazeMap::battleEvent(player, 1);
	}

	else if (random < 80)
	{
		// 60~79 : 함정이 있는 방.

		std::cout << "두가지 버튼이 있다. 어느것이 안전한 버튼일까?" << std::endl;
		std::cout << "[1]첫번째 [2]두번째 : ";
		int playerInput{ iosystem.input_number(1, 2) };

		MazeMap::room_Trap(player, playerInput);
	}

	else if (random < 90)
	{
		// 80~89 : 회복의 샘
		MazeMap::room_FountainOfRecovery(player);
	}

	else if (random < 95)
	{
		// 90~94 : 상인의 방
		std::cout << "정체를 모를 노인이 앉아있다." << std::endl;
		trade(player);
	}
	else if (random < 100)
	{
		// 95~99 : 보물의 방
		std::cout << "금색으로 빛나는 상자가 놓여있다." << std::endl;
		MazeMap::room_RareChest(player);
	}
	(void) _getch();
}

void MazeMap::battleEvent(class RPG_Player* player, int monsterType)
{
	BattleSystem* battleSystem = new BattleSystem(player);	// 전투시스템
	Monster* monster = nullptr;

	int randomStatus{ 1000 };
	if (monsterType == 1)
	{
		int randomMonster{ rand() % 3 };
		// 0 : 고블린
		// 1 : 슬라임
		// 2 : 코볼트
		if (randomMonster == 0)
		{
			int randomHp{ randomStatus % 10 + 25 };
			int randomDmg{ randomStatus % 2 + 6 };
			int randomDef{ randomStatus % 2 };
			monster = new Monster("고블린", randomHp, randomDmg, randomDef, 20);
		}
		else if (randomMonster == 1)
		{
			int randomHp{ randomStatus % 5 + 20 };
			int randomDmg{ randomStatus % 2 + 4 };
			int randomDef{ randomStatus % 3 };
			monster = new Monster("슬라임", randomHp, randomDmg, randomDef, 20);
		}
		else if (randomMonster == 2)
		{
			int randomHp{ randomStatus % 10 + 20 };
			int randomDmg{ randomStatus % 2 + 7 };
			int randomDef{ randomStatus % 2 };
			monster = new Monster("코볼트", randomHp, randomDmg , randomDef, 25);
		}


	}
	else if (monsterType == 2)
	{
		int randomHp{ randomStatus % 10 + 20 };
		int randomDmg{ randomStatus % 4 + 7 };
		int randomDef{ randomStatus % 2 };
		monster = new Monster("미믹", randomHp, randomDmg, randomDef, 20);
	}
	else if (monsterType == 9)
	{
		int randomHp{ randomStatus % 20 + 100 };
		int randomDmg{ randomStatus % 5 + 10 };
		int randomDef{ randomStatus % 2 + 3 };
		monster = new Monster("[보스]", randomHp, randomDmg, randomDef, 500);
	}

	if (monster != nullptr)
	{
		std::cout << "저 형체는.. " << monster->getName() << "!?" << std::endl;
		
		std::cout << "계속하려면 아무키나 입력하세요." << std::endl;
		(void) _getch();
		
		battleSystem->setEnemy(monster);
		battleSystem->startBattle();
	}

	delete battleSystem;
	delete monster;
}

std::string& MazeMap::getMap(int y, int x)
{
	return this->map[y][x];
}

/* 맵사이즈 가져오기 (col==0, row==1) */
int MazeMap::getMapSize(int arrow)
{
	if (arrow == 0)
		return this->cols;
	else
		return this->rows;
}

void MazeMap::setMapElement(int y, int x, std::string mapData)
{
	this->map[y][x] = mapData;
}

void MazeMap::swapMap(int playerY, int playerX, int targetY, int targetX)
{
	std::swap(this->map[playerY][playerX], this->map[targetY][targetX]);
}

void MazeMap::room_Trap(RPG_Player* player, int playerInput)
{
	const int random_bottom{ rand() % 2 + 1 };
	if (playerInput == random_bottom)
	{
		const int random_dmg{ rand() % 11 + 5 };
		std::cout
			<< "'으악!! 무언가 몸을 찔렀다!'" << std::endl
			<< "함정을 밟아 플레이어의 체력이 "
			<< random_dmg << "감소했습니다." << std::endl;
		player->setHp(random_dmg, 2);
	}
	else
		std::cout << "아무런 위협없이 문이 열렸다. 휴.. " << std::endl;
}

void MazeMap::room_FountainOfRecovery(RPG_Player* player)
{
	const int max_heal = player->getMaxHp() * 0.2;
	const int actual_heal = std::min(max_heal, (player->getMaxHp() - player->getHp()));
	std::cout 
		<< "맑은 기운이 느껴지는 우물이다." << std::endl
		<< "전체 체력의 20% 회복: 체력+"
		<< actual_heal << std::endl;

	player->setHp(actual_heal, 1);
}

void MazeMap::room_NormalChest(RPG_Player* player, int playerInput)
{
	if (playerInput == 1)
	{
		// 0 : 아무것도 없는 빈 상자
		// 1 : 아이템이 들어있는 상자
		// 2 : 몬스터가 있는 상자
		// 3 : 가시에 찔림
		if (const int random{ rand() % 4 + 1 };
			random == 1)
		{
			std::cout << "아무것도 들어있지 않은 빈 상자다." << std::endl;
			return;
		}
		else if (random == 2)
		{
			std::cout << "무언가 쓸만한 도구가 들어있다." << std::endl;
			if (const int random_items = rand() % 4;
				random_items == 0)
			{
				std::cout << "스스로 밝게 빛나는 돌이다." << std::endl;
				player->addItem(new Armor("발광석", 0, 0, 1), 1);
			}
			else if (random_items == 1)
			{
				std::cout << "투박하지만 쓸만해보이는 몽둥이다" << std::endl;
				player->addItem(new Weapon("목봉", 200, 6), 1);
				player->setDamage(6, true);
			}
			else if (random_items == 2)
			{
				std::cout << "무언가 빨갛게 빛나는 액체다." << std::endl;
				Item* hpPotion = new Item("HP포션", 50);
				hpPotion->setInfo("체력을 회복하는 물약. 마시면 20의 체력을 회복합니다.");
				player->addItem(hpPotion, 1);
			}
			else if (random_items == 3)
			{
				std::cout << "무언가 파랗게 빛나는 액체다." << std::endl;
				Item* spPotion = new Item("SP포션", 50);
				spPotion->setInfo("스태미나를 회복하는 물약. 마시면 30의 스태미나를 회복합니다.");
				player->addItem(spPotion, 1);
			}

		}
		else if (random == 3)
		{
			std::cout << "상자가 갑자기 움직인다..?" << std::endl;
			MazeMap::battleEvent(player, 2);
		}
		else if (random == 4)
		{
			std::cout << "상자 안에 가시가 아무렇게나 얽혀있다." << std::endl;
			std::cout << "가시에 찔려 플레이어 체력이 5 감소했습니다." << std::endl;
			player->setHp(5, 2);
		}
	}
	else if (playerInput == 2)
		return;
}

void MazeMap::room_RareChest(RPG_Player* player)
{
	if (const int random{ rand() % 4 + 1 };
			random == 1)
	{
		auto* shining_armor = new Armor("빛나는 갑옷", 250, 4, 1);
		shining_armor->setInfo("갑옷에서 은은한 빛이난다. 덕분에 시야가 넓어졌지만 시선은 더 잘 끌릴것 같다.");
		player->addItem(shining_armor, 1);
	}
	else if (random == 2)
	{
		auto* sharp_sword = new Weapon("잘 벼려진 검", 200, 10);
		sharp_sword->setInfo("날이 무섭도록 서 있는 검");
		player->addItem(sharp_sword, 1);

	}
	else if (random == 3)
	{
		auto* clear_potion = new Item("맑은기운이 가득한 포션", 150);
		clear_potion->setInfo("각종 상태이상을 해제하고 일정량의 체력을 회복한다.");
		player->addItem(clear_potion, 1);
	}
	else if (random == 4)
	{
		auto* turbid_potion = new Item("해로운 기운이 가득한 포션", 150);
		turbid_potion->setInfo("큰 데미지와 랜덤한 상태이상을 가한다");
		player->addItem(turbid_potion, 1);
	}
}

void MazeMap::printMap(class RPG_Player* player)
{
	const int start_row = std::max(player->getLocation(0) - player->getVisibleRadius(), 0);
	const int end_row = std::min(player->getLocation(0) + player->getVisibleRadius(), this->cols - 1);

	const int start_col = std::max(player->getLocation(1) - player->getVisibleRadius(), 0);
	const int end_col = std::min(player->getLocation(1) + player->getVisibleRadius(), this->rows - 1);

	std::cout
		<< "\033[0;35mP\033[0m 플레이어,  "
		<< "?: 미탐험 지역,  "
		<< "\033[1;36mH\033[0m 우물,  "
		<< "\033[1;31mB\033[0m 보스"
		//<< "\033[0;35mB\033[0m: 보스"
		<< std::endl << std::endl;

	// 로드시 플레이어 사라지는 버그 대응
	this->map[player->getLocation(0)][player->getLocation(1)] = "P";

	for (int row = start_row; row <= end_row; row++)
	{
		for (int col = start_col; col <= end_col; col++)
		{
			// 방 경계 앞부분 출력
			if (this->map[row][col] != ".")
				std::cout << "[ ";
			else
				std::cout << "  ";

			if (this->map[row][col] == "X")
				std::cout << " ";
			else if (this->map[row][col] == "P")
				std::cout << "\033[0;35m" << this->map[row][col] << "\033[0m";
			else if (this->map[row][col] == "B")
				std::cout << "\033[1;31m" << this->map[row][col] << "\033[0m";
			else if (this->map[row][col] == "H")
				std::cout << "\033[1;36m" << this->map[row][col] << "\033[0m";
			else if (this->map[row][col] == ".")
				std::cout << " ";
			else
				std::cout << this->map[row][col];

			// 방 경계 뒷부분 출력
			if (this->map[row][col] != ".")
				std::cout << " ]";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
}
