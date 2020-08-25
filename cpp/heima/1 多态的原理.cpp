#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	virtual void func(int a, int b)
	{
		cout << "Parent: func(inta ,int b) ..." << endl;
	}

	void func(int a, int b, int c)
	{
		cout<< "Parent: func(int a, int b , int c" << endl;
	}
private:
	int a;
};


class Child :public Parent
{
public:
	virtual void func(int a, int b)
	{
		cout << "Child :func( int a , int b )..." << endl;
	}


private:
	int b;
};

int main(void)
{
	Parent *p = new Child; //父类指针指向了 子类对象

	p->func(10, 20); //此时发生了多态

	//编译器会 通过p指针， 找到p指针所指向内存块的vptr指针，根据vptr指针在去找匹配的函数

	p->func(10, 20, 30); //这是 静态联编
	p->func(10, 20);     //动态联编


	return 0;
}