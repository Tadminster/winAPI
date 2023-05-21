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
	string menus[2] = { "[ �����ϱ� ]", "[ �����ϱ� ]" };
	int size = sizeof(menus) / sizeof(std::string);

	while (current != 99)
	{
		system("cls");
		std::cout << "���� - �ο� - ����" << std::endl;

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
			std::cout << texts[i] << " ����";
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
		string texts[3] = { "[ ���� ]", "[ �ο� ]", "[ ���� ]" };
		int size = sizeof(texts) / sizeof(std::string);
		int current{ 0 };
		int betType; // [ 0 = high ], [1 = low], [2 = seven]
		while (current != 99)
		{
			system("cls");

			printCardProto(drawnCards, false);
			outputMsg(remainingCards, high, low, seven, coin);

			std::cout << "���� ���� ���� (����/�ο� 2��, ���� 5��)" << endl;
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
		std::cout << "���� ī�带 �����ϰڽ��ϴ�.";
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
		if (betType == 0) std::cout << "[ ���� ]";
		else if (betType == 1) std::cout << "[ �ο� ]";
		else std::cout << "[ ���� ]";
		std::cout << "���� �ݾ� �Է�(" << MIN_BET << "~" << MAX_BET << "): " << betting << endl;

		std::cout << std::endl;
		std::cout << "���� ī��� [\033[1;33m"
			<< (drawnCards[5].symbol == Symbol::SPADE ? "�� " :
				drawnCards[5].symbol == Symbol::DIAMOND ? "�� " :
				drawnCards[5].symbol == Symbol::HEART ? "�� " :
				drawnCards[5].symbol == Symbol::CLUB ? "�� " : "ERROE")
			<< drawnCards[5].number << "\033[0m] �Դϴ�." << std::endl;


		// Output the Result
		funcResult(betting, betType, coin, drawnCards);
		std::cout << std::endl;

		// Check the end condition
		int c;
		if (coin == 0)
		{
			std::cout << "��� ���� �Ҿ����ϴ�. ";
			gameOver(true);
			break;
		}
		else if (remainingCards < 6)
		{
			std::cout << "���� ī�尡 6�� �̸��Դϴ�. ";
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
	std::cout << "ù��° ī��\t�ι�° ī��\t����° ī��\t�׹�° ī��\t�ټ���° ī��\t\t���� ī��" << std::endl;

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
				std::cout << "��";
				break;
			case Symbol::DIAMOND:
				std::cout << "��";
				break;
			case Symbol::HEART:
				std::cout << "��";
				break;
			case Symbol::CLUB:
				std::cout << "��";
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
	std::cout << "ī�带 6�� �̾ҽ��ϴ�. ���� ī��: " << remainingCards << endl;
	std::cout << "�巯�� 5���� ī�� �� \033[1;31m ����: " << high
		<< " , \033[1;34m �ο�: " << low
		<< " , \033[1;36m ����: " << seven
		<< "\033[0m" << endl;
	std::cout << endl;
	std::cout << "�÷��̾��� ������: " << coin << endl;

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
	if (betType == 0) std::cout << "[ ���� ]";
	else if (betType == 1) std::cout << "[ �ο� ]";
	else std::cout << "[ ���� ]";

	std::string str;
	int input{ 0 };
	while (1)
	{
		std::cout << "���� �ݾ� �Է�(" << MIN_BET << "~" << MAX_BET << "): ";
		std::cin >> str;

		try
		{
			input = stoi(str);
		}
		// std::string checking
		catch (const std::invalid_argument& e)
		{
			std::cout << "[ERROR] '����'�� �ԷµǾ����ϴ�." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < MIN_BET) std::cout << "[ERROR] " << MIN_BET << "'�̻� �����ؾ� �մϴ�." << std::endl;
		else if (input > coin) std::cout << "[ERROR] ���� ������ ���� ������ �� �����ϴ�." << std::endl;
		else if (input > MAX_BET) std::cout << "[ERROR] �ִ� ���ñݾ��� '" << MAX_BET << "'�Դϴ�." << std::endl;
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
		std::cout << "�����մϴ�! \033[1;32m����\033[0m�� ���� '" << payout << "��'�� �������ϴ�." << std::endl;
		coin += payout;
	}
	else if (cards[5].number > 7 && betType == 0)
	{
		int payout = betting * 2;
		std::cout << "�����մϴ�! \033[1;31m����\033[0m�� ���� '" << payout << "��'�� �������ϴ�." << std::endl;
		coin += payout;
	}
	else if (cards[5].number < 7 && betType == 1)
	{
		int payout = betting * 2;
		std::cout << "�����մϴ�! \033[1;34m�ο�\033[0m�� ���� '" << payout << "��'�� �������ϴ�." << std::endl;
		coin += payout;
	}
	else
	{
		std::cout << "�ƽ��Ե�.. �̹� ���ӿ��� �й��Ͽ� '" << betting << "��'�� �Ҿ����ϴ�." << std::endl;
		coin = (coin - betting < 0 ? 0 : coin - betting);
	}
}

void gameOver(bool death)
{
	if (death)
	{
		std::cout << "������ �������ϴ�." << std::endl;
		std::cout << "�ƹ�Ű�� ������ �޴�â���� ���ư��ϴ�." << std::endl;
	}
	else
		std::cout << "����Ϸ��� �ƹ�Ű�� ��������..";
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
			std::cout << "��";
			break;
		case Symbol::DIAMOND:
			std::cout << "��";
			break;
		case Symbol::HEART:
			std::cout << "��";
			break;
		case Symbol::CLUB:
			std::cout << "��";
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