#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	Parent(int a)
	{
		this->a = a;
	}

	int a;
};

class Child :public Parent
{
public :
	Child(int a, int aa) : Parent(aa)
	{
		this->a = a; //��Child ��a  = a�� �ø��׵�a = aa
	}

	void print()
	{
		cout << "a = " << a << endl; //Ĭ����ʹ�� ��ǰ��������ı���
		cout << "Parent::a = " << Parent::a << endl;  //�������ʸ����е��������� ��Ҫ���ϸ����������
	} 

	int a;
	/*
	  a ---> Paretn::a
	*/
};

int main(void)
{
	Child c(10, 100);

	c.print();
	
	return 0;
}