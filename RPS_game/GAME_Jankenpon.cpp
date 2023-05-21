#include "GAME_jankenpon.h"
#include "Player_Jankenpon.h"
#include "framework.h"

void jankenpon()
{
    int playerNum{ 2 };
    JKP_Player** players = new JKP_Player * [playerNum];
    players[0] = new JKP_Player("�÷��̾�");
    players[1] = new JKP_Player("��ǻ��");

    while (1)
    {
        // �÷��̾� �ʱ�ȭ
        players[0]->init();
        players[1]->init();

        // ȭ�� �����
        system("cls");

        // ���������ֱ�
        std::cout
            << "���� ���ھ�: �÷��̾�[" << players[0]->getWinRate() << "], "
            << "��ǻ��[" << players[1]->getWinRate() << "]" <<
            std::endl << std::endl;

        // ���������� ����
        playerBet(players, true);
        int result = (players[0]->getBackHand() - players[1]->getBackHand() + 3) % 3;

        // ���� ����
        firstRound(players, result);
    }

    for (int i = 0; i < playerNum; i++)
        delete players[i];
    delete[] players;
}

void playerBet(JKP_Player** players, bool isFirst)
{
    int bet;
    while (1)
    {
        if (isFirst)
            std::cout << "�ȳ��� ����! ";
        else
        {
            std::cout << std::endl;
            std::cout << "�����! ";
        }
        std::cout << "[1]���� [2]���� [3]��: ";
        std::cin >> bet;

        if (bet == 1 || bet == 2 || bet == 3) break;
        else std::cout << "�߸��� �Է��Դϴ�." << std::endl;
    }


    players[0]->setHand(bet);

    int random = rand() % 3 + 1;
    std::cout << random << std::endl;
    players[1]->setHand(random);
}

void firstRound(JKP_Player** players, int result)
{
    std::cout << std::endl;
    std::cout <<
        "�÷��̾�� [" << players[0]->getHand() << "]�� " <<
        "��ǻ�ʹ� [" << players[1]->getHand() << "]�� �´�." <<
        std::endl;

    if (result == 0)
    {
        std::cout << "���º�! ����.." << std::endl << std::endl;
        system("pause");
        return;
        // ���º�
    }
    else if (result == 1)
    {
        // �÷��̾� ��
        std::cout << "�÷��̾� ��! �÷��̾��� ����" << std::endl << std::endl;
        players[0]->setRound_1_Win(true);
        system("pause");
    }
    else
    {
        // ��ǻ�� ��
        std::cout << "��ǻ�� ��! ��ǻ���� ����" << std::endl << std::endl;
        players[1]->setRound_1_Win(true);
        system("pause");
    }

    while (1)
    {
        playerBet(players, false);
        if (players[0]->getRound_1_Win()) // �÷��̾ �¸��ߴٸ�..
        {
            int result = (players[0]->getBackHand() - players[1]->getBackHand() + 3) % 3;
            secondRound(players[0], players[1], result);
        }
        else if (players[1]->getRound_1_Win()) // ��ǻ�Ͱ� �¸��ߴٸ�..
        {
            int result = (players[1]->getBackHand() - players[0]->getBackHand() + 3) % 3;
            secondRound(players[1], players[0], result);
        }

        if (players[0]->getRound_2_Win() || players[1]->getRound_2_Win())
            break;
    }
}


void secondRound(JKP_Player* attacker, JKP_Player* defender, int result)
{
    std::cout <<
        "�������� \"" << attacker->getName() << "\"�� [" <<
        attacker->getHand() << "]�� " << std::endl <<
        "������� \"" << defender->getName() << "\"�� [" <<
        defender->getHand() << "]�� �´�." <<
        std::endl;

    if (attacker->getHand() == defender->getHand())
    {
        std::cout << attacker->getName() << " �¸�!!" << std::endl;
        attacker->setRound_2_Win();
        attacker->setWinRate();
    }
    else
    {
        if (result == 1)
        {
            // ������ ��
            std::cout << "������ " << attacker->getName() << " ��! ����ؼ� ����" << std::endl;
            return;
        }
        else if (result == 2)
        {
            std::cout << "����� " << defender->getName() << " ��! ������ȯ!" << std::endl;
            // ����� ��
            defender->setRound_1_Win(true);
            attacker->setRound_1_Win(false);
        }
    }
    std::cout << std::endl;
    system("pause");
}