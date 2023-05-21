#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Player
{
private:
    std::string        name;
    int                seed{ 10000 };
    // 1 = 가위, 2 = 바위, 3 = 보
    int                status{ 0 };

public:
    Player(std::string name)
    {
        this->name = name;
    }

    void setStatus(int status)
    {
        this->status = status;
    }
};

bool menuInput();
void jankenpon();

int main()
{
    srand((unsigned int)time(NULL));
    while (menuInput())
    {
        jankenpon();
    }
}

bool menuInput()
{
    std::string input;
    while (1)
    {
        std::cout << "가위! 바위! 보!" << std::endl;
        std::cout << "[1] 시작하기" << std::endl;
        std::cout << "[2] 종료하기" << std::endl;
        std::cout << "원하는 옵션을 선택하세요: ";
        std::cin >> input;
        if (input == "1") return true;
        else if (input == "2") exit(1);
        else std::cout << "올바른 옵션을 선택하세요." << std::endl;
    }
}

void jankenpon()
{
    // 플레이어 수 입력 받기
    std::cout << "플레이어 수 입력: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;

    // 플레이어 객체 생성
    Player** players = new Player * [numOfPlayers];
    for (int i = 0; i < numOfPlayers; i++)
    {
        std::cout << "플레이어 수 입력: ";
        string tempName;
        cin >> tempName;
        players[i] = new Player(tempName);
    }





    for (int i = 0; i < numOfPlayers; i++)
        delete[] players[i];
    delete[] players;


}
