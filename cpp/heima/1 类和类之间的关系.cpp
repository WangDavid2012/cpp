#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	void funcA()
	{
		cout << "func A ..." << endl;
	}
};


//A����B�� �ǳ䵱һ����Ա������ B has A   ������ϵ A ����B
class B
{
public:
	void funcB()
	{
		a.funcA();
	}
	A a;
};


//���C��ĳһ����Ա���� ��������A���βΣ� ��A�൱һ���βδ��ݽ���
//C use A
class C
{
public:
	void funcC(A *a)
	{
		a->funcA();
	}
};


//��D  �̳��� ��A
//��D  �̳���A  ��˵��  D is A
class D : public A
{
public:
	void funcD()
	{
		funcA(); //ֱ��ʹ��A��ķ�����
	}
};

int main(void)
{
	D d;
	d.funcA();
	
	return 0;
}