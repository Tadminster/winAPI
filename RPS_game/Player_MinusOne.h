#pragma once
#include "framework.h"

class MO_Player
{
private:
	std::string name;
	std::string status;
	int hand[3];
	bool isAlive{ true };

public:
	MO_Player(std::string name);

	std::string getName();

	bool getIsAlive();

	void playerInit();

	int getHandLeft();
	int getHandRight();
	void setHand(int left, int right);

	void setSelectHand(int select);
	int getSelectHand();

	void printAll(bool bMulligan);


	std::string branchRPS(int x);

	void setStatus(std::string str);

	void setIsAlive(bool b);
};