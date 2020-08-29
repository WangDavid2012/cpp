#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Complext.h"
#include "Complext.hpp" //不能够引入cpp
#include <vector>

//模板类的 方法的实现不能够用多文件编写。
//如果实现多文件的 由于二次编译 真正的实现体是在cpp文件定义的。需要引入cpp头文件。

using namespace std;



int main(void)
{
	
	Complex<int> c1(10, 20);
	c1.pirntComplex();

	Complex<int> c2(1, 2);

	Complex<int> c3; //调用无参构造
	c3 = c1 + c2;

	c3.pirntComplex();

	return 0;
}