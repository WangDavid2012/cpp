#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


template <class T>
class A
{
public:
	T value;
	static T a;
};

template <class T>
T A<T>::a = 0;//���еľ�̬��Ա��Ҫ������ⲿ���г�ʼ����

int main(void)
{
	//1 ģ����ͨ�����α�����ݵ��õĴ���������������ͬ����A  һ����A<int> һ��A<char>
	A<int> a1, a2, a3;
	A<char> b1, b2, b3;


	A<int>::a = 20; //�ı�A<int>�ľ�̬��Ա
	A<char>::a = 'X';//�ı�A<char>�ľ�̬��Ա

	cout << "a1:a = " << a1.a << endl; //20
	cout << "b1:a = " << b1.a << endl;//'X'

	cout << "a2:a = " << a2.a << endl;
	cout << "a3:a = " << a3.a << endl;


	cout << "b2:a= " << b2.a << endl;//'X'
	cout << "b3:a = " << b3.a << endl;//'X'


	
	return 0;
}