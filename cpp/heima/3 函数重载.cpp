#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//决定一个函数的  1 返回值， 2 参数列表

void func(int a)//void (*fp)(int)
{
	cout << "func1 " << endl;
	cout << a << endl;
}

//函数重载 是对一种函数的 添加的 意义， 对一个函数名  添加多中不同的实现  （+）
//函数重载， 就是对参数列表的 变换不是 函数返回值的变化
//返回值必须一样，参数列表不同， 并且函数名 相同的函数 都是重载函数
//void func(int a, int b = 10)
void func(int a, int b )
{
	cout << "func2" << endl;
	cout << a << "," <<b << endl;
}

//如果函数 完全相同 也不是一个函数重载
/*

void func(int a, int b)
{

}
*/


void func(int a, int b, char *str)
{
	cout << "func3" << endl;
	cout << a << ", " << b << ", " << str << endl;
}

//返回值类型不同，不能构成重载
/*
char func()
{

}
*/

void print(double a)
{
	cout << "print double " << endl;
	cout << a << endl;
}

void print(float a)
{
	cout <<"print float" <<endl;
	cout <<a <<endl;
}


#if 0
void print(int a)
{
	cout << "print int" << endl;
	cout << a << endl;
}

void print(char a)
{
	cout << "print char" << endl;
	cout << a << endl;
}
#endif




int main(void)
{
	//定义一个 指向void func(int a)的函数指针
	//void(*fp)(int) = func;//fp 就是执行 void()(int) 这种函数类型的指针

	//fp(10);


	func(10); //编译器 会根据用户传递的参数类型和个数 进行重载函数的匹配
	//如果说函数重载 加上了默认参数， 回导致调用函数的时候出现二义性，
	//记住：  函数重载 最好不要有默认参数，
	func(10, 20);
	func(10, 20, "abc");


	//print(10); //void print(int a)
	//print(1.1);//void print(double a)

	//print(1.1f); // 经过隐式转换 会调用void print(double a)
	//print('a'); //经过隐式转化， 'a' ->int   void print(int a)

	//print("asbdasd");

	//1 严格进行参数列表匹配
	//2 如果隐式转换可以找到匹配 那么依然可以调用
	//3 如果匹配不到， 直接报错。


	
	
	return 0;
}