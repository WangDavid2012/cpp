#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//const引用一般用在形参上，来限制  被引用的变量不能被修改，
void printX(const int & re )
{
	cout << "re " << re << endl;
}

int main(void)
{
	const int a = 10; // a必须初始化
	//int & b = a;
	const int &b = a;

	//如果是一个const 常量， 必须用const 引用来接收它
	int x = 3.14;
	const int &re1 = x;


	cout << "re1 " << re1 << endl;
	x = 20;
	cout << "re1 " << re1 << ", x: " << x << endl;


	const int &re2 = 10;// 用const 引用 引用一个字面量
									// 当用一个const 引用  去引用一个字面量的时候， 字面量他是没有地址，
									//引用是无法 对字面量取地址的， 临时创建一个 int temp， 10 --->temp
									//const int &re2 = temp;
									//用re2 就是代表 temp，re2是const的引用，你无法去改变temp的值
	//int &re2 = 10;         //非常量引用 必须是左值。 左值就是可以放在=左边的表达式，左值是可以赋值，是有内存空间的
									//如果想对一个字面量做引用的话，只能用 const 的引用

	cout << "re2 = " << re2 << endl;

	cout << "sizeof(re2)" << sizeof(re2) << endl;

	return 0;
}