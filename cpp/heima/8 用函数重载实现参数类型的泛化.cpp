#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


//��int �͵��������Ľ���
void mySwap(int & a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void print(int &a, int &b)
{
	cout << "a = " << a << ", b = " << b << endl;
}


//��char ���ͽ��н���
void mySwap(char & a, char & b)
{
	char temp = a;
	a = b;
	b = temp;
}

void print(char &x, char &y)
{
	cout << "x = " << x << ", y = " << y << endl;
}

int main(void)
{
	int a = 10;
	int b = 20;

	cout << "����֮ǰ" << endl;
	print(a, b);
	mySwap(a, b);
	cout << "����֮��" << endl;
	print(a, b);


	char x = 'x';
	char y = 'y';
	cout << "����֮ǰ" << endl;
	print(x, y);
	mySwap(x, y);
	cout << "����֮��" << endl;
	print(x, y);

	return 0;
}