#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	Parent(int a)
	{
		this->a = a;
	}
	virtual void print() //给一个成员函数 定义为 虚函数。
	{
		cout << "Parent ::print() : a = " << a << endl;
	}
private:
	int a;
};


class Child :public Parent
{
public:
	Child(int a, int b) :Parent(a)
	{
		this->b = b;
	}

	//重定义父类函数： 发生在子类和父类之间
	//当子类重写父类的成员函数，如果父类中这个函数不是虚函数， 是函数的重定义
	//如果子类重写父类的成员函数， 如果父类中的这个函数是 虚函数。 这是函数的重写。
	virtual void print()
	{
		cout << "Child: print b:" << b << endl;
		//Parent::print();
	}
private:
	int b;
};

//2015
/*
class Child2 :public Parent
{
public:

	virtual void print(){
		cout << "CHild 3 Print().." << endl;
	}
private:
};
*/

//1999 可以利用多态的特性来调用未来写的对象的方法。

void myPrintFunc(Parent *p) //  让父类指针指向子类对象的时候，
{
	p->print();// 再此时 print函数 发生了多态现象
}

int main(void)
{
	Child c(10, 20);
	c.print(); //调用的子类的print

	Parent p(100);
	p.print(); //调用的父类的print

	cout << "  -----  " << endl;
	myPrintFunc(&p); //希望调用父类的print

	cout << " ------  " << endl;
	myPrintFunc(&c); //希望调用子类的print  //Parent* p = &c;  父类指针指向子类对象。
								//编译器 会 不管你传递进来的是父类对象还是子类对象， 都会给你调用父类。
								//编译器做了一个安全的举措， 即使你传递是子类
								//编译器也认为 调用父类的print 是安全，他能够保证父类的print函数是一定存在的。
								//没有冒险去调用子类的print
	//Child2 c2;
	//myPrintFunc(&c2);
	
	return 0;
}