#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

void func(int a, int b)
{
	cout << a << b << endl;
}

void func(int a, int b, int c)
{
	cout << a << b << c << endl;
}


void func(int a, int b, int c, int d)
{
	cout << a << b << c <<d << endl;
}

//1 ����һ����������
typedef void(myfunctype)(int, int); //������һ���������ͣ� ����ֵvoid �����б��� int��int   ,, void()(int,int)

//2 ����һ������ָ������ 
typedef void(*myfunctype_pointer)(int, int); //������һ������ָ�����ͣ� ����ֵvoid �����б��� int��int   ,, void(*)(int,int)

int main(void)
{
	//1  ����һ������ָ��
	myfunctype * fp1 = NULL;

	fp1 = func;

	fp1(10, 20);


	// 2 ����һ������ָ��
	myfunctype_pointer fp2 = NULL;
	fp2 = func;
	fp2(10, 20);

	//3 ֱ�Ӷ���һ������ָ��
	void(*fp3)(int, int) = NULL;

	fp3 = func;

	fp3(10, 20);

	cout << " -----------------" << endl;

	//��ʱ��fp3 �� void(*)(int,int)
	//fp3(10, 30, 30); //fp3 �㶨ָ��һ�� ������ڣ�void func(int, int) �ĺ������
	//fp3(10, 30, 40, 50); //��Ҫͨ������ָ�룬������������ �ǲ����ܡ�
	fp3(10, 20);

	void(*fp4)(int, int, int) = func; //�ڶѺ���ָ�븳ֵ��ʱ�򣬺���ָ�������Լ������� �ҵ�һ�����غ���

	fp4(10, 10, 10);
	//fp4(10, 10, 10, 10);
	//����ָ�룬���õ�ʱ���ǲ��ܹ������������صġ�

	void(*fp5)(int, int, int, int) = func;// void func(int ,int ,int ,int )
	fp5(10, 10, 10, 10);
	
	return 0;
}