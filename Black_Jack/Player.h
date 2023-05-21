#pragma once

class Player
{
private:
	std::string	name;
	std::string	status;
	int		seed{ 10000 };
	int		sum{ 0 };
	int		aCnt{ 0 };
	bool	isDone{ false };
	vector<TrumpCard> hand;

public:
	Player(std::string name)
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

	void cardPrintBody(int i, int side, std::string shape, int number) const
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

	//bool selectA()
	//{
	//	int temp{ 0 };
	//	for (auto& n : this->hand)
	//		if (n.getNumber() == 1) temp++;

	//	if (this->aCnt < temp)
	//	{
	//		std::cout << std::endl;
	//		std::cout << "[1] 1     [2] 11" << std::endl;
	//		std::cout << "A 카드를 몇으로 사용하시겠습니까: ";

	//		while (true)
	//		{
	//			std::string input;
	//			std::cin >> input;
	//			if (input == "1")
	//				break;
	//			else if (input == "2")
	//			{
	//				this->sum += 10;
	//				break;
	//			}
	//			else
	//				std::cout << "잘못된 입력입니다." << std::endl;
	//		}
	//		this->aCnt++;
	//		return true;
	//	}
	//	return false;
	//}

	bool selectA()
	{
		int input{ 0 }, temp{ 0 };
		for (auto& n : this->hand)
			if (n.getNumber() == 1) temp++;

		if (this->aCnt < temp)
		{
			this->aCnt++;
			return true;
		}
		return false;
	}

	std::string getName()
	{
		return this->name;
	}

	void setStatus(std::string str)
	{
		this->status = str;
	}

	std::string getStatus()
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


	void setSum(int x)
	{
		this->sum += x;
	}

	int getSum()
	{
		return this->sum;
	}

	void setInit()
	{
		this->sum = 0;
		this->aCnt = 0;
		this->status = "";
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