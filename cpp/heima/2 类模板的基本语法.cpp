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
	C<int>  c(1000, 2000); //C����һ��ģ����

	c.printC();

	

	return 0;
}