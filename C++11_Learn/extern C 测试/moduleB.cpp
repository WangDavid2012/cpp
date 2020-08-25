//moduleB实现文件 moduleB.cpp //B模块的实现也没有改变，只是头文件的设计变化了


#include <iostream>
#include "moduleB.h"
using namespace std;


int main()
{
	cout << fun(2, 3) << endl;
	getchar();
}