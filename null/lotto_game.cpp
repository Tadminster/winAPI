#include <iostream>
#include <time.h>
#include <string>

using namespace std;

void lotto();
int playerInput();
bool duplication(int[], int, int&);
void bubbleSort(int[], int);
int lottoScore(int[], int[]);

int main()
{
	cout << "[??] [??] [??] [??] [??] [??]" << endl;

	int first = true;
	bool bContinue = true;
	while (bContinue)
	{
		cout << endl;

		cout << "�ζ� ��ȣ ������" << endl;
		cout << "(ġƮ) 8, 13, 19, 27, 40, 45" << endl;

		
		int pInput{ playerInput() };
		if (pInput == 1) 
		{
			system("cls");
			lotto();
		}
		else bContinue = false;
	}


}

/* �ζ� ��ȣ ���� */
void lotto()
{
	// ������(1057ȸ��) �ζǹ�ȣ
	int lastWeekNum[6] = { 8, 13, 19, 27, 40, 45 };

	// �����õ� �ʱ�ȭ
	srand(time(0));

	int myNum[6] = {};
	int cnt{ 6 }, i{ 0 }, dup{ 0 };
	while (cnt > 0)
	{
		
		int x = rand() % 45 + 1;
		if (duplication(myNum, x, dup))
		{
			continue; 
		}
		else
		{
			myNum[i++] = x;
			cnt--;
		}
	}

	bubbleSort(myNum, 6);
	int score = lottoScore(myNum,lastWeekNum);

	// �ζ� ��ȣ ���
	for (int n : myNum)
		if (n < 10) cout << "[ " << n << "] ";
		else cout << "[" << n << "] ";
	cout << " �ߺ�����: " << dup;
	cout << ", ��������: " << score;


	cout << endl;
}

/* �޴� �Է� */
int playerInput()
{
	string sInput;
	int iInput;

	while (1)
	{
		cout << "[1]�̱� [2]�����ϱ�, ��ȣ�� �����ϼ���: ";
		cin >> sInput;
		if (sInput == "1" || sInput == "2")
		{
			iInput = stoi(sInput);
			break;
		}
		else cout << "�ùٸ� ��ȣ�� �Է��ϼ���." << endl;
	}
	
	return iInput;
}

bool duplication(int arr[], int x, int &dup)
{
	bool bDup = false;
	for (int j = 0; j < 6; j++)
	{
		if (arr[j] == x)
		{
			bDup = true;
			dup++;
			break;
		}
	}
	
	return bDup;
}

void bubbleSort(int arr[], int n) 
{
for (int i = 0; i < n - 1; i++) 
		for (int j = 0; j < n - i - 1; j++) 
			if (arr[j] > arr[j + 1]) 
				swap(arr[j], arr[j + 1]);
}

int lottoScore(int myNum[], int lastWeekNum[])
{
	int score{ 0 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			if (lastWeekNum[i] == myNum[j]) score++;

	return score;
}