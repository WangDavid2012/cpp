#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


void func(const char *p) //p��ָ����ڴ������ܹ��޸�
{
	char *pp = const_cast<char *>(p);//��p��const ����ȥ��
	//char *pp = (char*)p;
	pp[0] = 'A';
}

int main(void)
{
	const char *p = "12345677"; // pָ����ǳ�����
	char buf[] = "12343242377";

	
	func(buf);//2
	//func(p);//1
	//cout << "p:" << p << endl;
	cout << "buf:" << buf << endl;

	const int a = 10;//a ����һ����������һ��10�ķ���
	const int *a_p = &a; //��ʱ������һ���ռ䣬��10�Ž�ȥ�� ��a_pָ������ռ�
	int *a_p1 = const_cast<int*>(a_p); //��a_p��const ����ȥ��
	*a_p1 = 100;

	int *p2 = const_cast<int*>(&a);
	*p2 = 200;

	cout << "*a_p = " << *a_p << endl;
	cout << "a= " << a << endl;
	cout << "*p2 " << *p2 << endl;

	//const_cast �����þ��� ��һ����ֻ�����Ե�ָ�룬��ֻ������ȥ��������ǰ���ǵ�ǰ���ڴ�ռ��ǿ����޸ġ�
	
	return 0;
}