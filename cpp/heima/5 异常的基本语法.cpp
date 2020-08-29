#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//是一个能够抛出异常的函数
void divide(int x, int y)
{
	if (y == 0) {
		//出现了算术的非法
		cout << "发现y == 0" << endl;
		throw 0; //throw divide就退出了， return
	}

	cout << "x/y = " << x / y << endl;
}

void use_divide(int x, int y)
{
	try {
		divide(x, y);
	}
	catch (...) {
		cout << "use_divide 捕获到未知异常，向上抛" << endl;
		throw ; //中间层函数，捕获到异常，不做最终处理，直接向上抛
	}
}
//1 异常的捕获是严格按照类型匹配
//2 异常可以不做处理 继续向上抛，中间层可以不需要处理，用一个统一处理异常的函数统一处理。
//3 如果说异常一直向上抛， 没有函数处理， 最终操作系统会将正常错误处理

int main(void)
{
	try {
		use_divide(10, 0);
	}
	catch (int e)
	{
		cout << "捕获到了异常 e = " << e << endl;
	}
	catch (char e)
	{
		cout << "捕获到了异常 e = " << e << endl;
		throw e;
	}
	catch (...)//能够捕获任意类型的异常
	{
		cout << "捕获到未知异常" << endl;
	}
	
	return 0;
}