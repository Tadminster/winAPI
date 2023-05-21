#include <iostream>
#include <time.h> //time func.h
#include <string> //stoi func.h
using namespace std;

void baseball();
int playerInput();
int catcherS(int[], int[]);
int catcherB(int[], int[], int);
int inputRE();

int main()
{
	cout << "���� �߱� ����" << endl;

	bool bContinue = true;
	while (bContinue)
	{ 
		// Main Game
		baseball();

		// Restart?
		int iContinue{ inputRE() };

		cout << endl;
		if (iContinue == 1)
		{
			system("cls");
			continue;
		}
		else bContinue = false;
	}
}

void baseball()
{
	//
	int cnt{ 0 }, ball{ 0 }, strike{ 0 };

	// random seed initialize
	srand(time(0));

	// Create an array & initialize it to 0
	int arr[3] = {};

	// arr[index]
	int index{ 0 };
	while (arr[2] == 0)
	{
		// Create random Number
		int num = rand() % 9 + 1;
		// for duplicate checking
		bool dup = false;

		// duplicate checking
		for (int i = 0; i < 3; i++)
			if (num == arr[i]) dup = true;

		// If no duplicates, assign a value to the array 
		if (!dup) arr[index++] = num;
	}

	// Random number output
	cout << "ġƮ: ";
	for (int n : arr)
	{
		cout << n;
	}

	cout << endl;


	do 
	{	
		cout << endl;
		
		// Input
		int input = playerInput();
		int inputs[3] = { input / 100, input % 100 / 10, input % 10 };

		/*
		int x = input / 100,
			y = input % 100 / 10,
			z = input % 10;
		*/

		strike = catcherS(inputs, arr);
		ball = catcherB(inputs, arr, strike);

		cout << "�õ�Ƚ��: " << cnt << ", �̹� ���� ���: " << strike << "S " << ball << "B" << endl;
		cnt++;

	} while (!(strike == 3));


	cout << endl;
	cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "�����մϴ�! '" << cnt << "'�� ���� ��� ���ڸ� ������ϴ�." << endl;
	cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << endl;
}

/* Player input */
int playerInput()
{
	string str;
	int input{0};
	while (1)
	{
		cout << "�ߺ����� ���ӵǴ� �� 3���� �Է��ϼ���: ";
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
		if ( input < 100 || input > 999) cout << "[ERROR] '��'�� �۰ų� Ů�ϴ�." << endl;
		else
		{
			int x = input / 100,
				y = input % 100 / 10,
				z = input % 10;
			// 0 checking
			if (y == 0 || z == 0) cout << "[ERROR] '0'�� �ֽ��ϴ�." << endl;
			// duplicate checking
			else if (x != y && x != z && y != z) break;
			else cout << "[ERROR] '�ߺ��Ǵ� ����'�� �ֽ��ϴ�." << endl;
		}
			cout << endl;
	}

	return input;
}

/* Scoring Strikes */
int catcherS(int inputs[], int arr[])
{
	int score{ 0 };

	for (int i = 0; i < 3; i++)
	{
		//cout << "inputs[i]= " << inputs[i] << ", arr[i]= " << arr[i] << endl;
		if (inputs[i] == arr[i]) score++;
	}

	return score;
}

/* Scoring Ball */
int catcherB(int inputs[], int arr[], int strike)
{
	int score{ 0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//cout << "inputs[i]= " << inputs[i] << ", arr[i]= " << arr[i] << endl;
			if (inputs[i] == arr[j]) score++;
		}
	}

	return score - strike;
}

/* Inputs .. to game restarts */
int inputRE()
{
	int x;

	while (1)
	{
		cout << "[1]�����ϱ� [2]�׸��ϱ�, �� ������ ���� �Ͻðڽ��ϱ�? ";
		string str;
		cin >> str;

		if (str == "1" || str == "2")
		{
			x = stoi(str);
			break;
		}
		else
			cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���. " << endl;
	}

	return x;
}