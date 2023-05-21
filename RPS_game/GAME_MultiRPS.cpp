#pragma once
#include "GAME_MultiRPS.h"
#include "Player_MRPS.h"
#include "framework.h"

void multiRPS()
{
    // �÷��̾� �� �Է� �ޱ�
    std::cout << "�÷��̾� �� �Է�: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;
    int numOfSurv{ numOfPlayers };

    // �÷��̾� ��ü ����
    MRPS_Player** players = new MRPS_Player * [numOfPlayers];
    RPS* rps = new RPS();
    for (int i = 0; i < numOfPlayers; i++)
    {
        std::cout << "[" << i + 1 << "]�� �÷��̾� �̸� �Է�: ";
        std::string tempName;
        std::cin >> tempName;
        players[i] = new MRPS_Player(tempName);
    }

    while (1)
    {
        // ���������� ���� �ʱ�ȭ
        rps->init();

        // �÷��̾� �ʱ�ȭ
        for (int i = 0; i < numOfPlayers; i++)
        {
            if (players[i]->getIsAlive())
                players[i]->playerInit();
        }

        // ���������� ����
        rpsBet(players, numOfPlayers, rps);

        // �ؽ�Ʈ�� ����ó�� �� ���
        system("cls");
        result(players, numOfPlayers, rps, numOfSurv, true);
        print(players, numOfPlayers);
        system("pause");

        // ����������� ����ó�� �� ���
        result(players, numOfPlayers, rps, numOfSurv, false);

        if (numOfSurv == 1)
        {
            for (int i = 0; i < numOfPlayers; i++)
                if (players[i]->getIsAlive())
                {
                    std::cout << "\"" << players[i]->getName() << "\" �÷��̾� �¸�!" << std::endl;
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

// ��ü ���
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
    std::cout << "�ȳ��� ����! ����, ����, ��!" << std::endl;
    std::cout << "�ƹ�Ű�� �Է� : ";
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
    // ��� ���� �� üũ
    int tempAlive{ 0 };
    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive()) tempAlive++;

    int* arrSize = rps->SizeOfRPS();

    // ����, ����, ���� ��� 1�� �̻� ���� ��
    if (arrSize[0] > 0 && arrSize[1] > 0 && arrSize[2] > 0)
        rps->allSetStatus(3, players, "����");

    // ��ΰ� ���� ���� ���� ��
    else if (arrSize[0] == tempAlive || arrSize[1] == tempAlive || arrSize[2] == tempAlive)
    {
        int tempNum = arrSize[0] > 0 ? 0 : arrSize[1] > 0 ? 1 : 2;
        rps->allSetStatus(tempNum, players, "����");
    }

    // ���� �ٸ� �͵� �ΰ��� ���� ��
    else
    {
        if (arrSize[0] == 0) // ���� �ȳ��� ��
        {
            rps->losers(1, players, onlyText, numOfSurv);  // ���� �й�
            rps->allSetStatus(2, players, "�̰��");       // �� �¸�
        }
        else if (arrSize[1] == 0) // ���� �ȳ��� ��
        {
            rps->losers(2, players, onlyText, numOfSurv);   // �� �й�
            rps->allSetStatus(0, players, "�̰��");        // ���� �¸�
        }
        else if (arrSize[2] == 0) // �� �ȳ��� ��
        {
            rps->losers(0, players, onlyText, numOfSurv);   // ���� �й�
            rps->allSetStatus(1, players, "�̰��");        // ���� �¸�
        }
    }

    delete[] arrSize;
}