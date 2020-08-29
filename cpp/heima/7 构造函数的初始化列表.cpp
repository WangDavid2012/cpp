#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	//显示提供一个带参数的构造函数
	A(int a)
	{
		m_a = a;
		cout << "a = " << m_a << "调用了构造函数" << endl;

	}
	~A()
	{
		cout << "a = " << m_a << "被析构了" << endl;
	}

	void printA()
	{
		cout << " a = " << m_a << endl;
	}
private:
	int m_a;
};

class B
{
public:
	B(int b) :a1(10), a2(100) //在初始化B的时候通过初始化列表给内部对象a1 和a2 进行了初始化
	{
		m_b = b;
		/*
		a1(10);
		a2(20);
		*/
		cout << "b = " << m_b << "调用了构造函数" << endl;
	}

	B(int aa1, int aa2, int b) : a1(aa1), a2(aa2), m_b(b) //通过初始化列表不仅能够初始化成员对象， 还可以初始化成员变量
	{

	}

	void printB()
	{
		cout << "b = " << m_b << endl;
		a1.printA();
		a2.printA();
	}

	~B()
	{
		cout <<"b = " <<m_b << " 调用了析构函数" << endl;
	}

private:
	int m_b;
	A a2;
	A a1;
};

//类内部的对象初始化的顺序，跟对象的定义顺序一样，跟初始化列表中的顺序无关
//析构的顺序就跟构造的顺序相反

class ABC
{
public:
	ABC()
	{

	}
	ABC(int a, int b, int c) :m_a(a), m_b(b), m_c(c) {}


	ABC(const ABC &abc)
	{
		m_a = abc.m_a;
		m_b = abc.m_b;
		m_c = abc.m_c;
	}

	void printABC()
	{
		cout << m_a << "," << m_b << "," << m_c << "," << endl;
	}
private:
	int m_a;
	int m_b;
	int m_c;
};


class ABCD
{
public:
	ABCD(int a, int b, int c, int d, int m) :m_abc(a, b, c), m_m(m)//常量成员变量不能够赋值，只能通过初始化列表进行初始化
	{
		m_d = d;
	}

	ABCD(int d, ABC abc, int m) :m_abc(abc), m_m(m)
	{
		m_d = d;
	}

	ABCD(int d, int m) :m_m(m)
	{

	}

	void printABCD()
	{
		m_abc.printABC();
		cout << m_d << endl;
	}

private: 
	ABC m_abc; 
	int m_d;
	const int m_m; //常量
};

int main(void)
{
	//A a(10);

	//a(10);//将一个a对象当成一个函数调用了

//	B b(1); 
//	b.printB();

	//B b2(10, 20, 30);
	//b2.printB();

	ABCD abcd_obj1(1, 2, 3, 4);
	abcd_obj1.printABCD();

	cout << " -----" << endl;

	ABC abc_obj(1, 2, 3); 
	ABCD abcd_obj2(40, abc_obj);
	abcd_obj2.printABCD();



	
	return 0;
}