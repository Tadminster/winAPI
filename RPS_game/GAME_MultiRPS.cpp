#pragma once
#include "GAME_MultiRPS.h"
#include "Player_MRPS.h"
#include "framework.h"

void multiRPS()
{
    // 플레이어 수 입력 받기
    std::cout << "플레이어 수 입력: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;
    int numOfSurv{ numOfPlayers };

    // 플레이어 객체 생성
    MRPS_Player** players = new MRPS_Player * [numOfPlayers];
    RPS* rps = new RPS();
    for (int i = 0; i < numOfPlayers; i++)
    {
        std::cout << "[" << i + 1 << "]번 플레이어 이름 입력: ";
        std::string tempName;
        std::cin >> tempName;
        players[i] = new MRPS_Player(tempName);
    }

    while (1)
    {
        // 가위바위보 벡터 초기화
        rps->init();

        // 플레이어 초기화
        for (int i = 0; i < numOfPlayers; i++)
        {
            if (players[i]->getIsAlive())
                players[i]->playerInit();
        }

        // 가위바위보 내기
        rpsBet(players, numOfPlayers, rps);

        // 텍스트만 승패처리 후 출력
        system("cls");
        result(players, numOfPlayers, rps, numOfSurv, true);
        print(players, numOfPlayers);
        system("pause");

        // 멤버변수까지 승패처리 후 출력
        result(players, numOfPlayers, rps, numOfSurv, false);

        if (numOfSurv == 1)
        {
            for (int i = 0; i < numOfPlayers; i++)
                if (players[i]->getIsAlive())
                {
                    std::cout << "\"" << players[i]->getName() << "\" 플레이어 승리!" << std::endl;
                    system("pause");
                    break;
                }
            break;
        }
    }

    for (int i = 0; i < numOfPlayers; i++)
        delete players[i];
    delete[] players;
    delete rps;
}

// 전체 출력
void print(MRPS_Player** players, int numOfPlayers)
{
    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive())
            players[i]->printAll();
}


void rpsBet(MRPS_Player** players, int numOfPlayers, RPS* rps)
{
    int random;
    system("cls");
    std::cout << "안내면 진다! 가위, 바위, 보!" << std::endl;
    std::cout << "아무키나 입력 : ";
    int wait;
    std::cin >> wait;
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (players[i]->getIsAlive())
        {
            random = rand() % 3;
            rps->push(random, i);
            players[i]->setHand(random);
        }
    }
}

void result(MRPS_Player** players, int numOfPlayers, RPS* rps, int& numOfSurv, bool onlyText)
{
    // 살아 남은 수 체크
    int tempAlive{ 0 };
    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive()) tempAlive++;

    int* arrSize = rps->SizeOfRPS();

    // 가위, 바위, 보가 모두 1개 이상씩 있을 때
    if (arrSize[0] > 0 && arrSize[1] > 0 && arrSize[2] > 0)
        rps->allSetStatus(3, players, "비겼다");

    // 모두가 같은 것을 냈을 때
    else if (arrSize[0] == tempAlive || arrSize[1] == tempAlive || arrSize[2] == tempAlive)
    {
        int tempNum = arrSize[0] > 0 ? 0 : arrSize[1] > 0 ? 1 : 2;
        rps->allSetStatus(tempNum, players, "비겼다");
    }

    // 각자 다른 것들 두개씩 냈을 때
    else
    {
        if (arrSize[0] == 0) // 가위 안냈을 때
        {
            rps->losers(1, players, onlyText, numOfSurv);  // 바위 패배
            rps->allSetStatus(2, players, "이겼다");       // 보 승리
        }
        else if (arrSize[1] == 0) // 바위 안냈을 때
        {
            rps->losers(2, players, onlyText, numOfSurv);   // 보 패배
            rps->allSetStatus(0, players, "이겼다");        // 가위 승리
        }
        else if (arrSize[2] == 0) // 보 안냈을 때
        {
            rps->losers(0, players, onlyText, numOfSurv);   // 가위 패배
            rps->allSetStatus(1, players, "이겼다");        // 바위 승리
        }
    }

    delete[] arrSize;
}