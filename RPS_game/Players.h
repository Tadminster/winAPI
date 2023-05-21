#pragma once
#pragma once
#include "framework.h"

class Player
{
private:
    std::string name;
    std::string hand;
    bool        is1stWin{ false };
    bool        is2ndWin{ false };
    int         backHand;
    int         winRate{ 0 };
public:
    Player(std::string name)
    {
        this->name = name;
    }

    void init()
    {
        this->backHand = 0;
        this->hand = "";
        this->is1stWin = false;
        this->is2ndWin = false;
    }

    void setRound_1_Win(bool b)
    {
        this->is1stWin = b;
    }

    bool getRound_1_Win()
    {
        return this->is1stWin;
    }

    void setRound_2_Win()
    {
        this->is2ndWin = true;
    }

    bool getRound_2_Win()
    {
        return this->is2ndWin;
    }


    std::string getName()
    {
        return this->name;
    }

    void setHand(int x)
    {
        this->backHand = x - 1;

        if (x == 1)
            this->hand = "가위";
        else if (x == 2)
            this->hand = "바위";
        else if (x == 3)
            this->hand = "보";
    }

    std::string getHand()
    {
        return this->hand;
    }

    int getBackHand()
    {
        return this->backHand;
    }

    int getWinRate()
    {
        return this->winRate;
    }

    void setWinRate()
    {
        this->winRate = +1;
    }
};