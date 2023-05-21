#pragma once
#include "framework.h"
#include "Player_MinusOne.h"

class RPS_MinusOne
{
private:
	std::vector<int> scissors;
	std::vector<int> rock;
	std::vector<int> paper;

public:

	void push(int type, int playerNum);

	void init();

	int* SizeOfRPS();

	void allSetStatus(int type, MO_Player** players, std::string str);

	void losers(int losers, MO_Player** players, bool onlyText, int& numOfSurv);
};