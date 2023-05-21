#pragma once
#include "framework.h"
#include "Player_MinusOne.h"

MO_Player::MO_Player(std::string name)
{
	this->name = name;
}

std::string MO_Player::getName()
{
	return this->name;
}

bool MO_Player::getIsAlive()
{
	return this->isAlive;
}

void MO_Player::playerInit()
{
	this->status = "";
	this->hand[0] = 0;
	this->hand[1] = 0;
	this->hand[2] = 0;
}

int MO_Player::getHandLeft()
{
	return this->hand[0];
}

int MO_Player::getHandRight()
{
	return this->hand[1];
}

void MO_Player::setHand(int left, int right)
{
	this->hand[0] = left;
	this->hand[1] = right;
}

void MO_Player::setSelectHand(int select)
{
	this->hand[2] = select;
}

int MO_Player::getSelectHand()
{
	return this->hand[2];
}

void MO_Player::printAll(bool bMulligan)
{
	std::cout
		<< this->name << "\t";
	if (bMulligan)
		std::cout << branchRPS(this->hand[0]) << "\t" << branchRPS(this->hand[1]);
	else
		std::cout << branchRPS(this->hand[2]) << "\t" << this->status;
	std::cout << std::endl;
}

std::string MO_Player::branchRPS(int x)
{
	if (x == 1) return "가위";
	else if (x == 2) return "바위";
	else if (x == 3) return "보";
	else return "ERROR";
}

void MO_Player::setStatus(std::string str)
{
	this->status = str;
}

void MO_Player::setIsAlive(bool b)
{
	this->isAlive = b;
}
