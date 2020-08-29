#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//模板就是 对数据类型的 参数化

//此时编译器不知道T是个什么东东， 告诉编译器T是一个类型的泛化
//template <typename T> //告诉编译器 T是一个泛化类型
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

	cout << "交换之前" << endl;
	//<>在调用模板函数的时候，要告诉编译器T泛化的类型的 具体到底是什么类型
	print<int>(a, b);
	mySwap<int>(a, b);
	cout << "交换之后" << endl;
	print<int>(a, b);

	char x = 'x';
	char y = 'y';

	cout << "交换之前" << endl;
	print<char>(x, y);
	mySwap<char>(x, y);
	cout << "交换之后" << endl;
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