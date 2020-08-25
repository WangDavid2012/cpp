#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class A
{
public:
	A(){
		cout << "A() ...." << endl;
	}
	~A()
	{
		cout << "~A()...." << endl;
	}
	void func()
	{
		cout << "a --> func()...." << endl;
	}
};


class MyAutoPtr //定义一个指向A类的智能指针
{
public:
	//有参数的构造函数，  将A的对象的地址  接收过来。
	MyAutoPtr(A* ptr) //ptr = new A;
	{
		this->m_p = ptr;
	}

	~MyAutoPtr()
	{
		if (this->m_p != NULL) {
			delete m_p;
		}
	}

	A* operator->()
	{
		return m_p;
	}

	A &  operator*()
	{
		return *m_p; //A temp = *m_p; 
	}

private:
	A* m_p;//指向A对象的地址。
};


void test1()
{
	//只能指针不需要我们手动 delete这个空间
	auto_ptr<A>   auto_p(new A);    //智能指针。
	auto_p->func();
}

void test2()
{
	MyAutoPtr auto_p(new A); // A  auto_p  &A,  *auto_p  A

	//auto_p =  &A;
	//auto_p->     func(); // A* m_p = &A;  m_p->func();
	//(*auto_p)      .func()//  *m_p    .func()
	// m_p->      func();
	/*
	A* m_p = new A;
	m_p->func();
	(*m_p).func();
	delete m_p;


	*/

	auto_p->func();  //m_p->func(); 

	(*auto_p).func();   //(*m_p).func();

	//销毁auto_p   就会调用auto_p 析构函数
}


class Teacher
{
public:
	Teacher(int id, string name)
	{
		this->id = id;
		this->name = name;
	}

	void printT()
	{
		cout << "id = " << id << " name = " << name << endl;
	}
private:
	int id;
	string name;
};


int main(void)
{
	
	test2();

	string str1 = "12312321";
	string str2 = str1;
	string str3;

	str3 = str1 + str2;

	cout << str1 << endl;


	return 0;
}