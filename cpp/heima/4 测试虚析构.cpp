#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent1
{
public:
	void func(){
		cout << "Parent1()..." << endl;
	}
	virtual ~Parent1(){}
private:
	int a;
};

class Parent2
{
public:
	void func(){
		cout << "Parent2()..." << endl;
	}
	virtual ~Parent2(){}
private:
	int b;
};

class Child :public Parent1, public Parent2
{
public:
	void func()
	{
		cout << "Child() ..." << endl;
	}
private:
	int c;
};


void test()
{
	Parent1 * p = new Child;

	p->func(); //没有多态

	delete p; //正常delete 没有问题

	Parent2 *p2 = new Child;
	p2->func();

	delete p2; //delete p2 ;; p2.~,  free(p2)    delete Child,  Child.~, free(child)
}

int main(void)
{
	test();
	
	return 0;
}