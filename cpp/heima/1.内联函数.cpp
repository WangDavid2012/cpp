#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//inline ��һ���ؼ��֣�����˺��������������� ���ں�������ֵ��ǰ��
#define MY_MAX(a, b) ((a) < (b)? (a):(b))

inline int   my_func(int a, int b)
{
	return (a < b ? a : b);
}

inline void printAB(int a, int b);

int main(void)
{
	int a = 10;
	int b = 20;

	//1 �������� �ڵ��õ�ʱ�򣬲�����ͨ������ѹջ �ͳ�ջ�Ŀ���
	//2 �������� �����ǰ���ͨ������ѹվ�ͳ�ջ����ʡȥ�ˣ� ���еı������ʷ�������У�� ���� �������б����������
	  // ���꺯��������Ԥ����������ģ�û���뺯��һ����У��
	//my_func(a, b);
	{
		return (a < b ? a : b);
	}
	//printAB(a, b);
	{
		cout << "a = " << a << ", b = " << b << endl;
	}

	MY_MAX(a++, b);
	(a++) < (b) ? (a++) : (b);
	my_func(a++, b);

	//MY_MAX("adsad", "dasdas");
	//my_func("adsad", "dasdsa");

	
	
	return 0;
}

//�����������д�� inline �ؼ���  ���� ��������û��дinline ��������Ȼ���ᵱinline��������
void printAB(int a, int b)
{
	cout << "a = " << a << ", b = " << b << endl;
}