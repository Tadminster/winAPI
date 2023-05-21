#pragma once
#include "framework.h"

class JKP_Player
{
private:
    std::string name;
    std::string hand;
    bool        is1stWin    { false };
    bool        is2ndWin    { false };
    int         backHand;
    int         winRate     { 0 };
public:
    JKP_Player(std::string name);

    void init();

    void setRound_1_Win(bool b);
    bool getRound_1_Win();
    void setRound_2_Win();
    bool getRound_2_Win();

    std::string getName();

    void setHand(int x);
    std::string getHand();

    int getBackHand();

    int getWinRate();
    void setWinRate();
};