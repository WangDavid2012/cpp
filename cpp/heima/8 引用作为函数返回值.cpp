#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

int getA1()
{
	int a = 10;
	return a;
} //value_a = a; 

int &getA2()
{
	int a = 10;
	return a;
} //���������� int & = a;  //  int &temp = &a;

int &getBB()
{
	static int b = 100;
	return b;
}

int main(void)
{
	int value_a = 0;

	value_a = getA1();   //��ȷ

	cout << "value_a " << value_a << endl;


	value_a = getA2();// int value_a = temp;   // int value_a = *temp; //����һ��ֵ����
	cout << "value_a " << value_a << endl;
	cout << "value_a " << value_a << endl;


	int &r_a = getA2(); //û��ֵ��������  ����ֹ
	//����������ֵ����һ���ֲ����������õ�ʱ�򣬲����������������ա�
	cout << "r_a  " << r_a << endl;
	cout << "r_a  " << r_a << endl;


	int &r_b = getBB(); //��ʱ��r_b ���� getBB�е� static int b
	//����������ֵ�������Ӻ����ڲ��ֲ��������Ϳ��������ý��н��գ�
	cout << "r_b " << r_b << endl;
	cout << "r_b " << r_b << endl;

	r_b = 2000; //��ʱr_b ����getBB�е�b�ı����� �޸�r_b �����޸� b

	int value_b = getBB();  // ����һ����ʱ������ int &temp = b;  value_b = *temp; //������ֵ����
	//getBB();//getBB ����b�ı���
	//int value_b = *(getBB());
	//int value_b = static b;
	cout << "value_b " << value_b << endl;

	getBB() = 3000; //static b  = 3000; //��������Ϊ�����ķ���ֵ��ʱ��ֻҪ��������ǺϷ��ģ��Ϳ��Ե���ֵ��


	//��Ŀ�����
	int a = 10;
	int b = 20;

	(a < b ? a : b) = 30;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	return 0;
}