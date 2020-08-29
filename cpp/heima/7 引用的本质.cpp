#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


struct TypeA
{
	int *a;
};

struct TypeB
{
	double &a;
};

struct Teacher
{
	int id;
	char name[64];
};


void motifyTeacher(Teacher &t) //
{
	t.id = 100; // ���˵t��һ����ָ�룬 *t ����ָ��ָ���ڴ�ռ�  (*t).id = 100
	//����Ҫ��ͼ�޸Ļ��߻�ȡ�Ѿ���ʼ�������õ�ʱ�� ����������һ�����ص�*�Ĳ���
}

void motifyA(int *const a)   //��ָ�� Ҳ��һ�������� Ҳ�Ǳ���Ҫ��ʼ����  Ҳ���ܱ��޸�
{
	*a = 100;
}

void motifyB(int &a)
{
	a = 1000; //a ʵ������һ������ָ�룬 ����������һ��a��ֵ������������һ�����εĲ����� *
}

//���о����õ�ʱ�� �����Խ��������Ϊ һ�� ��ָ��
//��������õ�ʱ�� ���Խ��������Ϊ һ�������ı���

void test()
{
	int value = 20;
	Teacher t1 = { 1, "zhangsan" };

	motifyA(&value);

	cout << "value = " << value << endl;

	motifyB(value);  // int value --> int &a  , int& a = value ������ָ��ָ���ĸ�������ʱ�� �������ṩ������һ�����εĲ���
						// a = &value;

	cout << "value = " << value << endl;

	motifyTeacher(t1);  //���˵ motifyTeacher ���β���һ����ָ�룬Teacher *const t = &t1;
								//���������� Teacher &t �β���һ�����ã� Teacher &t = &t1;
								//�������ó�ʼ����ʱ�� ����һ��&  �����β���
}


void motifyAA(int *a)
{
	*a = 100;   //��ӵĸ�ֵ
}

void motifyBB(int &a) //int &a = a;    a = &a;
{
	a = 200; //*a = 200
}

void test2()
{
	int a = 10; //����һ


	motifyAA(&a); //int*a = &a; //�����˹���

	motifyBB(a);
}


int main(void)
{
	int a = 10;
	int b = 20;

	const int c_a = 10;

	//c_a = 20;//�����ڳ�ʼ��֮�󣬲��ܹ����޸���

	int &re = a; //���ñ����ʼ��.  �����ڳ�ʼ��֮��Ҳ���ܹ����ı�
	re = b; // a = b ������ ��re����ָ��b

	cout << "re = " << re << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	re = 100; //�Ǹõ�a ����b��

	cout << "re = " << re << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	//1 ���� ������һ�� ������

	cout << "sizeof(TypeA): " << sizeof(TypeA) << endl;
	cout << "sizeof(TypeB):" << sizeof(TypeB) << endl;

	//ͨ�����������С�� ���ֲ���������ʲô���� ����4���ֽڣ�����ָ��Ĵ�Сһ����

	//2 ���ÿ�����һ�� ָ�룿


	test();
	
	return 0;
}