#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

int input(std::string text, int min, int max);
int jankenpon();
void shuffleCards(struct Card cards[], int cardSize);
void cardPrint(struct Card cards[], int size);
void allPrint(struct Player* player, int numOfP);
void Genealogy(struct Player& player, struct Card& card_1, struct Card& card_2);
void Winner(struct Player* player, int &numOfP);

enum winRate
{
	¸ÁÅë, ÇÑ²ı, µÎ²ı, ¼¼²ı, ³×²ı, ´Ù¼¸²ı, ¿©¼¸²ı, ÀÏ°ö²ı, ¿©´ü²ı, °©¿À,
	¼¼·ú, Àå»ç, Àå»æ, ±¸»æ, µ¶»ç, ¾Ë¸®,
	»æ¶¯, ÀÌ¶¯, »ï¶¯, »ç¶¯, ¿À¶¯, À°¶¯, Ä¥¶¯, ÆÈ¶¯, ±¸¶¯, Àå¶¯,
	ÀÏ»ï±¤¶¯, ÀÏÆÈ±¤¶¯, »ïÆÈ±¤¶¯
};

struct Card
{
	std::string symbol;
	int num{ 0 };

	Card(int num, std::string symbol)
	{
		this->num = num;
		this->symbol = symbol;
	}
};

struct Player
{
	std::string name;
	int seed{ 0 };
	Card card[2];
	int rank{ 0 };
	bool arrive{ true };
};


int main()
{
	while (1)
	{
		system("cls");
		std::cout << "È­Åõ°ÔÀÓ" << std::endl;
		std::string menuText{ "[1]°ÔÀÓ½ÃÀÛ [2]Á¾·áÇÏ±â: " };
		int menu{ input(menuText, 1, 2) };
		if (menu == 1)
			jankenpon();
		else if (menu == 2)
			exit(1);
	}
}

/* »ç¿ëÀÚ ÀÔ·Â, ¿¹¿ÜÃ³¸® */
int input(std::string text, int min, int max)
{
	std::string str;
	int input{ 0 };
	while (1)
	{
		std::cout << text;
		std::cin >> str;

		try
		{
			input = std::stoi(str);
		}
		// std::string checking
		catch (const std::invalid_argument& e)
		{
			//std::cout <<  e.what() << std::endl;
			std::cout << "[ERROR] '¹®ÀÚ'°¡ ÀÔ·ÂµÇ¾ú½À´Ï´Ù." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < min || input > max)
			std::cout << "[ERROR] '°ª'ÀÌ ÀÛ°Å³ª Å®´Ï´Ù." << std::endl;
		else
			break;
		std::cout << std::endl;
	}

	return input;
}


/* °ÔÀÓ ½ÃÀÛ */
int jankenpon()
{
	// Ä«µå »ı¼º
	const int cardSize{ 20 };
	Card** cards = new Card*[cardSize];
	for (int i = 0; i < cardSize; i++)
	{
		cards[i] = new Card();

		cards[i].num = (i + 2) / 2;
		if (i == 0 || i == 4 || i == 14)
			cards[i].symbol = "±¤";
		else
			cards[i].symbol = "ÇÇ";
	}

	// ³­¼ö ÃÊ±âÈ­
	srand((unsigned int)time(NULL));

	// ÇÃ·¹ÀÌ¾î »ı¼º
	std::string pText{ "ÇÃ·¹ÀÌ ÇÒ ÀÎ¿ø ¼ö ÀÔ·Â: " };
	int numOfP{ input(pText, 2, 10) };
	Player* player = new Player[numOfP];

	// ÀÌ¸§ ÀÔ·Â, ½Ãµå ÃÊ±âÈ­
	std::string name;
	for (int i = 0; i < numOfP; i++)
	{
		std::cout << i << "¹ø ÇÃ·¹ÀÌ¾î ÀÌ¸§: ";
		std::cin >> name;
		player[i].name = name;
		player[i].seed = 10000;
	}
	//°è¼Ó ÇÏ±â¿ë ÀÓ½Ã º¯¼ö
	std::string x;

	// º»°ÔÀÓ ½ÃÀÛ
	while (1)
	{
		// Ä«µå ¼¯±â
		shuffleCards(cards, cardSize);

		// ÇÃ·¹ÀÌ¾î Ä«µå ÃÊ±âÈ­
		int temp{ 0 };
		for (int i = 0; i < numOfP; i++)
		{
			player[i].card[0] = cards[temp++];
			player[i].card[1] = cards[temp++];
		}

		// Ãâ·Â
		allPrint(player, numOfP);

		// ½ÂÀÚÃ³¸®
		Winner(player, numOfP);

		// 1¸í¸¸ ³²¾ÒÀ» ¶§ ÃÖÁ¾½Â¸®
		if (numOfP == 1)
		{
			for (int i = 0; i < numOfP; i++)
			{
				if (player[i].arrive)
					std::cout << std::endl << std::endl;
					std::cout << "ÇÃ·¹ÀÌ¾î [" << player[i].name << "] °¡ ÃÖÁ¾ ½Â¸®Çß½À´Ï´Ù.";
					std::cout << "ÇÃ·¹ÀÌ¾î [" << player[i].name << "] °¡ ÃÖÁ¾ ½Â¸®Çß½À´Ï´Ù.";
					std::cout << "ÇÃ·¹ÀÌ¾î [" << player[i].name << "] °¡ ÃÖÁ¾ ½Â¸®Çß½À´Ï´Ù.";
					std::cin >> x;
					return 1;
			}
		}


		std::cout << "°è¼ÓÇÏ·Á¸é ¾Æ¹«Å°³ª ÀÔ·ÂÇÏ¼¼¿ä: ";
		std::cin >> x;

	}


	delete[] player;

	return 1;
}

/* Ä«µå ¼¯±â */
void shuffleCards(struct Card cards[], int cardSize)
{
	for (int i = 0; i < cardSize; i++)
	{
		int j = rand() % 20;
		std::swap(cards[i], cards[j]);
	}
}

/* !Å×½ºÆ®¿ë! */
void cardPrint(struct Card cards[], int size)
{
	for (int i = 0; i < size; i++)
		std::cout << cards[i].num << " : " << cards[i].symbol << std::endl;
}

/* ÃÖÁ¾ Ãâ·Â */
void allPrint(struct Player* player, int numOfP)
{
	system("cls");
	for (int i = 0; i < numOfP; i++)
	{
		if (!player[i].arrive) continue;
		std::cout << player[i].name << "\t"
			<< player[i].card[0].num
			<< player[i].card[0].symbol << "\t"
			<< player[i].card[1].num
			<< player[i].card[1].symbol << "\t"
			<< player[i].seed << "\t";
		Genealogy(player[i], player[i].card[0], player[i].card[1]);
	}
}

/* Á·º¸ °á°ú Ã³¸®*/
void Genealogy(struct Player& player, struct Card& card_1, struct Card& card_2)
{
	if (card_1.symbol == "±¤" && card_2.symbol == "±¤")
	{
		if (card_1.num == 3 && card_2.num == 8)
		{
			player.rank = »ïÆÈ±¤¶¯;
			std::cout << "38±¤¶¯";
		}
		else if (card_1.num == 1 && card_2.num == 8)
		{
			player.rank = ÀÏÆÈ±¤¶¯;
			std::cout << "18±¤¶¯";
		}
		else if (card_1.num == 1 && card_2.num == 3)
		{
			player.rank = ÀÏ»ï±¤¶¯;
			std::cout << "13±¤¶¯";
		}
	}
	else if (card_1.num == card_2.num)
	{
		switch (card_1.num)
		{
		case 1:
			player.rank = »æ¶¯;
			std::cout << "»æ¶¯";
			break;
		case 2:
			player.rank = ÀÌ¶¯;
			std::cout << "2¶¯";
			break;
		case 3:
			player.rank = »ï¶¯;
			std::cout << "3¶¯";
			break;
		case 4:
			player.rank = »ç¶¯;
			std::cout << "4¶¯";
			break;
		case 5:
			player.rank = ¿À¶¯;
			std::cout << "5¶¯";
			break;
		case 6:
			player.rank = À°¶¯;
			std::cout << "6¶¯";
			break;
		case 7:
			player.rank = Ä¥¶¯;
			std::cout << "7¶¯";
			break;
		case 8:
			player.rank = ÆÈ¶¯;
			std::cout << "8¶¯";
			break;
		case 9:
			player.rank = ±¸¶¯;
			std::cout << "9¶¯";
			break;
		case 10:
			player.rank = Àå¶¯;
			std::cout << "Àå¶¯";
			break;
		default: break;
		}
	}
	else if (card_1.num == 1 && card_2.num == 2)
	{
		player.rank = ¾Ë¸®;
		std::cout << "¾Ë¸®";
	}
	else if (card_1.num == 1 && card_2.num == 4)
	{
		player.rank = µ¶»ç;
		std::cout << "µ¶»ç";
	}
	else if (card_1.num == 1 && card_2.num == 9)
	{
		player.rank = ±¸»æ;
		std::cout << "±¸»æ";
	}
	else if (card_1.num == 1 && card_2.num == 10)
	{
		player.rank = Àå»æ;
		std::cout << "Àå»æ";
	}
	else if (card_1.num == 4 && card_2.num == 10)
	{
		player.rank = Àå»ç;
		std::cout << "Àå»ç";
	}
	else if (card_1.num == 4 && card_2.num == 6)
	{
		player.rank = ¼¼·ú;
		std::cout << "¼¼·ú";
	}
	else
	{
		int temp = (card_1.num + card_2.num) % 10;
		switch (temp)
		{
		case 0: 
			player.rank = ¸ÁÅë;
			std::cout << "¸ÁÅë"; 
			break;
		case 1: 
			player.rank = ÇÑ²ı;
			std::cout << "ÇÑ²ı"; 
			break;
		case 2: 
			player.rank = µÎ²ı;
			std::cout << "µÎ²ı"; 
			break;
		case 3: 
			player.rank = ¼¼²ı;
			std::cout << "¼¼²ı"; 
			break;
		case 4: 
			player.rank = ³×²ı;
			std::cout << "³×²ı"; 
			break;
		case 5: 
			player.rank = ´Ù¼¸²ı;
			std::cout << "´Ù¼¸²ı"; 
			break;
		case 6: 
			player.rank = ¿©¼¸²ı;
			std::cout << "¿©¼¸²ı"; 
			break;
		case 7: 
			player.rank = ÀÏ°ö²ı;
			std::cout << "ÀÏ°ö²ı"; 
			break;
		case 8: 
			player.rank = ¿©´ü²ı;
			std::cout << "¿©´ü²ı"; 
			break;
		case 9: 
			player.rank = °©¿À;
			std::cout << "°©¿À"; 
			break;
		default: break;
		}
	}
	std::cout << std::endl;
}

void Winner(struct Player* player, int &numOfP)
{
	std::string	winner		{ player[0].name };
	int		topScore	{ player[0].rank};
	int		tie			{ 0 };
	int		winnerNum	{ 0 };

	for (int i = 1; i < numOfP; i++)
	{
		if (!player[i].arrive) continue;
		if (topScore < player[i].rank)
		{
			winner = player[i].name;
			topScore = player[i].rank;
			winnerNum = i;
			tie = 0;
		}
		else if (topScore == player[i].rank)
			tie++;
		
	}

	if (tie > 0)
	{
		std::cout << std::endl;
		std::cout << "µ¿Á¡ÀÇ ÇÃ·¹ÀÌ¾î°¡ ÀÖÀ¸¹Ç·Î, Àç°æ±â ÇÏ°Ú½À´Ï´Ù." << std::endl;
	}
	else
	{
		for (int i = 0; i < numOfP; i++)
			player[i].seed >= 1000 ? player[i].seed -= 1000 : 0;
		player[winnerNum].seed += numOfP * 1000;
		allPrint(player, numOfP);
		std::cout << std::endl;
		std::cout << "ÇÃ·¹ÀÌ¾î [" << winner << "] °¡ ½Â¸®ÇÏ¿© "<< numOfP * 1000 << "¿ø È¹µæ!" << std::endl;
	}

	for (int i = 0; i < numOfP; i++)
		if (player[i].seed == 0 && player[i].arrive)
		{
			player[i].arrive = false;
			numOfP--;
			std::cout << "ÇÃ·¹ÀÌ¾î [" << player[i].name << "] °¡ ¸ğµç µ·À» ÀÒ¾î Å»¶ô!" << std::endl;
		}
}