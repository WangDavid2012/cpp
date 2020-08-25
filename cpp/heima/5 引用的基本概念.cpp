#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;



/*
1 引用没有定义,是一种关系型声明。声明它和原有某一变量(实体)的关
系。故 而类型与原类型保持一致,且不分配内存。与被引用的变量有相同的地
址。
2 声明的时候必须初始化,一经声明,不可变更。
3 可对引用,再次引用。多次引用的结果,是某一变量具有多个别名。
4 &符号前有数据类型时,是引用。其它皆为取地址。
*/

int printA(int &a) //引用作为函数参数的时候不需要初始化， 因为形参一定会被赋值的。
{
	cout << "a = " << a << endl;

	return 0;
}

int main(void)
{
	int a = 10;  //在内存上开辟4个字节， a就代表这个4个字节内存

	int *p = &a;  //让一个指针 指向这个4个字节的空间

	*p = 20;

	cout << "a = " << a << endl;

	//c++提供了另一种对 变量的间接操作的方式， 就是使用引用
	int & b = a; //定义一个引用b 指向a， b此时就是变量的a的别名
	//double &c = a;
	b = 40;

	cout << "a = " << &a << endl;
	cout << "b = " << b << endl;


	cout << "&a = " << &a << endl;
	cout << "&b =" << &b << endl;

	//int & c; //只是单纯定义一个引用， 不初始化，   引用一定要初始化


	int &bb = b; //对b引用再次 引用， 实际上是b的别名

	cout << "bb = " << bb << endl;
	cout << "&bb =" << &bb << endl;

	return 0;
}