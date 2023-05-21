#pragma once
#include "framework.h"
#include "RPS_MinusOne.h"
#include "Player_MinusOne.h"

void RPS_MinusOne::push(int type, int playerNum)
{
	if (type == 1)
		scissors.push_back(playerNum);

	else if (type == 2)
		rock.push_back(playerNum);

	else if (type == 3)
		paper.push_back(playerNum);
}

void RPS_MinusOne::init()
{
	this->scissors.clear();
	this->rock.clear();
	this->paper.clear();
}

int* RPS_MinusOne::SizeOfRPS()
{
	int* arr = new int[3];
	arr[0] = this->scissors.size();
	arr[1] = this->rock.size();
	arr[2] = this->paper.size();

	return arr;
}

void RPS_MinusOne::allSetStatus(int type, MO_Player** players, std::string str)
{
	if (type == 0)
	{
		for (auto& i : this->scissors)
			players[i]->setStatus(str);
	}
	else if (type == 1)
	{
		for (auto& i : this->rock)
			players[i]->setStatus(str);
	}
	else if (type == 2)
	{
		for (auto& i : this->paper)
			players[i]->setStatus(str);
	}
	else if (type == 3)
	{
		allSetStatus(0, players, str);
		allSetStatus(1, players, str);
		allSetStatus(2, players, str);
	}
}

void RPS_MinusOne::losers(int losers, MO_Player** players, bool onlyText, int& numOfSurv)
{
	if (losers == 0)
	{
		for (auto& i : this->scissors)
		{
			if (onlyText)
				players[i]->setStatus("졌다");
			else
			{
				players[i]->setIsAlive(false);
				numOfSurv--;
			}
		}
	}
	else if (losers == 1)
	{
		for (auto& i : this->rock)
		{
			if (onlyText)
				players[i]->setStatus("졌다");
			else
			{
				players[i]->setIsAlive(false);
				numOfSurv--;
			}
		}
	}
	else if (losers == 2)
	{
		for (auto& i : this->paper)
		{
			if (onlyText)
				players[i]->setStatus("졌다");
			else
			{
				players[i]->setIsAlive(false);
				numOfSurv--;
			}
		}
	}
}