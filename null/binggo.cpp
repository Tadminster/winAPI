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

// 한줄의 빙고여부를 체크할 구조체
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

		cout << "빙고게임" << endl;
		cout << "빙고의 크기는 2~10, ";
		cout << "프로그램을 종료하시려면 그 이하를 입력하세요." << endl << endl;;

		string start = "빙고의 크기를 입력하세요(2~10): ";
		int size{ menuInput(10, start) };

		if (size > 1 && size < 11)
		{
			system("cls");
			mainGame(size);
		}
		else if (size > 10)
		{
			cout << "10이하로 입력하세요." << endl;
			Sleep(2000);
		}
		else exit(1);
	}
	
}

/* 플레이어 입력 */
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
			cout << "[ERROR] '문자'가 입력되었습니다." << endl;
			cout << endl;
			continue;
		}

		//overflow checking
		if (input < 0 || input > sizeBing)
			cout << "[ERROR] '값'이 작거나 큽니다." << endl;
		else break;
		cout << endl;
	}

	return input;
}


void mainGame(int size)
{
	// dynamic 2d array
	string** bingoDeck = new string* [size];	// 실제 빙고배열
	bool** bingoBool = new bool* [size];		// 각 칸의 빙고여부
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

	Bingo bingo = { size }; // 빙고 여부를 저장할 구조체
	int globalBingo{ 0 };	// 빙고 개수를 저장할 변수

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
		cout << "빙고: " << globalBingo << endl;
		

		string inputText = "0 ~ " + to_string(size*size-1) + " 사이의 숫자를 입력하세요 : ";
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

	cout << "모든 빙고를 맞췄습니다!" << endl;
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
			cout << "입력:";
			string inputStr;
			cin >> inputStr;
			bingoDeck[i][j] = inputStr;

			system("cls");
			printBingo(bingoDeck, bingoBool, size);
		}
		cout << endl;
	}
}

/* 배열을 출력(2차원배열, 배열의크기) */
void printBingo(string** bingoDeck, bool** bingoBool, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// 공백 미출력
			if (bingoDeck[i][j] == "") return;

			cout << "[";
			// 빙고판 맞췄을시 색상넣기
			if (bingoBool[i][j] == true)
				cout << "\033[1;32m";

			cout << bingoDeck[i][j].substr(0, 10);

			// 5글자 초과하면 ..로 처리
			if (bingoDeck[i][j].size() > 11)
				cout << "..";

			// 5글자 미만이면 공백으로 처리
			if (bingoDeck[i][j].size() < 12)
			{
				int len = (12 - bingoDeck[i][j].size()) / 2;
				for (int k = 0; k < len; k++)
					cout << "  ";

			}
				
			// 흰색으로 초기화
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

/* 입력값에 해당하는 배열검색 & 처리(2차원배열, 입력값) */
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
(빙고 2차원 배열, 배열크기, 검사할 세로줄, 검사할 가로줄, 빙고여부, 글로벌빙고카운터*/
void checkHead(bool** bingoBool, int size, struct bingo& bing, int& globalBingo)
{
	for (int i = 0; i < size; i++)
	{
		if (!bing.col[i])				// 세로줄
			bRowCol(bingoBool, size, -1, i, bing.col[i], globalBingo);
		if (!bing.row[i])				// 가로줄
			bRowCol(bingoBool, size, i, -1, bing.row[i], globalBingo);
		if (i < 2 && !bing.cross[i])	// 대각선 
			bCross(bingoBool, size, i, bing.cross[i], globalBingo);
	}
}

/* row-col 빙고 Check
(2차원 빙고배열, 배열크기, 검사할 세로줄, 검사할 가로줄, 빙고여부, 글로벌빙고카운터)*/
void bRowCol(bool** bingoBool, int size, int col, int row, bool& bBing, int& globalBingo)
{
	int tempCol{ col },						// 가로/세로줄 호환성을 위한 임시변수
		tempRow{ row };					
	int cnt{ 0 };							// 한줄의 X 개수를 저장할 임시 카운터
	for (int j = 0; j < size; j++)
	{
		if (col == -1)						// -1이면 해당방향을 j 변수로 쓴다는 의미
			tempCol = j;					// 예를 들어서 세로줄 검사면 [0,0] [0,1] [0,2]..
		else if (row == -1)					// col은 고정되어있고 row만 바뀌기 때문
			tempRow = j;

		if (bingoBool[tempCol][tempRow] == true)	// 해당 칸이 -1이면 X 개수++
			cnt++;
		if (cnt == size)					// X 개수가 size와 같으면 빙고
		{
			globalBingo++;
			bBing = true;
			break;
		}
	}
}

/* 대각선 빙고 Check 
(2차원 빙고배열, 배열크기, 대각선방향 빙고여부, 글로벌빙고카운터)*/
void bCross(bool** bingoBool, int size, int direction, bool& bBing, int& globalBingo)
{
	int tempCol{ 0 },	// 대각선 방향 호환성을 위한 임시변수		
		tempRow{ 0 };
	if (direction == 1)	// direction == 0 ? 좌상>우하 : 우상>좌하
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

		if (direction == 0) // 대각선 방향에 따라 변수 증가감이 다르기 때문에
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