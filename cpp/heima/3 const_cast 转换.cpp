#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


void func(const char *p) //p所指向的内存区域不能够修改
{
	char *pp = const_cast<char *>(p);//将p的const 属性去掉
	//char *pp = (char*)p;
	pp[0] = 'A';
}

int main(void)
{
	const char *p = "12345677"; // p指向的是常量区
	char buf[] = "12343242377";

	
	func(buf);//2
	//func(p);//1
	//cout << "p:" << p << endl;
	cout << "buf:" << buf << endl;

	const int a = 10;//a 就是一个常量，是一个10的符号
	const int *a_p = &a; //临时开辟了一个空间，把10放进去， 用a_p指向这个空间
	int *a_p1 = const_cast<int*>(a_p); //把a_p的const 属性去掉
	*a_p1 = 100;

	int *p2 = const_cast<int*>(&a);
	*p2 = 200;

	cout << "*a_p = " << *a_p << endl;
	cout << "a= " << a << endl;
	cout << "*p2 " << *p2 << endl;

	//const_cast 的作用就是 将一个有只读属性的指针，把只读属性去掉，但是前提是当前的内存空间是可以修改。
	
	return 0;
}