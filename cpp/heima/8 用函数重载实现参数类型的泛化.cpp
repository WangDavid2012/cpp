#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


//是int 型的两个数的交换
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


//对char 类型进行交换
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

	cout << "交换之前" << endl;
	print(a, b);
	mySwap(a, b);
	cout << "交换之后" << endl;
	print(a, b);


	char x = 'x';
	char y = 'y';
	cout << "交换之前" << endl;
	print(x, y);
	mySwap(x, y);
	cout << "交换之后" << endl;
	print(x, y);

	return 0;
}