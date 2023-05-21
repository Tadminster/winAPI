#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int DECK_SIZE{ 52 };
const int INITIAL_COIN{ 10000 };
const int MIN_BET{ 500 };
const int MAX_BET{ 5000 };

enum class Symbol
{
	SPADE,
	DIAMOND,
	HEART,
	CLUB,
	QUESTION
};

typedef struct card
{
	Symbol symbol;
	int number;
}Card;

void menu();
void outputText(string texts[], int size, int currnet);
int InputArrow(int current, int selectSize);
void game();
void printCardProto(Card deck[], bool hCardVisibility);
void printCardBody(int i, int side, Symbol symbol, int number, bool hidden);
void shuffle(Card deck[]);
void outputMsg(int remainingCards, int high, int low, int seven, int coin);
int InputBet(int coin, int betType);
void funcResult(int betting, int betType, int& coin, Card cards[]);
void gameOver(bool death);

void arrayOutput(Card deck[], int deckSize);

int main()
{

	while (1)
	{
		menu();
	}
}

/* Menu settings */
void menu()
{
	int current{ 0 }, temp;
	string menus[2] = { "[ 시작하기 ]", "[ 종료하기 ]" };
	int size = sizeof(menus) / sizeof(std::string);

	while (current != 99)
	{
		system("cls");
		std::cout << "하이 - 로우 - 세븐" << std::endl;

		outputText(menus, 2, current);
		temp = current;
		current = InputArrow(current, 2);
	}

	if (temp == 0) game();
	else if (temp == 1) exit(1);
}

/* Array of text to print, size of the array, text to display as an arrow */
void outputText(string texts[], int size, int current)
{
	for (int i = 0; i < size; i++)
	{
		if (current == i)
			std::cout << texts[i] << " ◀◀";
		else
			std::cout << texts[i];
		std::cout << std::endl;
	}
}

/* Main game start */
void game()
{
	// Initialize player money
	int coin{ INITIAL_COIN };

	// Initialize the deck
	Card deck[DECK_SIZE];
	for (int i = 0; i < DECK_SIZE; i++)
	{
		deck[i].number = (i % 13) + 1;
		if (i < 13) deck[i].symbol = Symbol::SPADE;
		else if (i < 26) deck[i].symbol = Symbol::DIAMOND;
		else if (i < 39) deck[i].symbol = Symbol::HEART;
		else deck[i].symbol = Symbol::CLUB;
	}

	// Random Seed Initialize & Shuffle
	srand(time(NULL));
	shuffle(deck);

	int cardIndex = 0;
	int remainingCards = DECK_SIZE;
	while (remainingCards > 5)
	{
		int high{ 0 }, low{ 0 }, seven{ 0 };

		// Draw three cards
		remainingCards -= 6;
		Card drawnCards[6];
		for (int i = 0; i < 6; i++)
		{
			drawnCards[i] = deck[cardIndex++];
			if (i == 5) break;
			else if (drawnCards[i].number < 7) low++;
			else if (drawnCards[i].number == 7) seven++;
			else high++;
		}

		// bet type
		string texts[3] = { "[ 하이 ]", "[ 로우 ]", "[ 세븐 ]" };
		int size = sizeof(texts) / sizeof(std::string);
		int current{ 0 };
		int betType; // [ 0 = high ], [1 = low], [2 = seven]
		while (current != 99)
		{
			system("cls");

			printCardProto(drawnCards, false);
			outputMsg(remainingCards, high, low, seven, coin);

			std::cout << "배팅 종류 선택 (하이/로우 2배, 세븐 5배)" << endl;
			outputText(texts, size, current);

			betType = current;
			current = InputArrow(current, size);
		}

		int betting{ 0 };
		// bet amount

		system("cls");

		printCardProto(drawnCards, false);
		outputMsg(remainingCards, high, low, seven, coin);

		betting = InputBet(coin, betType);

		// Display the Hidden cards
		std::cout << std::endl;
		std::cout << "히든 카드를 공개하겠습니다.";
		for (int i = 0; i < 3; i++)
		{
			Sleep(400);
			std::cout << ".";
		}
		Sleep(400);
		std::cout << std::endl;

		// Final
		system("cls");
		printCardProto(drawnCards, true);
		outputMsg(remainingCards, high, low, seven, coin);
		if (betType == 0) std::cout << "[ 하이 ]";
		else if (betType == 1) std::cout << "[ 로우 ]";
		else std::cout << "[ 세븐 ]";
		std::cout << "배팅 금액 입력(" << MIN_BET << "~" << MAX_BET << "): " << betting << endl;

		std::cout << std::endl;
		std::cout << "히든 카드는 [\033[1;33m"
			<< (drawnCards[5].symbol == Symbol::SPADE ? "♠ " :
				drawnCards[5].symbol == Symbol::DIAMOND ? "◆ " :
				drawnCards[5].symbol == Symbol::HEART ? "♥ " :
				drawnCards[5].symbol == Symbol::CLUB ? "♣ " : "ERROE")
			<< drawnCards[5].number << "\033[0m] 입니다." << std::endl;


		// Output the Result
		funcResult(betting, betType, coin, drawnCards);
		std::cout << std::endl;

		// Check the end condition
		int c;
		if (coin == 0)
		{
			std::cout << "모든 돈을 잃었습니다. ";
			gameOver(true);
			break;
		}
		else if (remainingCards < 6)
		{
			std::cout << "남은 카드가 6장 미만입니다. ";
			gameOver(true);
			break;
		}
		else
			gameOver(false);

	}
}

/* Shuffle cards */
void shuffle(Card deck[])
{
	for (int i = 0; i < DECK_SIZE; i++) {
		int j = rand() % DECK_SIZE;
		std::swap(deck[i], deck[j]);
	}
}

/* Display the cards
!!This func must be called!! */
void printCardProto(Card deck[], bool hCardVisibility)
{
	// Cards of size (side * side)
	int side{ 5 };
	std::cout << "첫번째 카드\t두번째 카드\t세번째 카드\t네번째 카드\t다섯번째 카드\t\t히든 카드" << std::endl;

	// Print the square card shape
	for (int i = 1; i <= side; i++) {
		int index{ 0 };

		// 1st ~ 5th card
		for (int j = 0; j < 5; j++)
		{
			printCardBody(i, side, deck[index].symbol, deck[index].number, false);
			std::cout << "\t";
			index++;
		}

		// Hidden Card
		std::cout << "\t";
		if (hCardVisibility == true)
		{
			printCardBody(i, side, deck[index].symbol, deck[index].number, true);
			index++;
		}
		else
			printCardBody(i, side, Symbol::QUESTION, 0, true);

		std::cout << std::endl;
	}
}

/* This func should not be called! */
void printCardBody(int i, int side, Symbol symbol, int number, bool hidden)
{
	for (int j = 1; j <= side; j++) {
		// Outline
		if (i == 1 || i == side || j == 1 || j == side)
			std::cout << "* ";
		// Symbol
		else if (i == 2 && j == 2)
		{
			switch (symbol)
			{
			case Symbol::SPADE:
				std::cout << "♠";
				break;
			case Symbol::DIAMOND:
				std::cout << "◆";
				break;
			case Symbol::HEART:
				std::cout << "♥";
				break;
			case Symbol::CLUB:
				std::cout << "♣";
				break;
			case Symbol::QUESTION:
				std::cout << "? ";
				break;
			default:
				break;
			}
		}
		// Number
		else if (i == side - 1 && j == side - 1)
		{
			// Set color to
			if (number == 0) {}
			else if (number < 7)
				std::cout << "\033[1;34m"; // BLUE
			else if (number > 7)
				std::cout << "\033[1;31m"; // RED
			else
				std::cout << "\033[1;36m"; // GREEN

			// Print Number
			if (number == 0)
				std::cout << "? ";
			else if (number == 1)
				std::cout << "A ";
			else if (number == 11)
				std::cout << "J ";
			else if (number == 12)
				std::cout << "Q ";
			else if (number == 13)
				std::cout << "K ";
			else if (number == 10)
				std::cout << number;
			else
				std::cout << number << " ";

			std::cout << "\033[0m"; // reset color
		}
		// Inner blank space
		else {
			std::cout << "  ";
		}
	}
}

void outputMsg(int remainingCards, int high, int low, int seven, int coin)
{
	std::cout << endl;
	std::cout << "카드를 6장 뽑았습니다. 남은 카드: " << remainingCards << endl;
	std::cout << "드러난 5장의 카드 중 \033[1;31m 하이: " << high
		<< " , \033[1;34m 로우: " << low
		<< " , \033[1;36m 세븐: " << seven
		<< "\033[0m" << endl;
	std::cout << endl;
	std::cout << "플레이어의 소지금: " << coin << endl;

}

/* (Current =  current value of the menu, selectSize = number of options) */
int InputArrow(int current, int selectSize)
{
	int ch = 0;
	selectSize -= 1;
	do {
		ch = _getch(); // read key press
		if (ch == 0xE0) { // check for arrow key
			ch = _getch(); // read arrow direction
			if (ch == 72)
			{ // up arrow
				current = (current - 1 > 0 ? --current : 0);
				return current;
			}
			else if (ch == 80)
			{ // down arrow
				current = (current + 1 < selectSize ? ++current : selectSize);
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

/* Player input bet*/
int InputBet(int coin, int betType)
{
	if (betType == 0) std::cout << "[ 하이 ]";
	else if (betType == 1) std::cout << "[ 로우 ]";
	else std::cout << "[ 세븐 ]";

	std::string str;
	int input{ 0 };
	while (1)
	{
		std::cout << "배팅 금액 입력(" << MIN_BET << "~" << MAX_BET << "): ";
		std::cin >> str;

		try
		{
			input = stoi(str);
		}
		// std::string checking
		catch (const std::invalid_argument& e)
		{
			std::cout << "[ERROR] '문자'가 입력되었습니다." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < MIN_BET) std::cout << "[ERROR] " << MIN_BET << "'이상 배팅해야 합니다." << std::endl;
		else if (input > coin) std::cout << "[ERROR] 가진 돈보다 많이 배팅할 수 없습니다." << std::endl;
		else if (input > MAX_BET) std::cout << "[ERROR] 최대 배팅금액은 '" << MAX_BET << "'입니다." << std::endl;
		else break;
		std::cout << std::endl;
	}
	return input;
}

/* result output */
void funcResult(int betting, int betType, int& coin, Card cards[])
{
	if (cards[5].number == 7 && betType == 2)
	{
		int payout = betting * 5;
		std::cout << "축하합니다! \033[1;32m세븐\033[0m을 맞춰 '" << payout << "원'을 벌었습니다." << std::endl;
		coin += payout;
	}
	else if (cards[5].number > 7 && betType == 0)
	{
		int payout = betting * 2;
		std::cout << "축하합니다! \033[1;31m하이\033[0m을 맞춰 '" << payout << "원'을 벌었습니다." << std::endl;
		coin += payout;
	}
	else if (cards[5].number < 7 && betType == 1)
	{
		int payout = betting * 2;
		std::cout << "축하합니다! \033[1;34m로우\033[0m을 맞춰 '" << payout << "원'을 벌었습니다." << std::endl;
		coin += payout;
	}
	else
	{
		std::cout << "아쉽게도.. 이번 게임에서 패배하여 '" << betting << "원'을 잃었습니다." << std::endl;
		coin = (coin - betting < 0 ? 0 : coin - betting);
	}
}

void gameOver(bool death)
{
	if (death)
	{
		std::cout << "게임이 끝났습니다." << std::endl;
		std::cout << "아무키나 누르면 메뉴창으로 돌아갑니다." << std::endl;
	}
	else
		std::cout << "계속하려면 아무키나 누르세요..";
	int c;
	c = getchar();
	c = _getch();
}

/* !!only for debugging!! Array output */
void arrayOutput(Card deck[], int deckSize)
{
	for (int i = 0; i < deckSize; i++)
	{
		switch (deck[i].symbol)
		{
		case Symbol::SPADE:
			std::cout << "♠";
			break;
		case Symbol::DIAMOND:
			std::cout << "◆";
			break;
		case Symbol::HEART:
			std::cout << "♥";
			break;
		case Symbol::CLUB:
			std::cout << "♣";
			break;
		case Symbol::QUESTION:
			std::cout << "? ";
			break;
		default:
			break;
		}
		std::cout << " : " << deck[i].number << endl;
	}
}