#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	void func(int a, int b)
	{
		cout << "Parent func " << endl;
	}
private:
	int a;
};

class Parent2
{
public:
	virtual void func(int a, int b)
	{
		cout << "Parent2 func " << endl;
	}
private:
	int a;
};

int main(void)
{
	Parent p1;
	Parent2 p2;

	cout << "sizeof(p1)" << sizeof(p1) << endl;
	cout << "sizeof(p2)" << sizeof(p2) << endl; //p2多出来的4个字节就是存放vptr指针的空间大小
																		//vptr指针我们访问不了，vptr指针指向的是Parent2类的虚函数表
																		//此表中目前有一个 虚函数 func(inta, intb)的入口地址。


	
	return 0;
}