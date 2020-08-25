#include <iostream>
using namespace std;

template <class T>
T myadd(T a, T b)
{
	return a + b;
}
//调用模板时，需要首先生成的一个具体的函数
//需要通过模板去生成函数，然后再调用
void template_test()
{
	int a = 2, b = 4;
	char c1 = 'a';
	char c2 = 'b';
	myadd(a, b);				//会生成一个myadd(int,int)类型的函数
	myadd(c1, c2);				//会生成一个myadd(char,char)类型的函数	

}

//类模板的基本语法
template <class T>
class Person
{
	// public:
	// 	Person(T id, T age) :mId(id), mAge(age);
	// 
	// private:
	// 	T mId;
	// 	T mAge;
};

//template<class T>
//Person::Person(T id, T age)
//{
//	this->mAge = age;
//	this->mId = id;
//}




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


int template_test1(void)
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



