#include "framework.h"
#include "GAME_MinusOne.h"
#include "GAME_Jankenpon.h"
#include "GAME_MultiRPS.h"


bool menuInput();
int ruleInput();

int main()
{
    srand((unsigned int)time(NULL));
    while (menuInput())
    {
        int ruleSelect{ ruleInput() };
        if (ruleSelect == 1) // 기본룰
        {
            multiRPS();
        }
        else if (ruleSelect == 2) // 묵찌빠
        {
            jankenpon();
        }
        else if (ruleSelect == 3) // 하나빼기
        {
            minusOne();
        }
    }
}

bool menuInput()
{
    std::string input;
    while (1)
    {
        system("cls");
        std::cout << "가위-바위-보!" << std::endl;
        std::cout << "[1] 시작하기" << std::endl;
        std::cout << "[2] 종료하기" << std::endl;
        std::cout << "원하는 옵션을 선택하세요: ";
        std::cin >> input;
        if (input == "1") return true;
        else if (input == "2") exit(1);
        else std::cout << "올바른 옵션을 선택하세요." << std::endl;
    }
}

int ruleInput()
{
    std::string input;
    while (1)
    {
        system("cls");
        std::cout << "[1] 1:n 가위바위보" << std::endl;
        std::cout << "[2] 1:1 묵찌빠" << std::endl;
        std::cout << "[3] 1:n 하나빼기 " << std::endl;
        std::cout << "룰을 선택하세요: ";
        std::cin >> input;
        if (input == "1") return 1;
        else if (input == "2") return 2;
        else if (input == "3") return 3;
        else std::cout << "올바른 옵션을 선택하세요." << std::endl;
    }
    return 0;
}