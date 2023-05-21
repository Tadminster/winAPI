#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
const int DECK_SIZE = 52;

#include "TrumpCard.h"
#include "Player.h"

void mainImage();
void outputText(string subject, string texts[], int size, int current);
bool menu(string subject, string menuTexts[], int current, int size, void (*func)());
bool menu(string subject, string menuTexts[], int &current, int size,
	void (*func)(Player*, Player**, int), Player* player, Player** players, int numOfPlayers);
void jankenpon();
int inputNumOfPlayer();
void shuffle(vector <unique_ptr<TrumpCard>>& deck);
void printSystem(Player* player, Player** players, int numOfPlayers);
int InputArrow(int& current, int minimum, int maximum, bool isForward);

int main()
{
	srand((unsigned int)time(NULL));

	int current{ 0 };
	string subject = "\t\t\t\t\t   BLACK   JACK";
	string menuTexts[2] = { "\t\t\t\t\t   [ 시작하기 ]",
							"\t\t\t\t\t   [ 종료하기 ]" };
	int size = sizeof(menuTexts) / sizeof(std::string);
	while (menu(subject, menuTexts, current, size, mainImage))
	{
		jankenpon();
	}
}

/* 메뉴 분기점 */
bool menu(string subject, string menuTexts[], int current, int size, void (*func)())
{
	int temp{ 0 };

	while (current != 99)
	{

		system("cls");
		(func)();


		outputText(subject, menuTexts, size, current);
		temp = current;
		current = InputArrow(current, 0, 1, true);
	}

	if (temp == 0) return true;
	else if (temp == 1) return false;
}

// @overloading
bool menu(string subject, string menuTexts[], int &current, int size,
	void (*func)(Player*, Player**, int), Player* player, Player** players, int numOfPlayers)
{
	int temp{ 0 }, tempWhile{ 0 };

	while (tempWhile != 99)
	{

		system("cls");
		(func)(player, players, numOfPlayers);

		outputText(subject, menuTexts, size, current);
		temp = current;
		tempWhile = InputArrow(current, 0, 1, true);
	}

	if (temp == 0) return true;
	else if (temp == 1) return false;
}

/* 메뉴 출력, 화살표 표시 */
void outputText(string subject, string menuTexts[], int size, int current)
{
	std::cout << std::endl << subject << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (current == i)
			std::cout << menuTexts[i] << " ◀◀";
		else
			std::cout << menuTexts[i];
		std::cout << endl;
	}
}

/* 게임의 시작 위치 */
void jankenpon()
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
	int numOfPlayers{ inputNumOfPlayer() };

	// 딜러, 플레이어 생성
	Player* dealer = new Player("딜러");
	Player** players = new Player * [numOfPlayers];
	for (int i = 0; i < numOfPlayers; i++)
	{
		system("cls");
		mainImage();
		std::cout << std::endl;
		std::cout << "\t\t\t\t  " << numOfPlayers << "명의 플레이어가 참여했습니다. " << std::endl;
		std::cout << "\t\t\t\t  [" << i+1 << "]번 플레이어 이름 입력: ";
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
			players[i]->setInit();
			players[i]->setIsDone(false);
			players[i]->addCardToHand(*deck[temp++]);
			players[i]->addCardToHand(*deck[temp++]);
		}
		dealer->handClear();
		dealer->setInit();

;
		// 플레이어 시스템 출력
		for (int i = 0; i < numOfPlayers; i++)
		{
			while (true)
			{

				// 화면 지우고 새로 출력
				std::system("cls");
				printSystem(players[i], players, numOfPlayers);

				// A카드 확인
				if (players[i]->selectA())
				{
					int aTemp{ 0 };
					string subject = "A 카드를 몇으로 사용 하시겠습니까?";
					string menuTexts[2] = { "[   1  ]",
											"[  11  ]" };
					int size = sizeof(menuTexts) / sizeof(std::string);
					menu(subject, menuTexts, aTemp, size, printSystem, players[i], players, numOfPlayers);
					if (aTemp == 1)
						players[i]->setSum(10);
				}

				// 버스트 확인
				if (players[i]->getSum() > 21)
				{
					std::cout << std::endl;
					players[i]->setStatus("\033[1;31m버스트\033[0m");
					players[i]->setIsDone(true);
					std::system("pause");
					break;
				}

				// 카드 새로 받기
				int current{ 0 };
				{
					string subject = "카드를 더 받으시겠습니까";
					string menuTexts[2] = { "[ 카드를 더 받기 ]",
										"[ 이제 그만 받기 ]" };
					int size = sizeof(menuTexts) / sizeof(std::string);
					menu(subject, menuTexts, current, size, printSystem, players[i], players, numOfPlayers);
					if (current == 0)
						players[i]->addCardToHand(*deck[temp++]);
					else
					{
						players[i]->setIsDone(true);
						break;
					}
				}
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
			for (int i = 0; i < 10; i++)
				Sleep(150);
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

	for (int i = 0; i < numOfPlayers; i++)
		delete[] players[i];
	delete[] players;
	delete[] dealer;

	return;
}


int inputNumOfPlayer()
{
	int numOfPlayers{ 2 }, temp;

	while (numOfPlayers != 99)
	{
		system("cls");
		mainImage();

		std::cout << std::endl;
		std::cout << "\t\t\t\t\t\t\t   ▲" << std::endl;
		std::cout << "\t\t\t\t\t플레이 할 인원 수: " << numOfPlayers << std::endl;
		std::cout << "\t\t\t\t\t\t\t   ▼";

		temp = numOfPlayers;
		numOfPlayers = InputArrow(numOfPlayers, 2, 5, false);
	}

	return temp;
}

/* 섞기 (덱) */
void shuffle(vector <unique_ptr<TrumpCard>>& deck)
{
	for (int i = 0; i < DECK_SIZE; i++) {
		int j = rand() % DECK_SIZE;
		std::swap(deck[i], deck[j]);
	}
}

/* 시스템 메뉴 출력하기 */
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


/* (Current =  current value of the menu, selectSize = number of options) */
int InputArrow(int& current, int minimum, int maximum, bool isForward)
{
	int ch = 0;
	do {
		ch = _getch(); // read key press
		if (ch == 0xE0) { // check for arrow key
			ch = _getch(); // read arrow direction
			if (ch == 72)
			{ // up arrow
				if(isForward)
					current = (current - 1 > minimum ? --current : minimum);
				else 
					current = (current + 1 < maximum ? ++current : maximum);

				return current;
			}
			else if (ch == 80)
			{ // down arrow
				if (isForward)
					current = (current + 1 < maximum ? ++current : maximum);
				else
					current = (current - 1 > minimum ? --current : minimum);

				return current;
			}
			else if (ch == 75)
			{
				// left arrow 
			}
			else if (ch == 77)
			{
				// right arrow
			}
		}
	} while (ch != 13);

	return 99;
}

/* 메인 이미지 그리기 */
void mainImage()
{
	std::cout << "                             ...........                  ......." << std::endl;
	std::cout << "                        .................                 ...\033[1;31mAAAA\033[0m:....." << std::endl;
	std::cout << "                  ........................     .^~:.     ...\033[1;31mAA.\033[1;31mAA\033[0m:........." << std::endl;
	std::cout << "             .......\033[1;31mJJ!\033[0m.................... .:^7YPY!^.  ..~\033[1;31mAA\033[0m,,\033[1;31mAA\033[0m:.............." << std::endl;
	std::cout << "              .......\033[1;31mJJ!\033[0m.................:^^~?5B#BBB57^^^:\033[1;31mAAAAAAA\033[0m:.................." << std::endl;
	std::cout << "               .......\033[1;31mJJ!\033[0m..............:^^~JG##BBBBBBBP?~^\033[1;31mAA\033[0m:..\033[1;31mAA\033[0m:.................." << std::endl;
	std::cout << "                ....,..\033[1;31mJJ!\033[0m..........::^^!YB###BBBBBBBBBBPJ~^:::\033[1;31mAA\033[0m:................." << std::endl;
	std::cout << "                 ..\033[1;31m^J\033[0m,,\033[1;31mJJ!\033[0m.........:^:^75##########BBBBBBBBGY!^.\033[1;31mA\033[0m:................" << std::endl;
	std::cout << "                  ...\033[1;31mJJJJ!\033[0m......:^^^?P#&&&&&##########BBBBB#&G?^................." << std::endl;
	std::cout << "                   ...........:^^^?G&&#BGGGGB#&#########BGGB@@@BJ^.............." << std::endl;
	std::cout << "                    ........:^^^JB&@BJ!\033[1;36m~^^~~~\033[0m?P######BGY\033[1;36m~^:!\033[0m@@@@@#J^..........." << std::endl;
	std::cout << "                     .....:^^:?#&&&5\033[1;36m^^^^^!~^^^^\033[0mJ###Y7\033[1;36m~^:::.~\033[0m@@@@@@@#?........." << std::endl;
	std::cout << "                      ..:^^:!B&#&&&7!!\033[1;36m~7B&#!^~~^\033[0m###?\033[1;36m.^^~~..~\033[0m@@@@@@@@@G!......" << std::endl;
	std::cout << "                      .^~:^P&##&&&&&&&&&@&P\033[1;36m~~~^\033[0mJ&##GJYPY\033[1;36m...~\033[0m@@@@@@@@@@@5^^.." << std::endl;
	std::cout << "                      .~:7#&B&@@&&&&&&&#57\033[1;36m^^^~\033[0mY#######&P\033[1;36m:::~\033[0m@@@@@@@@@@@@#!^." << std::endl;
	std::cout << "                      ::?@&B&@@&&&&&&BY!\033[1;36m^^~\033[0m75#&######&@G\033[1;36m^^^!\033[0m@@@@@@@@@@@@@@7:." << std::endl;
	std::cout << "                      ^^#@B&@@@@&&&&5!\033[1;36m~~~\033[0m?P#&&#####&@@@G\033[1;36m^^:!\033[0m@@@@@@@@@@@@@@B^:" << std::endl;
	std::cout << "                      ^~&@B@@@@@&&@Y\033[1;36m^~~~~\033[0m?J??777G&#\033[1;36m????7^^^^77!B\033[0m@@@@@@@@@@#~:" << std::endl;
	std::cout << "                      ^~G@B&&&&&&&&~\033[1;36m^^^~~~~~~^^^\033[0mG@#\033[1;36m^^^^^^::::::P\033[0m@@@@@@@@&@B~." << std::endl;
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