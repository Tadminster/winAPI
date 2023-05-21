#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
const int DECK_SIZE = 52;

class TrumpCard
{
private:
	string shape;
	int number;

public:
	TrumpCard(int shape, int number)
	{
		if (shape == 0)
			this->shape = "♥";
		else if (shape == 1)
			this->shape = "◆";
		else if (shape == 2)
			this->shape = "♠";
		else if (shape == 3)
			this->shape = "♣";
		this->number = number;
	}

	int getNumber() const
	{
		return this->number;
	}

	string getShape() const
	{
		return this->shape;
	}
};

class Player
{
private:
	string	name;
	string	status;
	int		seed	{ 10000 };
	int		sum		{ 0 };
	int		aCnt	{ 0 };
	bool	isDone	{ false };
	vector<TrumpCard> hand;

public:
	Player(string name)
	{
		this->name = name;
	}

	void addCardToHand(const TrumpCard& card)
	{
		this->hand.push_back(card);
		int x = card.getNumber();
		this->sum += (x > 10 ? 10 : x);
	}

	void handClear()
	{
		hand.clear();
	}

	void getHand()
	{
		int side{ 5 };
		for (int i = 1; i <= side; i++) {
			// 1st ~ 5th card
			for (int j = 0; j < hand.size(); j++)
			{
				this->cardPrintBody(i, side, hand[j].getShape(), hand[j].getNumber());
				std::cout << "\t";
			}
			std::cout << std::endl;
		}
	}

	void cardPrintBody(int i, int side, string shape, int number) const
	{
		for (int j = 1; j <= side; j++) {
			// Outline
			if (i == 1 || i == side || j == 1 || j == side)
				std::cout << "* ";
			// Symbol
			else if (i == 2 && j == 2)
				std::cout << "\033[1;36m" << shape << "\033[0m ";
			// Number
			else if (i == side - 1 && j == side - 1)
			{
				if (number == 1) std::cout << "\033[1;36mA ";
				else if (number == 10) std::cout << "\033[1;36m10";
				else if (number == 11) std::cout << "\033[1;36mK ";
				else if (number == 12) std::cout << "\033[1;36mQ ";
				else if (number == 13) std::cout << "\033[1;36mK ";
				else std::cout << "\033[1;36m" << number << " ";
			}
			// Inner blank space
			else
				std::cout << "  ";

			std::cout << "\033[0m";
		}
	}

	bool selectA()
	{
		int temp{ 0 };
		for (auto& n : this->hand)
			if (n.getNumber() == 1) temp++;

		if (this->aCnt < temp)
		{
			std::cout << std::endl;
			std::cout << "[1] 1     [2] 11" << std::endl;
			std::cout << "A 카드를 몇으로 사용하시겠습니까: ";

			while (true)
			{
				string input;
				std::cin >> input;
				if (input == "1") 
					break;
				else if (input == "2")
				{
					this->sum += 10;
					break;
				}
				else 
					std::cout << "잘못된 입력입니다." << std::endl;
			}
			this->aCnt++;
			return true;
		}
		return false;
	}

	string getName()
	{
		return this->name;
	}

	void setStatus(string str)
	{
		this->status = str;
	}

	string getStatus()
	{
		return this->status;
	}

	int getSeed()
	{
		return this->seed;
	}

	void setSeed(int x)
	{
		this->seed += x;
	}

	int getSum()
	{
		return this->sum;
	}

	void setInit(int x)
	{
		this->sum = x;
		this->aCnt = x;
	}

	void setIsDone(bool b)
	{
		this->isDone = b;
	}

	bool getIsDone()
	{
		return this->isDone;
	}

};

void mainImage();
bool menuInput();
void mainGame();
void shuffle(vector <unique_ptr<TrumpCard>>& deck);
void printSystem(Player* player, Player** players, int numOfPlayers);
void addCard(Player* players, vector <unique_ptr<TrumpCard>>& deck, int& temp);

int main()
{
	srand((unsigned int)time(NULL));
	while (menuInput())
	{
		mainGame();
	}
}

bool menuInput()
{
	std::string input;
	while (1)
	{
		mainImage();
		std::cout << "[1] 시작하기" << std::endl;
		std::cout << "[2] 종료하기" << std::endl;
		std::cout << "원하는 옵션을 선택하세요: ";
		std::cin >> input;
		if (input == "1") return true;
		else if (input == "2") exit(1);
		else std::cout << "올바른 옵션을 선택하세요." << std::endl;
	}
}

void mainGame()
{
	std::system("cls");

	// 덱 만들기
	vector <unique_ptr<TrumpCard>> deck;

	// 덱 초기화
	for (int shape = 0; shape < 4; shape++) {
		for (int number = 1; number <= 13; number++) {
			deck.emplace_back(make_unique<TrumpCard>(shape, number));
		}
	}

	// 인원수 입력 받기
	std::cout << "플레이어 수 입력: ";
	int numOfPlayers;
	std::cin >> numOfPlayers;

	// 딜러, 플레이어 생성
	Player* dealer = new Player("딜러");
	Player** players = new Player*[numOfPlayers];
	for (int i = 0; i < numOfPlayers; i++)
	{
		std::cout << "[" << i << "]번 플레이어 이름 입력: ";
		string name;
		std::cin >> name;
		players[i] = new Player(name);
	}
	std::system("cls");

	while (true)
	{
		// 덱 섞기
		shuffle(deck);

		// deck, sum 초기화 + 덱 분배
		int temp{ 0 };
		for (int i = 0; i < numOfPlayers; i++)
		{
			players[i]->handClear();
			players[i]->setInit(0);
			players[i]->setIsDone(false);
			players[i]->addCardToHand(*deck[temp++]);
			players[i]->addCardToHand(*deck[temp++]);
		}
		dealer->handClear();

		// 플레이어 시스템 출력
		for (int i = 0; i < numOfPlayers; i++)
		{
			while (true)
			{
				// 화면 지우고 새로 출력
				std::system("cls");
				printSystem(players[i], players, numOfPlayers);

				// 버스트 확인
				if (players[i]->getSum() > 21)
				{
					std::cout << std::endl;
					players[i]->setStatus("\033[1;31m버스트\033[0m");
					players[i]->setIsDone(true);
					players[i]->setSeed(-1000);
					std::system("pause");
					break;
				}

				// A카드 확인
				if (players[i]->selectA())
				{
					std::system("cls");
					printSystem(players[i], players, numOfPlayers);
				}

				// 카드 추가로 받기
				std::cout << std::endl;
				std::cout << "[1]카드 더 받는다   [2]받지않는다" << std::endl;
				std::cout << "카드를 더 받으시겠습니까: ";
				string input;
				std::cin >> input;

				if (input == "1")
					players[i]->addCardToHand(*deck[temp++]);
				else if (input == "2")
				{
					players[i]->setIsDone(true);
					break;
				}
				else
					std::cout << "잘못된 입력입니다." << std::endl;
			}
		}

		// 딜러 덱분배, 출력
		dealer->addCardToHand(*deck[temp++]);

		do
		{
			//화면 지우고 새로 출력
			std::system("cls");
			dealer->addCardToHand(*deck[temp++]);
			std::cout << std::endl;
			printSystem(dealer, players, numOfPlayers);
			for (int i = 0; i<10; i++)
				Sleep(100);
		} while (dealer->getSum() < 17);

		// 승패 
		for (int i = 0; i < numOfPlayers; i++)
		{
			if (players[i]->getSum() < 22 && dealer->getSum() > 21)
			{
				players[i]->setSeed(1000);
				players[i]->setStatus("\033[1;34m승리\033[0m");
			}
			else if (players[i]->getSum() < 22)
			{
				if (players[i]->getSum() == dealer->getSum())
				{
					players[i]->setStatus("무승부");
				}
				else if (players[i]->getSum() < dealer->getSum())
				{
					players[i]->setSeed(-1000);
					players[i]->setStatus("\033[1;31m패배\033[0m");
				}
				else if (players[i]->getSum() > dealer->getSum())
				{
					players[i]->setSeed(1000);
					players[i]->setStatus("\033[1;34m승리\033[0m");
				}
			}
			else
			{
				players[i]->setSeed(-1000);
				players[i]->setStatus("\033[1;31m패배\033[0m");
			}
		}
	
		//마지막 결과 출력
		std::system("cls");
		printSystem(dealer, players, numOfPlayers);

		std::cout << std::endl;
		std::cout << "이번 라운드가 종료되었습니다." << std::endl;
		std::system("pause");

		if (players[0]->getSeed() > 0) continue;
		else if (players[0]->getSeed() < 1)
		{
			std::cout << "플레이어가 모든 돈을 잃어 패배했습니다." << std::endl;
			break;
		}
	}

	return;
}

/* 섞기 (덱) */
void shuffle(vector <unique_ptr<TrumpCard>>& deck)
{
	for (int i = 0; i < DECK_SIZE; i++) {
		int j = rand() % DECK_SIZE;
		std::swap(deck[i], deck[j]);
	}
}

void printSystem(Player* player, Player** players, int numOfPlayers)
{
	for (int i = 0; i < numOfPlayers; i++)
	{
		if (players[i]->getIsDone())
		{
			std::cout << "[" << players[i]->getName() << "] 의 손패";
			std::cout << "\t소지금: " << players[i]->getSeed();
			std::cout << "\t\t합: " << players[i]->getSum();
			std::cout << "\t" << players[i]->getStatus() << std::endl;
			players[i]->getHand();
			std::cout << std::endl;
		}
	}

	std::cout << "[" << player->getName() << "] 의 손패";
	if (!(player->getName() == "딜러"))
		std::cout << "\t소지금: " << player->getSeed();
	else cout << "\t\t";
	std::cout << "\t\t합: " << player->getSum();
	std::cout << std::endl;
	player->getHand();
}

void addCard(Player* players, vector <unique_ptr<TrumpCard>>& deck, int& temp)
{
	while (true)
	{
		if (players->getSum() > 21) return;

		std::cout << std::endl;
		std::cout << "[1]카드 더 받는다   [2]받지않는다" << std::endl;
		std::cout << "카드를 더 받으시겠습니까: ";
		string input;
		std::cin >> input;

		if (input == "1")
		{
			players->addCardToHand(*deck[temp++]);
			// printSystem(players, players, numOfPlayers);
		}
		else if (input == "2")
			return;
		else
			std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void mainImage()
{
	std::cout << "                             ...........                  ......." << std::endl;
	std::cout << "                        .................                 ...AAAA:....." << std::endl;
	std::cout << "                  ........................     .^~:.     ...AA.AA:........." << std::endl;
	std::cout << "             .......JJ!.................... .:^7YPY!^.  ..~AA,,AA:.............." << std::endl;
	std::cout << "              .......JJ!.................:^^~?5B#BBB57^^^:AAAAAAA:.................." << std::endl;
	std::cout << "               .......JJ!..............:^^~JG##BBBBBBBP?~^AA:..AA:.................." << std::endl;
	std::cout << "                ....,..JJ!..........::^^!YB###BBBBBBBBBBPJ~^:::AA:................." << std::endl;
	std::cout << "                 ..^J,,JJ!.........:^:^75##########BBBBBBBBGY!^.A:................" << std::endl;
	std::cout << "                  ...JJJJ!......:^^^?P#&&&&&##########BBBBB#&G?^................." << std::endl;
	std::cout << "                   ...........:^^^?G&&#BGGGGB#&#########BGGB@@@BJ^.............." << std::endl;
	std::cout << "                    ........:^^^JB&@BJ!~^^~~~?P######BGY~^:!@@@@@#J^..........." << std::endl;
	std::cout << "                     .....:^^:?#&&&5^^^^^!~^^^^J###Y7~^:::.~@@@@@@@#?........." << std::endl;
	std::cout << "                      ..:^^:!B&#&&&7!!~7B&#!^~~^###?.^^~~..~@@@@@@@@@G!......" << std::endl;
	std::cout << "                      .^~:^P&##&&&&&&&&&@&P~~~^J&##GJYPY...~@@@@@@@@@@@5^^.." << std::endl;
	std::cout << "                      .~:7#&B&@@&&&&&&&#57^^^~Y#######&P:::~@@@@@@@@@@@@#!^." << std::endl;
	std::cout << "                      ::?@&B&@@&&&&&&BY!^^~75#&######&@G^^^!@@@@@@@@@@@@@@7:." << std::endl;
	std::cout << "                      ^^#@B&@@@@&&&&5!~~~?P#&&#####&@@@G^^:!@@@@@@@@@@@@@@B^:" << std::endl;
	std::cout << "                      ^~&@B@@@@@&&@Y^~~~~?J??777G&#????7^^^^77!B@@@@@@@@@@#~:" << std::endl;
	std::cout << "                      ^~G@B&&&&&&&&~^^^~~~~~~^^^G@#^^^^^^::::::P@@@@@@@@&@B~." << std::endl;
	std::cout << "                      .~?&#B####&&&GPPPPPPPGGGGG&@&PPGGGGGGGPPP#@&&&&##B&&?:" << std::endl;
	std::cout << "                       .~J##GPGGBBB#####&&@@@@@@@@@@@@@@@@&&&&&#BBBGGPP#&J:" << std::endl;
	std::cout << "                         ^7G#G5YYYY55PPGGGBB#&@@&@@@@&#BBGGGPPP5YYJJYG#G!." << std::endl;
	std::cout << "                          .:75BBP5YYYY55PGB##P#@@@@@#P##BGP55YYYY5PBB5!." << std::endl;
	std::cout << "                              :~7J5555555J7~^!#&@@@@#!:!?Y5555555J7~." << std::endl;
	std::cout << "                                           ^J#&&@@@@@#?:" << std::endl;
	std::cout << "                                 .:^^^^!7YP#&&@@@@@@@&@#PJ7~~~~~:" << std::endl;
	std::cout << "                                 :~B&#&&@@@@@@@@@@@@@@@@@@@&&&&G~" << std::endl;
	std::cout << "                                 :^7???????????????????????????7^" << std::endl;
}