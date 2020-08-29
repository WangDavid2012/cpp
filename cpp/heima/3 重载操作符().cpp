#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Sqr
{
public:
	Sqr(int a)
	{
		this->a = a;
	}

	//想把s对象 定义成一个 带有一个参数的函数， 求出平方 返回
	//此函数功能就是 对a求平方
	int operator()(int a)
	{
		return a*a;
	}
private:
	int a;
};

//STL C++的标准模板库


//a 普通int  
//fp  --> int (*)(int)
void func(int a, int(*fp)(int))
{
	cout << a << "的平方结果是" << endl;
	cout << fp(a) << endl;
}

int sqr(int a)
{
	return a * a;
}

class Print
{
public:
	void operator()(int value)
	{
		cout << value << endl;
	}
};

void print(int value)
{
	cout << value << endl;
}


int main(void)
{
	Sqr s(10);

	int a = 10;

	//s对象 当成一个函数来使用
	//这种写法， 就是仿函数， 将s对象变成一个函数来使用，编译器认为s是一个函数。
	int aa = s(a);//s.operator()(a);    //伪函数


	//把一个对象 当成一个回调函数穿进去 就是仿函数的作用

	cout << aa << endl;


	int b = 20;

	func(b, sqr); //通过func 调用一个sqr回调函数
	//func(b, s);

	cout << "  ------  " << endl;

	vector<int> v1; //数组 添加10个元素

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 10);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << v1[i] << endl;
	}


	cout << " -----  " << endl;

	Print pObj;
	 
	for_each(v1.begin(), v1.end(), pObj); //pObjd(value)


	
	return 0;
}
