#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

int getA1()
{
	int a = 10;
	return a;
} //value_a = a; 

int &getA2()
{
	int a = 10;
	return a;
} //匿名的引用 int & = a;  //  int &temp = &a;

int &getBB()
{
	static int b = 100;
	return b;
}

int main(void)
{
	int value_a = 0;

	value_a = getA1();   //正确

	cout << "value_a " << value_a << endl;


	value_a = getA2();// int value_a = temp;   // int value_a = *temp; //这是一个值拷贝
	cout << "value_a " << value_a << endl;
	cout << "value_a " << value_a << endl;


	int &r_a = getA2(); //没有值拷贝动作  ，禁止
	//当函数返回值，是一个局部变量的引用的时候，不能再用引用来接收。
	cout << "r_a  " << r_a << endl;
	cout << "r_a  " << r_a << endl;


	int &r_b = getBB(); //此时的r_b 就是 getBB中的 static int b
	//当函数返回值，不是子函数内部局部变量，就可以用引用进行接收，
	cout << "r_b " << r_b << endl;
	cout << "r_b " << r_b << endl;

	r_b = 2000; //此时r_b 就是getBB中的b的别名， 修改r_b 就是修改 b

	int value_b = getBB();  // 会有一个临时的引用 int &temp = b;  value_b = *temp; //发生了值拷贝
	//getBB();//getBB 就是b的别名
	//int value_b = *(getBB());
	//int value_b = static b;
	cout << "value_b " << value_b << endl;

	getBB() = 3000; //static b  = 3000; //当引用作为函数的返回值的时候，只要这个引用是合法的，就可以当左值。


	//三目运算符
	int a = 10;
	int b = 20;

	(a < b ? a : b) = 30;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	return 0;
}