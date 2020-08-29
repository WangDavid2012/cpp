
#include <iostream>

using namespace std;
//第一次编译 c++编译器对模板函数，进行词法分析
//如果语法分析没有任何问题


template <typename T>
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

/*
//通过编译器的第二次比编译给我们生成两个模板函数的重载
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


//通过汇编，我们可以看到编译器只给我们生成了int 和char 的模板函数的实现体 并没有生成去哪不的类型的实现体
int main(void)
{
	int a = 10;
	int b = 20;

	//第二次编译 根据模板函数的调用来生成具体的模板
	//而不是所有数据类型都生成
	mySwap<int>(a, b);
	cout << "a = " << a << ", b = " << b << endl;

	char x = 'x';
	char y = 'y';

	mySwap<char>(x, y);
	cout << "x = " << x << ", y = " << y << endl;


	return 0;
}