#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
子类对象可以当作父类对象使用
子类对象可以直接赋值给父类对象
子类对象可以直接初始化父类对象
父类指针可以直接指向子类对象
父类引用可以直接引用子类对象
*/

class Parent
{
public:
	void printP()
	{
		cout << "Parent::printP()..." << endl;
	}
	int a;
};

class Child :public Parent
{
public:
	void printC()
	{
		cout << "Child:: printC()...." << endl;
	}
	int b;
};

void print(Parent *p)
{
	p->printP();
}

int main(void)
{
	Child c;//子类对象
	c.printP(); //子类对象可以当作父类对象使用

	Parent p = c; // 由于子类拥有全部父类的内存空间，子类能够保障父类初始化完整。
						 //子类对象可以直接初始化父类对象 因为子类内存空间包容的父类的，能够保证
						// 完全赋值。
	//Child c2 = p;

	
	//父类指针可以直接指向子类对象
	//子类对象能够完全满足父类指针的需求，所以可以  父类指针可以直接指向子类对象
	Parent *pp = &c;  //pp->printP   (x ) pp->printC
	//pp->printC();
	pp->a;

	//不能用子类指针指向父类对象。
	//父类对象满足不了子类指针的所有需求， 所以不能够 子类指针指向父类对象。
	//Child *cp = &p; // cp-> printP,  cp->printC
	//cp->b; //p中没有b的内存。 //此时访问b就越界了。
	//cp->printP();
	//cp->printC();

	//父类引用可以引用子类对象
	Parent &pr = c;

	//子类引用不可以引用父类的对象。
	//Child &cr = p;

	print(&p); //Parent* p = &p;

	print(&c); //Parent *p = &c;

	//父类指针可以指向子类对象。 

	return 0;
}