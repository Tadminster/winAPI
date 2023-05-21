#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

/* �迭�� ũ�� row * col */
#define row 5
#define col 5

/* ���� ��ǥ�� ���� */
typedef struct current
{
	int x, y;
}CUR;

void shuffle(int puzzle[][row]);
void printPuzzle(int puzzle[][row]);
CUR inputArrow(int puzzle[][row], CUR cur);

int main()
{
	// ������ ���� 2���� �迭
	int puzzle[5][5];
	// �迭 �ʱ�ȭ
	{
		int temp{ 0 };
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				puzzle[i][j] = temp++;
	}

	// �����Լ�, ����
	srand((unsigned int)time(NULL));
	shuffle(puzzle);

	// ��ĭ�� �� ��ǥ ����
	CUR cur{ 4, 4 };
	while (1)
	{
		system("cls");					//ȭ���ʱ�ȭ

		cout << "\t   �����̵� ����" << endl;
		cout << endl;

		printPuzzle(puzzle);			//ȭ��׸���
		cout << endl;
		cout << "    ����Ű�� ���� �����̼���.";
		
		cur = inputArrow(puzzle, cur);	//�Է¹ޱ�
	}
}

// ī�弯��
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

// ����ϱ�
void printPuzzle(int puzzle[][row])
{

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			// 0�� ��ĭ���� ���
			if (puzzle[i][j] == 0) 
				cout << " \t";
			// ������ ���ڸ��� ������ ������ ����
			else if (puzzle[i][j] == i * 5 + j) 
				cout << "\033[1;36m" << puzzle[i][j] << "\033[0m\t";
			// �� �ۿ� �Ϲ����
			else 
				cout << puzzle[i][j] << "\t";

		}
		cout << endl << endl;
	}
}

// Ű���� �Է¹ޱ�
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
