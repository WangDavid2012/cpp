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
	virtual void print() //��һ����Ա���� ����Ϊ �麯����
	{
		cout << "Parent ::print() : a = " << a << endl;
	}
private:
	int a;
};


class Child :public Parent
{
public:
	Child(int a, int b) :Parent(a)
	{
		this->b = b;
	}

	//�ض��常�ຯ���� ����������͸���֮��
	//��������д����ĳ�Ա���������������������������麯���� �Ǻ������ض���
	//���������д����ĳ�Ա������ ��������е���������� �麯���� ���Ǻ�������д��
	virtual void print()
	{
		cout << "Child: print b:" << b << endl;
		//Parent::print();
	}
private:
	int b;
};

//2015
/*
class Child2 :public Parent
{
public:

	virtual void print(){
		cout << "CHild 3 Print().." << endl;
	}
private:
};
*/

//1999 �������ö�̬������������δ��д�Ķ���ķ�����

void myPrintFunc(Parent *p) //  �ø���ָ��ָ����������ʱ��
{
	p->print();// �ٴ�ʱ print���� �����˶�̬����
}

int main(void)
{
	Child c(10, 20);
	c.print(); //���õ������print

	Parent p(100);
	p.print(); //���õĸ����print

	cout << "  -----  " << endl;
	myPrintFunc(&p); //ϣ�����ø����print

	cout << " ------  " << endl;
	myPrintFunc(&c); //ϣ�����������print  //Parent* p = &c;  ����ָ��ָ���������
								//������ �� �����㴫�ݽ������Ǹ��������������� ���������ø��ࡣ
								//����������һ����ȫ�ľٴ룬 ��ʹ�㴫��������
								//������Ҳ��Ϊ ���ø����print �ǰ�ȫ�����ܹ���֤�����print������һ�����ڵġ�
								//û��ð��ȥ���������print
	//Child2 c2;
	//myPrintFunc(&c2);
	
	return 0;
}