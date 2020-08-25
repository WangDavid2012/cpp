#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>

using namespace std;

template<class T>
class Complex;

template <class T>
Complex<T> mySub (Complex<T> &c1, Complex<T> &c2);


template<class T> //template <typename T>
class Complex
{
public:
	//如果写一个模板类提供一个友元函数， << >> 要在这个函数的声明 在操作符和参数列表之间
	// <T>
	friend ostream & operator<< <T> (ostream &os, Complex<T> &c); //cout <<c1

	//滥用友元
	friend Complex<T> mySub<T>(Complex<T> &c1, Complex<T> &c2);

	Complex()
	{
		this->a = 0;
		this->b = 0;
	}
	Complex(T a, T b)
	{
		this->a = a;
		this->b = b;
	}

	void pirntComplex()
	{
		cout << "( " << a << "+" << b << "i )" << endl;
	}

	Complex operator+(Complex &another);

	Complex operator-(Complex &another);

private:
	T a;
	T b;
};

template <class T>
Complex<T> Complex<T>::operator-(Complex<T> &another)
{

	Complex temp(this->a - another.a, this->b - another.b);
	return temp;

}

template <class T>
Complex<T>  Complex<T>::operator + (Complex<T> &another)
{
	Complex temp(this->a + another.a, this->b + another.b);
	return temp;
}



template <class T>
ostream & operator<<(ostream &os, Complex<T> &c)
{
	os << "( " << c.a << "+" << c.b << "i )" << endl;
	return os;
}


template<class T>
Complex<T> mySub(Complex<T> &c1, Complex<T> &c2)
{
	Complex<T> temp(c1.a - c2.a, c1.b - c2.b);
	return temp;
}




int main(void)
{
	Complex<int> c1(10, 20);
	c1.pirntComplex();

	Complex<int> c2(1, 2);
	
	Complex<int> c3; //调用无参构造
	c3 = c1 + c2;

	c3.pirntComplex();

	Complex<int> c4;
	c4 = c1 - c2;
	c4.pirntComplex();

	cout << " ----- " << endl;
	cout << c4 << endl;

	Complex<int> c5;
	c5 = mySub(c1, c2);
	
	return 0;
}