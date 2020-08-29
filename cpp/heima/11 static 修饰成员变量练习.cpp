#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Box
{
public:
	Box(int l, int w) :length(l), width(w) {}

	int volumu()
	{
		return length * width *height;
	}

	int length;//4
	int width;//4
	static int height; //声明一个静态的成员变量 //4
};

//在外部初始化
int  Box::height = 100;

int main(void)
{
	Box b1(10, 20);
	Box b2(30, 40);

	cout << "b1: " << b1.volumu() <<", " <<b1.height << endl;
	cout << "b2: " << b2.volumu() <<"," << b2.height << endl;
	Box::height;

	cout << "sizeof(b1) :" << sizeof(b1) << endl; //8
	cout << "sizeof(b2) :" << sizeof(b2) << endl; //8  说明static修饰的成员变量并不属于对象中， 而是在全局区开辟的。


	return 0;
}