#include <iostream>
#include <string>
#include <time.h>
using namespace std;

void random();

int main()
{
	random();
}

void random()
{
	int n{ 10 };
	int x;
	srand(time(0));

	while (n > 0)
	{
		x = rand();
		cout << x << endl;
		n--;
	}
}