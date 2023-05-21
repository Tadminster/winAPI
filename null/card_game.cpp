#include <iostream>
#include <ctime>
#include <string>

const int DECK_SIZE = 52;
const int INITIAL_COIN = 10000;
const int MIN_BET = 0;
const int MAX_BET = 5000;

enum Symbol { SPADE, DIAMOND, HEART, CLUB, QUESTION };
typedef struct deck
{
	Symbol symbol;
	int number;
}Deck;

void game();
void shuffle(Deck[], int, bool);
bool menuInput();
void displayMsg(int, int);
int playerInput(int);
void funcResult(int, int&, Deck[]);
void printCardProto(Deck[], bool);
void printCardBody(int, int, Symbol, int);

int main()
{
	std::cout << "월남뽕 게임" << std::endl;

	while (menuInput())
	{
		game();
	}
}

void game()
{
	// Initialize player money
	int coin{ INITIAL_COIN };

	// Initialize the deck
	Deck deck[DECK_SIZE];
	for (int i = 0; i < DECK_SIZE; i++)
	{
		deck[i].number = (i % 13) + 1;
		if (i < 13) deck[i].symbol = SPADE;
		else if (i < 26) deck[i].symbol = DIAMOND;
		else if (i < 39) deck[i].symbol = HEART;
		else deck[i].symbol = CLUB;
	}

	// shuffle
	shuffle(deck, 0, false);

	// Draw
	int cardIndex = 0;
	int remainingCards = DECK_SIZE;
	while (1)
	{
		// Clear the screen
		system("cls");

		// Draw three cards
		remainingCards -= 3;
		Deck cards[3] = { deck[cardIndex++], deck[cardIndex++], deck[cardIndex++] };

		// If card A and card B are the same... up to 3 times
		if (cards[0].number == cards[1].number)
			shuffle(deck, cardIndex, true);
		if (cards[0].number == cards[1].number)
			shuffle(deck, cardIndex, true);
		if (cards[0].number == cards[1].number)
			shuffle(deck, cardIndex, true);

		// Sort the cards
		if (cards[0].number > cards[1].number)
			std::swap(cards[0], cards[1]);

		// Display the cards .. 1
		printCardProto(cards, false);

		// Display System msg .. 2
		displayMsg(remainingCards, coin);

		// Get the player's bet
		int betting{ playerInput(coin) };

		// Display the Hidden cards .. 3
		system("cls");
		printCardProto(cards, true);
		displayMsg(remainingCards, coin);

		// Display System msg ..4 (Reveal the hidden card)
		std::cout << "히든 카드는 ["
			<< (cards[2].symbol == 0 ? "♠ " :
				cards[2].symbol == 1 ? "◆ " :
				cards[2].symbol == 2 ? "♥ " :
				cards[2].symbol == 3 ? "♣ " : "ERROE")
			<< cards[2].number << "] 입니다." << std::endl;

		// Output the Result
		funcResult(betting, coin, cards);
		std::cout << std::endl;

		// Check the end condition
		if (coin == 0)
		{
			std::cout << "모든 돈을 잃었습니다. 다시 시작하시겠습니까?" << std::endl;
			break;
		}
		else if (remainingCards < 3)
		{
			std::cout << "남은 카드가 3장 미만입니다. 다시 시작하시겠습니까?" << std::endl;
			break;
		}
		else
		{
			std::cout << "계속하려면 아무키나 입력하세요: ";
			std::string waiting;
			std::cin >> waiting;
		}
	}
}

/* Func to shuffle cards*/
void shuffle(Deck deck[], int index, bool reShuffle)
{
	// Random Seed Initialize
	srand(time(NULL));

	// Shuffle card
	for (int i = index; i < DECK_SIZE; i++) {
		int j;
		if (reShuffle)
		{
			j = index + (rand() % (DECK_SIZE - index));
		}
		else
			j = rand() % DECK_SIZE;
		std::swap(deck[i], deck[j]);
	}
}

/* Menu settings */
bool menuInput()
{
	std::string sInput;
	while (1)
	{
		std::cout << "[1] 시작하기" << std::endl;
		std::cout << "[2] 종료하기" << std::endl;
		std::cout << "원하는 옵션을 선택하세요 : ";
		std::cin >> sInput;
		if (sInput == "1") return true;
		else if (sInput == "2") exit(1);
		else std::cout << "올바른 옵션을 선택하세요." << std::endl;
	}
}

/* Player input */
int playerInput(int coin)
{
	std::string str;
	int input{ 0 };
	while (1)
	{
		std::cout << std::endl;
		std::cout << "배팅 금액을 입력하세요(0~5000): ";
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
		if (input < MIN_BET) std::cout << "[ERROR] '0원'이상 배팅해야 합니다." << std::endl;
		else if (input > coin) std::cout << "[ERROR] 가진 돈보다 많이 배팅할 수 없습니다." << std::endl;
		else if (input > MAX_BET) std::cout << "[ERROR] 최대 배팅금액은 '5000원'입니다." << std::endl;
		else break;
		std::cout << std::endl;
	}
	return input;
}

void displayMsg(int remainingCards, int coin)
{
	std::cout << std::endl;
	std::cout << "카드를 3장 뽑았습니다.. 남은 카드: " << remainingCards << std::endl;
	std::cout << "플레이어의 소지금: " << coin << std::endl;
}

/* result output */
void funcResult(int betting, int& coin, Deck cards[])
{
	if (betting == 0)
		std::cout << "0원을 배팅했습니다. 이번 게임은 패스하겠습니다." << std::endl;
	else if (cards[0].number < cards[2].number && cards[2].number < cards[1].number)
	{
		int payout = betting * 2;
		std::cout << "축하합니다! 이번 게임에서 승리하여 '" << payout << "원'을 벌었습니다." << std::endl;
		coin += payout;
	}
	else
	{
		std::cout << "아쉽게도.. 이번 게임에서 패배하여 '" << betting << "원'을 잃었습니다." << std::endl;
		coin = (coin - betting < 0 ? 0 : coin - betting);
	}
}

/* Display the cards
!!This func must be called!! */
void printCardProto(Deck deck[], bool hCardVisibility)
{
	// Cards of size (side * side)
	int side{ 5 };
	std::cout << "첫번째 카드\t두번째 카드\t\t히든 카드" << std::endl;

	// Print the square card shape
	for (int i = 1; i <= side; i++) {
		// 1st Card
		printCardBody(i, side, deck[0].symbol, deck[0].number);

		// 2nd Card
		std::cout << "\t";
		printCardBody(i, side, deck[1].symbol, deck[1].number);

		// 3rd Card
		std::cout << "\t\t";
		if (hCardVisibility == true)
			printCardBody(i, side, deck[2].symbol, deck[2].number);
		else
			printCardBody(i, side, QUESTION, 0);

		std::cout << std::endl;
	}
}

/* This func should not be called! */
void printCardBody(int i, int side, Symbol symbol, int number)
{
	for (int j = 1; j <= side; j++) {
		// Outline
		if (i == 1 || i == side || j == 1 || j == side) {
			std::cout << "* ";
		}
		// Symbol
		else if (i == 2 && j == 2)
		{
			switch (symbol)
			{
			case SPADE:
				std::cout << "♠ ";
				break;
			case DIAMOND:
				std::cout << "◆ ";
				break;
			case HEART:
				std::cout << "♥ ";
				break;
			case CLUB:
				std::cout << "♣ ";
				break;
			case QUESTION:
				std::cout << "? ";
				break;
			default:
				break;
			}
		}
		// Number
		else if (i == side - 1 && j == side - 1)
		{
			if (number == 0)
				std::cout << "? ";
			else if (number < 10)
				std::cout << number << " ";
			else
				std::cout << number;
		}
		// Inner blank space
		else {
			std::cout << "  ";
		}
	}
}