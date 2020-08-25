#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//定义一个函数
int func(int a, int b) {
	cout << "func 111 " << endl;

	return 0;
}


//定义一个函数指针
// C语言中 决定一个函数类型
// 返回值 参数列表

typedef int(FUNC)(int, int); //定义一个函数类型

typedef int(*FUNC_POINTER)(int, int); //定义一个函数指针类型


//如何将一个函数指针当成一个函数参数呢？
void my_function(FUNC *fp)
{
	fp(10, 20);
}

void my_function2(FUNC_POINTER fp)
{
	fp(10, 20);
}

//他是一个架构函数。 
void my_function3(int(*fp)(int, int))
{
	cout << "1999 年写的架构" << endl;
	cout << "固定业务1" << endl;
	fp(10, 20);
	cout << "固定业务2" << endl;
}


//2015 实现一个子函数
int my_new_function(int a, int b)
{
	cout << a << b << endl;
	cout << "2015年实现的新业务" << endl;

	return 0;
}

int main(void)
{
	FUNC * p = func;
	FUNC_POINTER p2 = func;
	int(*fp)(int, int) = func;

	p(10, 20);
	(*p)(10, 20); //以上两种写法等价

	p2(10, 20);
	(*p2)(20, 20);

	fp(10, 20);

	cout << " --------  " << endl;

	//2015   实现一个子函数，再调用1999的架构
	my_function3(my_new_function);
	
	return 0;
}