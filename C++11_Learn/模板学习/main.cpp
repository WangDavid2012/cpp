#include <iostream>

using namespace std;

//1. 模板类静态成员
template <typename T> struct testClass
{
	static int _data;
};
template<> int testClass<char>::_data = 1;
template<> int testClass<long>::_data = 2;
int main(void) {
	cout << boolalpha << (1 == testClass<char>::_data) << endl;
	cout << boolalpha << (2 == testClass<long>::_data) << endl;
}

//2. 模板类偏特化 
template <class I, class O> struct testClass
{
	testClass() { cout << "I, O" << endl; }
};
template <class T> struct testClass<T*, T*>
{
	testClass() { cout << "T*, T*" << endl; }
};
template <class T> struct testClass<const T*, T*>
{
	testClass() { cout << "const T*, T*" << endl; }
};
int main(void)
{
	testClass<int, char> obj1;
	testClass<int*, int*> obj2;
	testClass<const int*, int*> obj3;
}

//3.类模版+函数模版
template <class T> struct testClass
{
	void swap(testClass<T>&) { cout << "swap()" << endl; }
};
template <class T> inline void swap(testClass<T>& x, testClass<T>& y)
{
	x.swap(y);
}
int main(void)
{
	testClass<int> obj1;
	testClass<int> obj2;
	swap(obj1, obj2);
}


//4. 类成员函数模板 
struct testClass
{
	template <class T> void mfun(const T& t)
	{
		cout << t << endl;
	}
	template <class T> operator T()
	{
		return T();
	}
};
int main(void)
{
	testClass obj;
	obj.mfun(1);
	int i = obj;
	cout << i << endl;
}

//5. 缺省模板参数推导 
template <class T> struct test
{
	T a;
};
template <class I, class O = test<I> > struct testClass
{
	I b;
	O c;
};

void main()
{
}


//6. 非类型模板参数 
template <class T, int n> struct testClass {
	T _t;
	testClass() : _t(n) {
	}
};
int main(void) {
	testClass<int, 1> obj1;
	testClass<int, 2> obj2;
}


//7. 空模板参数 
template <class T> struct testClass;
template <class T> bool operator==(const testClass<T>&, const testClass<T>&)
{
	return false;
};
template <class T> struct testClass
{
	friend bool operator== <>(const testClass&, const testClass&);
};
void main()
{
}

//8. template template 类
struct Widget1
{
	template<typename T>
	T foo() {}
};

template<template<class T>class X>
struct Widget2
{
};
void main()
{
	cout << 3 << '\n';
}

