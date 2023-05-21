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
	����, �Ѳ�, �β�, ����, �ײ�, �ټ���, ������, �ϰ���, ������, ����,
	����, ���, ���, ����, ����, �˸�,
	�涯, �̶�, �ﶯ, �綯, ����, ����, ĥ��, �ȶ�, ����, �嶯,
	�ϻﱤ��, ���ȱ���, ���ȱ���
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
		std::cout << "ȭ������" << std::endl;
		std::string menuText{ "[1]���ӽ��� [2]�����ϱ�: " };
		int menu{ input(menuText, 1, 2) };
		if (menu == 1)
			jankenpon();
		else if (menu == 2)
			exit(1);
	}
}

/* ����� �Է�, ����ó�� */
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
			std::cout << "[ERROR] '����'�� �ԷµǾ����ϴ�." << std::endl;
			std::cout << std::endl;
			continue;
		}

		//overflow checking
		if (input < min || input > max)
			std::cout << "[ERROR] '��'�� �۰ų� Ů�ϴ�." << std::endl;
		else
			break;
		std::cout << std::endl;
	}

	return input;
}


/* ���� ���� */
int jankenpon()
{
	// ī�� ����
	const int cardSize{ 20 };
	Card** cards = new Card*[cardSize];
	for (int i = 0; i < cardSize; i++)
	{
		cards[i] = new Card();

		cards[i].num = (i + 2) / 2;
		if (i == 0 || i == 4 || i == 14)
			cards[i].symbol = "��";
		else
			cards[i].symbol = "��";
	}

	// ���� �ʱ�ȭ
	srand((unsigned int)time(NULL));

	// �÷��̾� ����
	std::string pText{ "�÷��� �� �ο� �� �Է�: " };
	int numOfP{ input(pText, 2, 10) };
	Player* player = new Player[numOfP];

	// �̸� �Է�, �õ� �ʱ�ȭ
	std::string name;
	for (int i = 0; i < numOfP; i++)
	{
		std::cout << i << "�� �÷��̾� �̸�: ";
		std::cin >> name;
		player[i].name = name;
		player[i].seed = 10000;
	}
	//��� �ϱ�� �ӽ� ����
	std::string x;

	// ������ ����
	while (1)
	{
		// ī�� ����
		shuffleCards(cards, cardSize);

		// �÷��̾� ī�� �ʱ�ȭ
		int temp{ 0 };
		for (int i = 0; i < numOfP; i++)
		{
			player[i].card[0] = cards[temp++];
			player[i].card[1] = cards[temp++];
		}

		// ���
		allPrint(player, numOfP);

		// ����ó��
		Winner(player, numOfP);

		// 1�� ������ �� �����¸�
		if (numOfP == 1)
		{
			for (int i = 0; i < numOfP; i++)
			{
				if (player[i].arrive)
					std::cout << std::endl << std::endl;
					std::cout << "�÷��̾� [" << player[i].name << "] �� ���� �¸��߽��ϴ�.";
					std::cout << "�÷��̾� [" << player[i].name << "] �� ���� �¸��߽��ϴ�.";
					std::cout << "�÷��̾� [" << player[i].name << "] �� ���� �¸��߽��ϴ�.";
					std::cin >> x;
					return 1;
			}
		}


		std::cout << "����Ϸ��� �ƹ�Ű�� �Է��ϼ���: ";
		std::cin >> x;

	}


	delete[] player;

	return 1;
}

/* ī�� ���� */
void shuffleCards(struct Card cards[], int cardSize)
{
	for (int i = 0; i < cardSize; i++)
	{
		int j = rand() % 20;
		std::swap(cards[i], cards[j]);
	}
}

/* !�׽�Ʈ��! */
void cardPrint(struct Card cards[], int size)
{
	for (int i = 0; i < size; i++)
		std::cout << cards[i].num << " : " << cards[i].symbol << std::endl;
}

/* ���� ��� */
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

/* ���� ��� ó��*/
void Genealogy(struct Player& player, struct Card& card_1, struct Card& card_2)
{
	if (card_1.symbol == "��" && card_2.symbol == "��")
	{
		if (card_1.num == 3 && card_2.num == 8)
		{
			player.rank = ���ȱ���;
			std::cout << "38����";
		}
		else if (card_1.num == 1 && card_2.num == 8)
		{
			player.rank = ���ȱ���;
			std::cout << "18����";
		}
		else if (card_1.num == 1 && card_2.num == 3)
		{
			player.rank = �ϻﱤ��;
			std::cout << "13����";
		}
	}
	else if (card_1.num == card_2.num)
	{
		switch (card_1.num)
		{
		case 1:
			player.rank = �涯;
			std::cout << "�涯";
			break;
		case 2:
			player.rank = �̶�;
			std::cout << "2��";
			break;
		case 3:
			player.rank = �ﶯ;
			std::cout << "3��";
			break;
		case 4:
			player.rank = �綯;
			std::cout << "4��";
			break;
		case 5:
			player.rank = ����;
			std::cout << "5��";
			break;
		case 6:
			player.rank = ����;
			std::cout << "6��";
			break;
		case 7:
			player.rank = ĥ��;
			std::cout << "7��";
			break;
		case 8:
			player.rank = �ȶ�;
			std::cout << "8��";
			break;
		case 9:
			player.rank = ����;
			std::cout << "9��";
			break;
		case 10:
			player.rank = �嶯;
			std::cout << "�嶯";
			break;
		default: break;
		}
	}
	else if (card_1.num == 1 && card_2.num == 2)
	{
		player.rank = �˸�;
		std::cout << "�˸�";
	}
	else if (card_1.num == 1 && card_2.num == 4)
	{
		player.rank = ����;
		std::cout << "����";
	}
	else if (card_1.num == 1 && card_2.num == 9)
	{
		player.rank = ����;
		std::cout << "����";
	}
	else if (card_1.num == 1 && card_2.num == 10)
	{
		player.rank = ���;
		std::cout << "���";
	}
	else if (card_1.num == 4 && card_2.num == 10)
	{
		player.rank = ���;
		std::cout << "���";
	}
	else if (card_1.num == 4 && card_2.num == 6)
	{
		player.rank = ����;
		std::cout << "����";
	}
	else
	{
		int temp = (card_1.num + card_2.num) % 10;
		switch (temp)
		{
		case 0: 
			player.rank = ����;
			std::cout << "����"; 
			break;
		case 1: 
			player.rank = �Ѳ�;
			std::cout << "�Ѳ�"; 
			break;
		case 2: 
			player.rank = �β�;
			std::cout << "�β�"; 
			break;
		case 3: 
			player.rank = ����;
			std::cout << "����"; 
			break;
		case 4: 
			player.rank = �ײ�;
			std::cout << "�ײ�"; 
			break;
		case 5: 
			player.rank = �ټ���;
			std::cout << "�ټ���"; 
			break;
		case 6: 
			player.rank = ������;
			std::cout << "������"; 
			break;
		case 7: 
			player.rank = �ϰ���;
			std::cout << "�ϰ���"; 
			break;
		case 8: 
			player.rank = ������;
			std::cout << "������"; 
			break;
		case 9: 
			player.rank = ����;
			std::cout << "����"; 
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
		std::cout << "������ �÷��̾ �����Ƿ�, ���� �ϰڽ��ϴ�." << std::endl;
	}
	else
	{
		for (int i = 0; i < numOfP; i++)
			player[i].seed >= 1000 ? player[i].seed -= 1000 : 0;
		player[winnerNum].seed += numOfP * 1000;
		allPrint(player, numOfP);
		std::cout << std::endl;
		std::cout << "�÷��̾� [" << winner << "] �� �¸��Ͽ� "<< numOfP * 1000 << "�� ȹ��!" << std::endl;
	}

	for (int i = 0; i < numOfP; i++)
		if (player[i].seed == 0 && player[i].arrive)
		{
			player[i].arrive = false;
			numOfP--;
			std::cout << "�÷��̾� [" << player[i].name << "] �� ��� ���� �Ҿ� Ż��!" << std::endl;
		}
}