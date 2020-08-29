#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	void funcA()
	{
		cout << "func A ..." << endl;
	}
};


//A对于B类 是充当一个成员变量， B has A   包含关系 A 属于B
class B
{
public:
	void funcB()
	{
		a.funcA();
	}
	A a;
};


//如果C中某一个成员函数 是依赖于A类形参， 将A类当一个形参传递进来
//C use A
class C
{
public:
	void funcC(A *a)
	{
		a->funcA();
	}
};


//类D  继承于 类A
//类D  继承于A  就说明  D is A
class D : public A
{
public:
	void funcD()
	{
		funcA(); //直接使用A类的方法。
	}
};

int main(void)
{
	D d;
	d.funcA();
	
	return 0;
}