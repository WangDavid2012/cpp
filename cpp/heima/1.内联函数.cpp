#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//inline 是一个关键字，代表此函数是内联函数， 放在函数返回值的前面
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

	//1 内联函数 在调用的时候，不想普通函数有压栈 和出栈的开销
	//2 内联函数 仅仅是把普通函数的压站和出栈开销省去了， 所有的编译器词法分析和校验 都有 ，他是有编译器处理的
	  // 而宏函数，是由预处理器处理的，没有想函数一样的校验
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

//如果函数声明写了 inline 关键字  但是 函数定义没有写inline 编译器依然不会当inline函数处理
void printAB(int a, int b)
{
	cout << "a = " << a << ", b = " << b << endl;
}