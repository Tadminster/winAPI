#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

/* 배열의 크기 row * col */
#define row 5
#define col 5

/* 현재 좌표를 저장 */
typedef struct current
{
	int x, y;
}CUR;

void shuffle(int puzzle[][row]);
void printPuzzle(int puzzle[][row]);
CUR inputArrow(int puzzle[][row], CUR cur);

int main()
{
	// 퍼즐을 담을 2차원 배열
	int puzzle[5][5];
	// 배열 초기화
	{
		int temp{ 0 };
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				puzzle[i][j] = temp++;
	}

	// 랜덤함수, 섞기
	srand((unsigned int)time(NULL));
	shuffle(puzzle);

	// 빈칸이 될 좌표 지정
	CUR cur{ 4, 4 };
	while (1)
	{
		system("cls");					//화면초기화

		cout << "\t   슬라이드 퍼즐" << endl;
		cout << endl;

		printPuzzle(puzzle);			//화면그리기
		cout << endl;
		cout << "    방향키를 눌러 움직이세요.";
		
		cur = inputArrow(puzzle, cur);	//입력받기
	}
}

// 카드섞기
void shuffle(int puzzle[][row])
{

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			int random = rand() % 5;
			if (i == 0 && j == 0) continue;
			else if (j == 0 && random == 0) continue;
			else swap(puzzle[i][j], puzzle[j][random]);
		}
	}
	swap(puzzle[0][0], puzzle[4][4]);
}

// 출력하기
void printPuzzle(int puzzle[][row])
{

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			// 0은 빈칸으로 출력
			if (puzzle[i][j] == 0) 
				cout << " \t";
			// 퍼즐이 제자리가 맞으면 색상을 입힘
			else if (puzzle[i][j] == i * 5 + j) 
				cout << "\033[1;36m" << puzzle[i][j] << "\033[0m\t";
			// 그 밖엔 일반출력
			else 
				cout << puzzle[i][j] << "\t";

		}
		cout << endl << endl;
	}
}

// 키보드 입력받기
CUR inputArrow(int arr[][row], CUR cur)
{
	int ch = 0;
	ch = _getch();		// read key press
	if (ch == 0xE0) {	// check for arrow key
		ch = _getch();	// read arrow direction
		// up
		if (ch == 72)
		{
			if (cur.x != 0)
			{
				swap(arr[cur.x][cur.y], arr[cur.x - 1][cur.y]);
				cur.x--;
			}
		}
		// down
		else if (ch == 80)
		{
			if (cur.x != 4)
			{
				swap(arr[cur.x][cur.y], arr[cur.x + 1][cur.y]);
				cur.x++;
			}
		}
		// left
		else if (ch == 75)
		{
			if (cur.y != 0)
			{
				swap(arr[cur.x][cur.y], arr[cur.x][cur.y - 1]);
				cur.y--;
			}
		}
		// right
		else if (ch == 77)
		{
			if (cur.y != 4)
			{
				swap(arr[cur.x][cur.y], arr[cur.x][cur.y + 1]);
				cur.y++;
			}
		}
	}

	return cur;
}
