#pragma once
#include "framework.h"

class MRPS_Player
{
private:
    std::string name;
    std::string hand;
    std::string status{ "" };
    bool        isAlive{ true };

public:
    MRPS_Player(std::string name);

    void setHand(int x);

    std::string getName();

    std::string getHand();

    void setStatus(std::string str);
    std::string getStatus();

    void setIsAlive(bool b);
    bool getIsAlive();

    void playerInit();
    void printAll();
};