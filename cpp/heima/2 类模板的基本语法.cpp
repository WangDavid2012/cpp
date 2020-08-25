#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

template<class T>
class A
{
public:
	A(T a)
	{
		this->a = a;
	}

	void printA()
	{
		cout << "a = " << a << endl;
	}
private:
	T a;
};


//继承模板类， 直接继承已经实例化的模板类
//这么继承完的B类， B类此时是一个普通类。
class B :public A<int>
{
public:
	B(int a, int b) : A<int>(a)
	{
		this->b = b;
	}

	void printB()
	{
		cout << "b = " << b << endl;
	}
private:
	int b;
};


//C类继承的是一个模板类，没有实例化，此时C类依然是一个模板类，
//编译器在堆c类处理依然需要二次编译
template <class T>
class C :public A<T>
{
public:
	C(T a, T c) : A(a)
	{
		this->c = c;
	}

	void printC()
	{
		cout << "c = " << c << endl;
	}
private:
	T c;
};


//普通函数
void func(A<int> & a)
{
	a.printA();
}

//模板函数
template <class T>
void func2(A<T> &a)
{
	a.printA();
}


int main(void)
{
	A<int> a(10);

	a.printA();

	func(a);
	func2<int>(a);


	A<double> a2(30.0);
	a2.printA();

	cout << " ------  " << endl;
	B b(100, 200);

	b.printB();


	cout << "-------- " << endl;
	C<int>  c(1000, 2000); //C类是一个模板类

	c.printC();

	

	return 0;
}