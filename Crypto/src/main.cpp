#include <iostream>
using namespace std;

//���ã��������������Լ������������������Լ����1
// ������������
inline  int gcd(int a, int b)
{
	return b ? gcd(b, a%b) : a;
}
//��չŷ������㷨
int ext_gcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	int q = ext_gcd(b, a%b, y, x);
	y -= a / b*x;
	return q;
}

int main()
{
	int a = gcd(8, 34);
	int x = 0, y = 0;
	int r = ext_gcd(5, -288, x, y);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	system("pause");
}
