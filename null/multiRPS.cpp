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
    // 1 = ����, 2 = ����, 3 = ��
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
        std::cout << "����! ����! ��!" << std::endl;
        std::cout << "[1] �����ϱ�" << std::endl;
        std::cout << "[2] �����ϱ�" << std::endl;
        std::cout << "���ϴ� �ɼ��� �����ϼ���: ";
        std::cin >> input;
        if (input == "1") return true;
        else if (input == "2") exit(1);
        else std::cout << "�ùٸ� �ɼ��� �����ϼ���." << std::endl;
    }
}

void jankenpon()
{
    // �÷��̾� �� �Է� �ޱ�
    std::cout << "�÷��̾� �� �Է�: ";
    int numOfPlayers;
    std::cin >> numOfPlayers;

    // �÷��̾� ��ü ����
    Player** players = new Player * [numOfPlayers];
    for (int i = 0; i < numOfPlayers; i++)
    {
        std::cout << "�÷��̾� �� �Է�: ";
        string tempName;
        cin >> tempName;
        players[i] = new Player(tempName);
    }





    for (int i = 0; i < numOfPlayers; i++)
        delete[] players[i];
    delete[] players;


}
