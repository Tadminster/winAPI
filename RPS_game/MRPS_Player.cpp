#pragma once
#include "framework.h"
#include "Player_MRPS.h"


MRPS_Player::MRPS_Player(std::string name)
{
    this->name = name;
}

void MRPS_Player::setHand(int x)
{
    if (x == 0)
        this->hand = "가위";
    else if (x == 1)
        this->hand = "바위";
    else if (x == 2)
        this->hand = "보";
}

std::string MRPS_Player::getName()
{
    return this->name;
}

std::string MRPS_Player::getHand()
{
    return this->hand;
}

void MRPS_Player::setStatus(std::string str)
{
    this->status = str;
}

std::string MRPS_Player::getStatus()
{
    return this->status;
}

void MRPS_Player::setIsAlive(bool b)
{
    this->isAlive = b;
}

bool MRPS_Player::getIsAlive()
{
    return this->isAlive;
}

void MRPS_Player::playerInit()
{
    this->hand = "";
    this->status = "";
}

void MRPS_Player::printAll()
{
    std::cout
        << this->name << "\t"
        << this->hand << "\t"
        << this->status << std::endl;
}