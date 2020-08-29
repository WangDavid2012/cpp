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
T A<T>::a = 0;//类中的静态成员需要在类的外部进行初始化。

int main(void)
{
	//1 模板类通过二次编译根据调用的代码生成了两个不同的类A  一个是A<int> 一个A<char>
	A<int> a1, a2, a3;
	A<char> b1, b2, b3;


	A<int>::a = 20; //改变A<int>的静态成员
	A<char>::a = 'X';//改变A<char>的静态成员

	cout << "a1:a = " << a1.a << endl; //20
	cout << "b1:a = " << b1.a << endl;//'X'

	cout << "a2:a = " << a2.a << endl;
	cout << "a3:a = " << a3.a << endl;


	cout << "b2:a= " << b2.a << endl;//'X'
	cout << "b3:a = " << b3.a << endl;//'X'


	
	return 0;
}