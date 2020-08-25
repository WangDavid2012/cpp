
#include <iostream>

using namespace std;
//��һ�α��� c++��������ģ�庯�������дʷ�����
//����﷨����û���κ�����


template <typename T>
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

/*
//ͨ���������ĵڶ��αȱ����������������ģ�庯��������
void mySwap(int &a, int &a)
{
int temp = a;
a = b;
b =temp;
}

void mySwap(char &a, char &b)
{
char temp = a;
a= b;
b = temp;
}
*/


//ͨ����࣬���ǿ��Կ���������ֻ������������int ��char ��ģ�庯����ʵ���� ��û������ȥ�Ĳ������͵�ʵ����
int main(void)
{
	int a = 10;
	int b = 20;

	//�ڶ��α��� ����ģ�庯���ĵ��������ɾ����ģ��
	//�����������������Ͷ�����
	mySwap<int>(a, b);
	cout << "a = " << a << ", b = " << b << endl;

	char x = 'x';
	char y = 'y';

	mySwap<char>(x, y);
	cout << "x = " << x << ", y = " << y << endl;


	return 0;
}