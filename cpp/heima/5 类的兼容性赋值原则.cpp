#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
���������Ե����������ʹ��
����������ֱ�Ӹ�ֵ���������
����������ֱ�ӳ�ʼ���������
����ָ�����ֱ��ָ���������
�������ÿ���ֱ�������������
*/

class Parent
{
public:
	void printP()
	{
		cout << "Parent::printP()..." << endl;
	}
	int a;
};

class Child :public Parent
{
public:
	void printC()
	{
		cout << "Child:: printC()...." << endl;
	}
	int b;
};

void print(Parent *p)
{
	p->printP();
}

int main(void)
{
	Child c;//�������
	c.printP(); //���������Ե����������ʹ��

	Parent p = c; // ��������ӵ��ȫ��������ڴ�ռ䣬�����ܹ����ϸ����ʼ��������
						 //����������ֱ�ӳ�ʼ��������� ��Ϊ�����ڴ�ռ���ݵĸ���ģ��ܹ���֤
						// ��ȫ��ֵ��
	//Child c2 = p;

	
	//����ָ�����ֱ��ָ���������
	//��������ܹ���ȫ���㸸��ָ����������Կ���  ����ָ�����ֱ��ָ���������
	Parent *pp = &c;  //pp->printP   (x ) pp->printC
	//pp->printC();
	pp->a;

	//����������ָ��ָ�������
	//����������㲻������ָ����������� ���Բ��ܹ� ����ָ��ָ�������
	//Child *cp = &p; // cp-> printP,  cp->printC
	//cp->b; //p��û��b���ڴ档 //��ʱ����b��Խ���ˡ�
	//cp->printP();
	//cp->printC();

	//�������ÿ��������������
	Parent &pr = c;

	//�������ò��������ø���Ķ���
	//Child &cr = p;

	print(&p); //Parent* p = &p;

	print(&c); //Parent *p = &c;

	//����ָ�����ָ��������� 

	return 0;
}