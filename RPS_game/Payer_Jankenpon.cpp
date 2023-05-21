#pragma once
#include "framework.h"
#include "Player_Jankenpon.h"


JKP_Player::JKP_Player(std::string name)
{
    this->name = name;
}

void JKP_Player::init()
{
    this->backHand = 0;
    this->hand = "";
    this->is1stWin = false;
    this->is2ndWin = false;
}

void JKP_Player::setRound_1_Win(bool b)
{
    this->is1stWin = b;
}

bool JKP_Player::getRound_1_Win()
{
    return this->is1stWin;
}

void JKP_Player::setRound_2_Win()
{
    this->is2ndWin = true;
}

bool JKP_Player::getRound_2_Win()
{
    return this->is2ndWin;
}


std::string JKP_Player::getName()
{
    return this->name;
}

void JKP_Player::setHand(int x)
{
    this->backHand = x - 1;

    if (x == 1)
        this->hand = "가위";
    else if (x == 2)
        this->hand = "바위";
    else if (x == 3)
        this->hand = "보";
}

std::string JKP_Player::getHand()
{
    return this->hand;
}

int JKP_Player::getBackHand()
{
    return this->backHand;
}

int JKP_Player::getWinRate()
{
    return this->winRate;
}

void JKP_Player::setWinRate()
{
    this->winRate = +1;
}