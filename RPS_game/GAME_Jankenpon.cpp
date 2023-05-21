#include "GAME_jankenpon.h"
#include "Player_Jankenpon.h"
#include "framework.h"

void jankenpon()
{
    int playerNum{ 2 };
    JKP_Player** players = new JKP_Player * [playerNum];
    players[0] = new JKP_Player("플레이어");
    players[1] = new JKP_Player("컴퓨터");

    while (1)
    {
        // 플레이어 초기화
        players[0]->init();
        players[1]->init();

        // 화면 지우고
        system("cls");

        // 전적보여주기
        std::cout
            << "현재 스코어: 플레이어[" << players[0]->getWinRate() << "], "
            << "컴퓨터[" << players[1]->getWinRate() << "]" <<
            std::endl << std::endl;

        // 가위바위보 내기
        playerBet(players, true);
        int result = (players[0]->getBackHand() - players[1]->getBackHand() + 3) % 3;

        // 게임 시작
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
            std::cout << "안내면 진다! ";
        else
        {
            std::cout << std::endl;
            std::cout << "묵찌빠! ";
        }
        std::cout << "[1]가위 [2]바위 [3]보: ";
        std::cin >> bet;

        if (bet == 1 || bet == 2 || bet == 3) break;
        else std::cout << "잘못된 입력입니다." << std::endl;
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
        "플레이어는 [" << players[0]->getHand() << "]를 " <<
        "컴퓨터는 [" << players[1]->getHand() << "]를 냈다." <<
        std::endl;

    if (result == 0)
    {
        std::cout << "무승부! 재대결.." << std::endl << std::endl;
        system("pause");
        return;
        // 무승부
    }
    else if (result == 1)
    {
        // 플레이어 승
        std::cout << "플레이어 승! 플레이어의 공격" << std::endl << std::endl;
        players[0]->setRound_1_Win(true);
        system("pause");
    }
    else
    {
        // 컴퓨터 승
        std::cout << "컴퓨터 승! 컴퓨터의 공격" << std::endl << std::endl;
        players[1]->setRound_1_Win(true);
        system("pause");
    }

    while (1)
    {
        playerBet(players, false);
        if (players[0]->getRound_1_Win()) // 플레이어가 승리했다면..
        {
            int result = (players[0]->getBackHand() - players[1]->getBackHand() + 3) % 3;
            secondRound(players[0], players[1], result);
        }
        else if (players[1]->getRound_1_Win()) // 컴퓨터가 승리했다면..
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
        "공격자인 \"" << attacker->getName() << "\"는 [" <<
        attacker->getHand() << "]를 " << std::endl <<
        "방어자인 \"" << defender->getName() << "\"는 [" <<
        defender->getHand() << "]를 냈다." <<
        std::endl;

    if (attacker->getHand() == defender->getHand())
    {
        std::cout << attacker->getName() << " 승리!!" << std::endl;
        attacker->setRound_2_Win();
        attacker->setWinRate();
    }
    else
    {
        if (result == 1)
        {
            // 공격자 승
            std::cout << "공격자 " << attacker->getName() << " 승! 계속해서 공격" << std::endl;
            return;
        }
        else if (result == 2)
        {
            std::cout << "방어자 " << defender->getName() << " 승! 공수전환!" << std::endl;
            // 방어자 승
            defender->setRound_1_Win(true);
            attacker->setRound_1_Win(false);
        }
    }
    std::cout << std::endl;
    system("pause");
}