#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//普通函数
void myPrint(int a, int b)
{
	cout << "普通函数" << endl;
	cout << "a = " << a << ", b = " << b << endl;
}

//模板函数
template<typename T>
void myPrint(T a, T b)
{
	cout << "模板函数" << endl;
	cout << "a = " << a << ", b = " << b << endl;
}

//1  如果没有普通函数 ，编译器会根据模板函数就行隐式的匹配。如果匹配到模板函数可以调用，调用模板
//2  编译器匹配普通函数的优先级 大于 模板函数
//3 当普通函数需要隐式转换的时候，如果模板函数能够匹配，那么就优先使用模板函数。
//4 模板函数 是类型的严格匹配 ，不会给参数类型进行隐式转换。

int main(void)
{
	int aInt = 10;
	int bInt = 20;

	char aChar = 'a';
	char bChar = 'b';
	
	myPrint(aInt, bInt);

	cout << " ----- " << endl;
	myPrint(aChar, bChar);

	cout << " ------  " << endl;
	myPrint(aChar, bInt);

	cout << " ------ " << endl;
	myPrint(aInt, bChar);
	
	return 0;
}