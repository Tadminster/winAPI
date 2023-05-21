#pragma once
#include "GAME_MinusOne.h"
#include "Player_MinusOne.h"
#include "framework.h"

void minusOne()
{
    // �÷��̾� �� �Է� �ޱ�
    std::cout << "�÷��̾� �� �Է�: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;
    int numOfSurv{ numOfPlayers };

    MO_Player** players = new MO_Player*[numOfPlayers];
    RPS_MinusOne* rps = new RPS_MinusOne();
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (i == 0)
            players[i] = new MO_Player("�÷��̾�");
        else 
            players[i] = new MO_Player("��ǻ��0" + std::to_string(i));
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
        rpsBet(players, numOfPlayers);

        // ��ü���
        system("cls");
        print(players, numOfPlayers, true);

        // �ϳ� ���� �� �ؽ�Ʈ�� ����
        selectOne(players, numOfPlayers, rps);
        result(players, numOfPlayers, rps, numOfSurv, true);
        print(players, numOfPlayers, false);

        // isAlive ���� ����
        system("pause");
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
                // �÷��̾�
                std::cout << "[1]����, [2]����, [3]��" << std::endl;
                std::cout << "�޼տ�  ������  ���ðڽ��ϱ�? ";
                std::cin >> left;
                std::cout << "�����տ� ������ ���ðڽ��ϱ�? ";
                std::cin >> right;
                players[i]->setHand(left, right);

            }
            else
            {
                // ��ǻ��
                left = rand() % 3 + 1;
                right = left + 1 > 3 ? 1 : left + 1;
                players[i]->setHand(left, right);
            }
        }
    }
}

// ��ü ���
void print(MO_Player** players, int numOfPlayers, bool Mulligan)
{
    if (Mulligan)
        std::cout << "\t\t" << "�޼�\t" << "������" << std::endl;
    else 
        std::cout << "\t\t" << "����\t" << "���" << std::endl;

    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive())
            players[i]->printAll(Mulligan);
}

// �ϳ�����
void selectOne(MO_Player** players, int numOfPlayers, RPS_MinusOne* rps)
{
    for (int i = 0; i < numOfPlayers; i++)
    {
        if (players[i]->getIsAlive())
        {
            // �÷��̾�
            if (i == 0)
            {
                std::cout << std::endl;
                std::cout
                    << "[1]" << players[i]->branchRPS(players[i]->getHandLeft()) << ", "
                    << "[2]" << players[i]->branchRPS(players[i]->getHandRight())
                    << std::endl;
                std::cout << "�� ���� ������ ����ڽ��ϱ�? ";
                int select;
                std::cin >> select;

                if (select == 1)
                    players[i]->setSelectHand(players[i]->getHandLeft());
                else if (select == 2)
                    players[i]->setSelectHand(players[i]->getHandRight());
            }
            // ��ǻ��
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
    // ��� ���� �� üũ
    int tempAlive{ 0 };
    for (int i = 0; i < numOfPlayers; i++)
        if (players[i]->getIsAlive()) tempAlive++;

    int* arrSize = rps->SizeOfRPS();

    std::cout << std::endl;
    std::cout 
        << "���� [ " << arrSize[0] << " ], "
        << "���� [ " << arrSize[1] << " ], "
        << "�� [ " << arrSize[2] << " ]"
        << std::endl << std::endl;

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