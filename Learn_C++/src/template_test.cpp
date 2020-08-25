#include <iostream>
using namespace std;

template <class T>
T myadd(T a, T b)
{
	return a + b;
}
//����ģ��ʱ����Ҫ�������ɵ�һ������ĺ���
//��Ҫͨ��ģ��ȥ���ɺ�����Ȼ���ٵ���
void template_test()
{
	int a = 2, b = 4;
	char c1 = 'a';
	char c2 = 'b';
	myadd(a, b);				//������һ��myadd(int,int)���͵ĺ���
	myadd(c1, c2);				//������һ��myadd(char,char)���͵ĺ���	

}

//��ģ��Ļ����﷨
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


//�̳�ģ���࣬ ֱ�Ӽ̳��Ѿ�ʵ������ģ����
//��ô�̳����B�࣬ B���ʱ��һ����ͨ�ࡣ
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


//C��̳е���һ��ģ���࣬û��ʵ��������ʱC����Ȼ��һ��ģ���࣬
//�������ڶ�c�ദ����Ȼ��Ҫ���α���
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


//��ͨ����
void func(A<int> & a)
{
	a.printA();
}

//ģ�庯��
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
	C<int>  c(1000, 2000); //C����һ��ģ����
	c.printC();
	return 0;
}



