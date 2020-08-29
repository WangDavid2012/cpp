#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


// c++中 允许给一个形参 默认设置为一个值, 当外部调用函数的时候，如果不传递参数的，那么x就是100
//如果外部传递实参，那么x的值就是实参的值
int func1(int x , int = 0)
{
	cout << "func1: x = " << x << endl;

	return 0;
}


//求一个 立方体的体积
//默认参数，必须是从右向左设置， 只有有一个参数是带有默认参数 的，那么他右边的所有参数都必须有默认值。
int volume(int len , int width, int high= 30)
{
	return len *width * high;
}

int main(void)
{
	int x = 10;
	int v = 0;

	func1(x);

	int len = 10;
	int w = 20;
	int h = 30;

	//v = volume(len, w, h);
	v = volume(len, w,h);

	cout << "v = " << v << endl;
	
	return 0;
}