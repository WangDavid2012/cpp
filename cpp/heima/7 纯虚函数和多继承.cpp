#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//抽象类1
class Interface1
{
public:
	//纯虚函数
	virtual void func(int a, int b) = 0;
	virtual void func2(int a) = 0;
};

class Interface2
{
public:
	virtual void func(int a, int b) = 0;
};

//当纯虚函数在多继承中出现了重复， 那么在子类中只要重新重写一次就可以了
class Child : public Interface1, public Interface2
{
public:
	virtual void func(int a, int b)
	{
		cout << "a = " << a << "b = " << b << endl;
	}
	virtual void func2(int a)
	{
		cout << "func2 ()" << endl;
	}
};

int main(void)
{
	Child c;
	c.func(10, 20);

	Interface1 *if1 = new Child;
	if1->func(10, 20);
	if1->func2(10);

	Interface2 *if2 = new Child;
	if2->func(10,20);

	
	return 0;
}