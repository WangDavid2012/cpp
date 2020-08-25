#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

void func(int a, int b)
{
	cout << a << b << endl;
}

void func(int a, int b, int c)
{
	cout << a << b << c << endl;
}


void func(int a, int b, int c, int d)
{
	cout << a << b << c <<d << endl;
}

//1 定义一个函数类型
typedef void(myfunctype)(int, int); //定义了一个函数类型， 返回值void 参数列表是 int，int   ,, void()(int,int)

//2 定义一个函数指针类型 
typedef void(*myfunctype_pointer)(int, int); //定义了一个函数指针类型， 返回值void 参数列表是 int，int   ,, void(*)(int,int)

int main(void)
{
	//1  定义一个函数指针
	myfunctype * fp1 = NULL;

	fp1 = func;

	fp1(10, 20);


	// 2 定义一个函数指针
	myfunctype_pointer fp2 = NULL;
	fp2 = func;
	fp2(10, 20);

	//3 直接定义一个函数指针
	void(*fp3)(int, int) = NULL;

	fp3 = func;

	fp3(10, 20);

	cout << " -----------------" << endl;

	//此时的fp3 是 void(*)(int,int)
	//fp3(10, 30, 30); //fp3 恒定指向一个 函数入口，void func(int, int) 的函数入口
	//fp3(10, 30, 40, 50); //想要通过函数指针，发生函数重载 是不可能。
	fp3(10, 20);

	void(*fp4)(int, int, int) = func; //在堆函数指针赋值的时候，函数指针会根据自己的类型 找到一个重载函数

	fp4(10, 10, 10);
	//fp4(10, 10, 10, 10);
	//函数指针，调用的时候是不能够发生函数重载的。

	void(*fp5)(int, int, int, int) = func;// void func(int ,int ,int ,int )
	fp5(10, 10, 10, 10);
	
	return 0;
}