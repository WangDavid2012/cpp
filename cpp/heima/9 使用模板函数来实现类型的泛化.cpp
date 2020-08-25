#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//ģ����� ���������͵� ������

//��ʱ��������֪��T�Ǹ�ʲô������ ���߱�����T��һ�����͵ķ���
//template <typename T> //���߱����� T��һ����������
template<class T>
void mySwap(T &a, T &b);

template<typename T>
void print(T &a, T &b)
{
	cout << a << ",   " << b << endl;
}

int main(void)
{
	int a = 10;
	int b = 20;

	cout << "����֮ǰ" << endl;
	//<>�ڵ���ģ�庯����ʱ��Ҫ���߱�����T���������͵� ���嵽����ʲô����
	print<int>(a, b);
	mySwap<int>(a, b);
	cout << "����֮��" << endl;
	print<int>(a, b);

	char x = 'x';
	char y = 'y';

	cout << "����֮ǰ" << endl;
	print<char>(x, y);
	mySwap<char>(x, y);
	cout << "����֮��" << endl;
	print<char>(x, y);

	double ff1 = 20.0;
	double ff2 = 30.0;

	mySwap<double>(ff1, ff2);
	
	return 0;
}

template <typename T>
void mySwap( T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}