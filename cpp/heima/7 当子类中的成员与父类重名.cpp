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

	int a;
};

class Child :public Parent
{
public :
	Child(int a, int aa) : Parent(aa)
	{
		this->a = a; //让Child 的a  = a， 让父亲的a = aa
	}

	void print()
	{
		cout << "a = " << a << endl; //默认是使用 当前类的重名的变量
		cout << "Parent::a = " << Parent::a << endl;  //如果想访问父类中的重名变量 需要加上父类的作用域
	} 

	int a;
	/*
	  a ---> Paretn::a
	*/
};

int main(void)
{
	Child c(10, 100);

	c.print();
	
	return 0;
}