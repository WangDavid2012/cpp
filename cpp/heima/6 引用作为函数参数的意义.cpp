#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

struct Teacher
{
	int id;
	char name[64];
};

void printT(Teacher t) //�ֲ���ʱ������  �ᷢ��ֵ����
{
	cout << "id = " << t.id << endl;
	cout << "name = " << t.name << endl;
	t.id = 100;
}

void printT2(Teacher *t) 
{
	cout << "id = " << t->id << endl;
	cout << "name = " << t->name << endl;
	t->id = 100;
}

void printT3(Teacher &t)//Teacher & t = t1;  t ����t1��һ������ 

//��������õ�ʱ��  �͵������ı�������⡣
{
	cout << "id = " << t.id << endl;
	cout << "name = " << t.name << endl;
	t.id = 1000;
}


//�������ɹ�
void my_swap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

void my_swap02(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void my_swap03(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main(void)
{
	Teacher t1 = {1, "zhang3"};

	printT(t1);

	cout << t1.id << endl;

	printT2(&t1);

	cout << t1.id << endl;


	printT3(t1); 
	cout << t1.id << endl;


	int a = 10;
	int b = 20;

	my_swap01(a, b);
	cout << "a = " << a << ", b = " << b << endl;

	my_swap02(&a, &b);
	cout << "a = " << a << ", b = " << b << endl;

	my_swap03(a, b);
	cout << "a = " << a << ", b = " << b << endl;


	return 0;
}