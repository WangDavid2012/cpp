#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	virtual void func(int a, int b)
	{
		cout << "Parent: func(inta ,int b) ..." << endl;
	}

	void func(int a, int b, int c)
	{
		cout<< "Parent: func(int a, int b , int c" << endl;
	}
private:
	int a;
};


class Child :public Parent
{
public:
	virtual void func(int a, int b)
	{
		cout << "Child :func( int a , int b )..." << endl;
	}


private:
	int b;
};

int main(void)
{
	Parent *p = new Child; //����ָ��ָ���� �������

	p->func(10, 20); //��ʱ�����˶�̬

	//�������� ͨ��pָ�룬 �ҵ�pָ����ָ���ڴ���vptrָ�룬����vptrָ����ȥ��ƥ��ĺ���

	p->func(10, 20, 30); //���� ��̬����
	p->func(10, 20);     //��̬����


	return 0;
}