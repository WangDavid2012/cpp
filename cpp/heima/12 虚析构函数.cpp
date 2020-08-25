#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	A() {
		cout << "A() ..." << endl;
		this->p = new char[64]; //给p开辟了一个空间
		memset(p, 0, 64);
		strcpy(p, "A string ");
	}

	virtual void print()
	{
		cout << p << endl;
	}

	virtual ~A()
	{
		cout << "~A()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p; 
};

class B : public A
{
public:
	B() {
		cout << "B()..." << endl;
		this->p = new char[64];
		memset(p, 0, 64);
		strcpy(p, "B string");
	}

	//重写
	virtual void print()
	{
		cout << p << endl;
	}

	virtual  ~B()
	{
		cout << "~B()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p;
};

class C : public B
{
public:
	C() {
		cout << "C()..." << endl;
		this->p = new char[64];
		memset(p, 0, 64);
		strcpy(p, "C string");
	}


	virtual void print()
	{
		cout << p << endl;
	}

	virtual  ~C()
	{
		cout << "~C()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p;
};


void func(A *p)//p = cp;  p = &c //用父类指针指向子类对象。
{ 
	p->print(); //在此处发生多态。

	//delete p; //delete 一个父类指针   如何让delete p不是将p看做父类指针来delete 而是当子类呢
	//如果类的析构函数加上了 virtual delete 就会发生多态。 delelte p 会调用C类的析构函数
}

void myDelete(A*p) //p->cp   父类指针指向子类对象
{
	delete p; //p->~()  //如果~（） 不加virtual关键 不会发生多态。
					//希望delete p， p->~() 调用C类的~（）
					// 如果给 所有的类的析构函数加上virtual关键字  就会发生多态。
}




void test()
{
	C c;
}
int main(void)
{
	/*
	C *cp = new C;

	cp->print();//cp的函数

	delete cp;
	*/

	cout << " -----  " << endl;
	C * cp1 = new C; //发生3此构造 A() B（） C()

	//test();
	func(cp1);
	myDelete(cp1); 
	
	return 0;
}