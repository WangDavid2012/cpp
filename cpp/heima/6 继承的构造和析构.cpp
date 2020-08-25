#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;



//子类在进行初始化成员变量的时候， 如果此成员变量是继承过来的， 那么需要调用父类的构造器来初始化。

class Parent
{
public:
	Parent(int a) {
		this->a = a;
		cout << "Parent(int a) ..." << endl;
	}
	~Parent()
	{
		cout << "~Parent()..." << endl;
	}

	void printA()
	{
		cout << "a = " << a << endl;
	}
private:
	int a;
};

class Son :public Parent
{
public:
	//子类继承于父类， 父类中的成员变量 应该用 父类的构造函数来初始化
	Son(int a, int b) : Parent(a)
	{
		this->b = b;
		cout << "Son(int a, int b) ..." << endl;
	}
	~Son()
	{
		//Parent p = Parent(b);//是一个新的parent对象。
		cout << "~Son() ..." << endl;
	}

	void printB()
	{
		cout << "b = " << b << endl;
	}

	void pirntAB()
	{
		Parent::printA();
		this->printB();
	}
private:
	int b;
	char *name;
};

void test1()
{
	Parent p(30);

	Son s(20, 20); // p + s独有


	s.pirntAB();
}

int main(void)
{

	test1();
	return 0;
}