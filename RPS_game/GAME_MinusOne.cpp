#pragma once
#include "GAME_MinusOne.h"
#include "Player_MinusOne.h"
#include "framework.h"

void minusOne()
{
    // 플레이어 수 입력 받기
    std::cout << "플레이어 수 입력: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;
    int numOfSurv{ numOfPlayers };

    MO_Player** players = new MO_Player*[numOfPlayers];
    RPS_MinusOne* rps = new RPS_MinusOne();
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (i == 0)
            players[i] = new MO_Player("플레이어");
        else 
            players[i] = new MO_Player("컴퓨터0" + std::to_string(i));
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
        rpsBet(players, numOfPlayers);

        // 전체출력
        system("cls");
        print(players, numOfPlayers, true);

        // 하나 선택 후 텍스트만 변경
        selectOne(players, numOfPlayers, rps);
        result(players, numOfPlayers, rps, numOfSurv, true);
        print(players, numOfPlayers, false);

        // isAlive 까지 변경
        system("pause");
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

void rpsBet(MO_Player** players, int numOfPlayers)
{
    int random, left, right;
    system("cls");

    for (int i = 0; i < numOfPlayers; i++)
    {
        if (players[i]->getIsAlive())
        {
            if (i == 0)
            {
                // 플레이어
                std::cout << "[1]가위, [2]바위, [3]보" << std::endl;
                std::cout << "왼손에  무엇을  내시겠습니까? ";
                std::cin >> left;
                std::cout << "오른손에 무엇을 내시겠습니까? ";
                std::cin >> right;
                players[i]->setHand(left, right);

            }
            else
            {
                // 컴퓨터
                left = rand() % 3 + 1;
                right = left + 1 > 3 ? 1 : left + 1;
                players[i]->setHand(left, right);
            }
        }
    }
}

// 전체 출력
void print(MO_Player** players, int numOfPlayers, bool Mulligan)
{
    if (Mulligan)
        std::cout << "\t\t" << "왼손\t" << "오른손" << std::endl;
    else 
        std::cout << "\t\t" << "선택\t" << "결과" << std::endl;

    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive())
            players[i]->printAll(Mulligan);
}

// 하나빼기
void selectOne(MO_Player** players, int numOfPlayers, RPS_MinusOne* rps)
{
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (players[i]->getIsAlive())
        {
            // 플레이어
            if (i == 0)
            {
                std::cout << std::endl;
                std::cout
                    << "[1]" << players[i]->branchRPS(players[i]->getHandLeft()) << ", "
                    << "[2]" << players[i]->branchRPS(players[i]->getHandRight())
                    << std::endl;
                std::cout << "두 손중 무엇을 남기겠습니까? ";
                int select;
                std::cin >> select;

                if (select == 1)
                    players[i]->setSelectHand(players[i]->getHandLeft());
                else if (select == 2)
                    players[i]->setSelectHand(players[i]->getHandRight());
            }
            // 컴퓨터
            else
            {
                int random = rand() % 2 + 1;
                if (random == 1)
                    players[i]->setSelectHand(players[i]->getHandLeft());
                else if (random == 2)
                    players[i]->setSelectHand(players[i]->getHandRight());
            }
            
            rps->push(players[i]->getSelectHand(), i);
        }
    }
}

void result(MO_Player** players, int numOfPlayers, RPS_MinusOne* rps, int& numOfSurv, bool onlyText)
{
    // 살아 남은 수 체크
    int tempAlive{ 0 };
    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive()) tempAlive++;

    int* arrSize = rps->SizeOfRPS();

    std::cout << std::endl;
    std::cout 
        << "가위 [ " << arrSize[0] << " ], "
        << "바위 [ " << arrSize[1] << " ], "
        << "보 [ " << arrSize[2] << " ]"
        << std::endl << std::endl;

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