#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include <windows.h>
using namespace std;

void mainGame(int size);
void deckInit(string** bingoDeck, bool** bingoBool, int size);
void printBingo(string** bingoDeck, bool** bingoBool, int size);
int menuInput(int size, string& text);
string playerInput();
void bResult(string** bingoDeck, bool** bingoBool, string inputStr, int size);
void checkHead(bool** bingoBool, int size, struct bingo& bing, int& globalBingo);
void bRowCol(bool** arr, int size, int col, int row, bool& bBing, int& globalBingo);
void bCross(bool** arr, int size, int direction, bool& bBing, int& globalBingo);

// ������ �����θ� üũ�� ����ü
typedef struct bingo
{
	int size;
	bool* row = new bool[size];
	bool* col = new bool[size];
	bool cross[2]{ false, false };
}Bingo;

int main()
{
	// player input
	while (1)
	{
		system("cls");

		cout << "�������" << endl;
		cout << "������ ũ��� 2~10, ";
		cout << "���α׷��� �����Ͻ÷��� �� ���ϸ� �Է��ϼ���." << endl << endl;;

		string start = "������ ũ�⸦ �Է��ϼ���(2~10): ";
		int size{ menuInput(10, start) };

		if (size > 1 && size < 11)
		{
			system("cls");
			mainGame(size);
		}
		else if (size > 10)
		{
			cout << "10���Ϸ� �Է��ϼ���." << endl;
			Sleep(2000);
		}
		else exit(1);
	}
	
}

/* �÷��̾� �Է� */
int menuInput(int size, string& text)
{
	string str;
	int input{ 0 };
	int sizeBing = size * size - 1;
	while (1)
	{
		cout << text;
		cin >> str;

		try
		{
			input = stoi(str);
		}
		// string checking
		catch (const invalid_argument& e)
		{
			cout << "[ERROR] '����'�� �ԷµǾ����ϴ�." << endl;
			cout << endl;
			continue;
		}

		//overflow checking
		if (input < 0 || input > sizeBing)
			cout << "[ERROR] '��'�� �۰ų� Ů�ϴ�." << endl;
		else break;
		cout << endl;
	}

	return input;
}


void mainGame(int size)
{
	// dynamic 2d array
	string** bingoDeck = new string* [size];	// ���� ����迭
	bool** bingoBool = new bool* [size];		// �� ĭ�� ������
	for (int i = 0; i < size; i++)
	{
		bingoDeck[i] = new string[size];
		bingoBool[i] = new bool[size];

	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			bingoBool[i][j] = false;

	// bingoDeck init
	deckInit(bingoDeck, bingoBool, size);

	Bingo bingo = { size }; // ���� ���θ� ������ ����ü
	int globalBingo{ 0 };	// ���� ������ ������ ����

	for (int i = 0; i < bingo.size; i++)
	{
		bingo.row[i] = false;
		bingo.col[i] = false;
	}

	while (globalBingo < (size * 2 + 2))
	{
		system("cls");
		printBingo(bingoDeck, bingoBool, size);

		// input
		cout << endl;
		cout << "����: " << globalBingo << endl;
		

		string inputText = "0 ~ " + to_string(size*size-1) + " ������ ���ڸ� �Է��ϼ��� : ";
		string inputStr = playerInput();

		bResult(bingoDeck, bingoBool, inputStr, size);
		checkHead(bingoBool, size, bingo, globalBingo);
	}

	for (int i = 0; i < size; ++i) {
		delete[] bingoDeck[i];
		delete[] bingoBool[i];
	}
	delete[] bingoDeck;
	delete[] bingoBool;

	cout << "��� ���� ������ϴ�!" << endl;
	Sleep(4000);
}

void deckInit(string** bingoDeck, bool** bingoBool, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			bingoDeck[i][j] = "";
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "�Է�:";
			string inputStr;
			cin >> inputStr;
			bingoDeck[i][j] = inputStr;

			system("cls");
			printBingo(bingoDeck, bingoBool, size);
		}
		cout << endl;
	}
}

/* �迭�� ���(2�����迭, �迭��ũ��) */
void printBingo(string** bingoDeck, bool** bingoBool, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// ���� �����
			if (bingoDeck[i][j] == "") return;

			cout << "[";
			// ������ �������� ����ֱ�
			if (bingoBool[i][j] == true)
				cout << "\033[1;32m";

			cout << bingoDeck[i][j].substr(0, 10);

			// 5���� �ʰ��ϸ� ..�� ó��
			if (bingoDeck[i][j].size() > 11)
				cout << "..";

			// 5���� �̸��̸� �������� ó��
			if (bingoDeck[i][j].size() < 12)
			{
				int len = (12 - bingoDeck[i][j].size()) / 2;
				for (int k = 0; k < len; k++)
					cout << "  ";

			}
				
			// ������� �ʱ�ȭ
			if (bingoBool[i][j] == true)
				cout << "\033[0m";

			cout << "]\t";
		}


		cout << endl << endl;
	}
}

string playerInput()
{
	string str;
	cin >> str;
	return str;
}

/* �Է°��� �ش��ϴ� �迭�˻� & ó��(2�����迭, �Է°�) */
void bResult(string** bingoDeck, bool** bingoBool, string inputStr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (bingoDeck[i][j] == inputStr)
			{
				bingoBool[i][j] = true;
				return;
			}

		}
	}
}

/* bingo check branch
(���� 2���� �迭, �迭ũ��, �˻��� ������, �˻��� ������, ������, �۷ι�����ī����*/
void checkHead(bool** bingoBool, int size, struct bingo& bing, int& globalBingo)
{
	for (int i = 0; i < size; i++)
	{
		if (!bing.col[i])				// ������
			bRowCol(bingoBool, size, -1, i, bing.col[i], globalBingo);
		if (!bing.row[i])				// ������
			bRowCol(bingoBool, size, i, -1, bing.row[i], globalBingo);
		if (i < 2 && !bing.cross[i])	// �밢�� 
			bCross(bingoBool, size, i, bing.cross[i], globalBingo);
	}
}

/* row-col ���� Check
(2���� ����迭, �迭ũ��, �˻��� ������, �˻��� ������, ������, �۷ι�����ī����)*/
void bRowCol(bool** bingoBool, int size, int col, int row, bool& bBing, int& globalBingo)
{
	int tempCol{ col },						// ����/������ ȣȯ���� ���� �ӽú���
		tempRow{ row };					
	int cnt{ 0 };							// ������ X ������ ������ �ӽ� ī����
	for (int j = 0; j < size; j++)
	{
		if (col == -1)						// -1�̸� �ش������ j ������ ���ٴ� �ǹ�
			tempCol = j;					// ���� �� ������ �˻�� [0,0] [0,1] [0,2]..
		else if (row == -1)					// col�� �����Ǿ��ְ� row�� �ٲ�� ����
			tempRow = j;

		if (bingoBool[tempCol][tempRow] == true)	// �ش� ĭ�� -1�̸� X ����++
			cnt++;
		if (cnt == size)					// X ������ size�� ������ ����
		{
			globalBingo++;
			bBing = true;
			break;
		}
	}
}

/* �밢�� ���� Check 
(2���� ����迭, �迭ũ��, �밢������ ������, �۷ι�����ī����)*/
void bCross(bool** bingoBool, int size, int direction, bool& bBing, int& globalBingo)
{
	int tempCol{ 0 },	// �밢�� ���� ȣȯ���� ���� �ӽú���		
		tempRow{ 0 };
	if (direction == 1)	// direction == 0 ? �»�>���� : ���>����
	{
		tempCol = 0;
		tempRow = size-1;
	}
	int cnt{ 0 };
	for (int j = 0; j < size; j++)
	{

		if (bingoBool[tempCol][tempRow] == true)
			cnt++;
		if (cnt == size)	
		{
			globalBingo++;
			bBing = true;
			break;
		}

		if (direction == 0) // �밢�� ���⿡ ���� ���� �������� �ٸ��� ������
		{
			tempCol++;
			tempRow++;
		}
		else if (direction == 1)
		{
			tempCol++;
			tempRow--;
		}
	}
}