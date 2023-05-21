#pragma once
#include "framework.h"
#include "Player_MRPS.h"

class RPS
{
private:
	std::vector<int> scissors;
	std::vector<int> rock;
	std::vector<int> paper;

public:
	void push(int type, int playerNum);
	int* SizeOfRPS();
	void allSetStatus(int type, MRPS_Player** players, std::string str);
	void losers(int losers, MRPS_Player** players, bool onlyText, int& numOfSurv);
	void init();
};