#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	static int s;

private:	

};

int A::s = 0;//��̬��Ա����Ҫ������ⲿ��ʼ��

class B :public A
{
public:
private:
};

int main(void)
{
	B b;
	cout << b.s << endl;
	b.s = 100;
	cout << b.s << endl;
	
	cout << A::s << endl;
	
	return 0;
}