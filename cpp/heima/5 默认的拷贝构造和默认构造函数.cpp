#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class B
{
public:
	/*
	
	默认提供的函数
	B() {
		//默认的无惨构造函数
	}
	B(const B& b)
	{
		m_b = b.m_b; //默认的拷贝构造函数
		p = b.p;
	}
	~B()
	{
		//默认的析构函数
	}
	*/

	//如果显示的写了一个普通构造函数， 会隐藏默认的无惨构造函数
	//如果显示的写了一个拷贝构造函数 ，会隐藏默认的无参构造函数和默认的拷贝构造函数
	//如果显示的写了一个析构函数， 会隐藏默认的析构函数
	B(const B& b)
	{

	}
private:
	int m_b;
	char *p;
};

class A
{
public:
	/*
	默认的构造函数
	如果普通构造函数，提供了一个显示的构造， 那么这个无参的默认构造就会被隐藏。 不会把拷贝构造函数隐藏掉
	A()
	{

	}
	*/
	A(int a)
	{
		m_a = a;
	}

	/*
	默认的拷贝构造函数
	A(const A & a)
	{
	   m_a = a;
	}
	*/
	//显示的提供一个拷贝构造的函数的时候，默认的拷贝构造函数就会被隐藏
	A(const A &a) {
		cout << "显示提供的拷贝构造函数" << endl;
		m_a = a.m_a;
	}

	/*
	 默认的析构函数
	 ~A()
	 {
	 }
	*/

	//只有提供一个显示的析构函数，才会将默认的析构覆盖点
	~A()
	{
		cout << "A的析构函数 调用 " << endl;
	}
private:
	int m_a;
};

int main(void)
{
	A aObj(10); //当你不提供任何构造函数的时候， 系统会有一个默认的构造函数
	A aObj2 = aObj;  //调用了aObj2的拷贝构造函数
	//A aObj2(aObj);
	
	return 0;
}