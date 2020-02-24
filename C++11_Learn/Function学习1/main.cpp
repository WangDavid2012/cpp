#include <iostream>
#include <functional>

using namespace std;

std::function<bool(int, int)> fun;

//普通函数
bool compare_com(int a, int b)
{
	return a > b;
}

//lambda表达式
auto compare_lambda = [](int a, int b) { return a > b; };

//仿函数
class compare_class
{
public:
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

//类成员函数
class compare
{
public:
	bool compare_member(int a, int b)
	{
		return a > b;
	}
	static bool compare_static_member(int a, int b)
	{
		return a > b;
	}
};
// 测试例程
int main()
{
	bool result;
	fun = compare_com;
	result = fun(10, 1);
	cout << "普通函数输出, result is " << result << endl;

	fun = compare_lambda;
	result = fun(10, 1);
	cout << "lambda表达式输出, result is " << result << endl;
	
	//仿函数，不是特别理解，暂时略过
	fun = compare_class();
	result = fun(10, 1);
	cout << "仿函数输出, result is " << result << endl;

	fun = compare::compare_static_member;
	result = fun(10, 1);
	cout << "类静态成员函数输出, result is " << result << endl;

	////类普通成员函数比较特殊，需要使用bind函数，并且需要实例化对象，成员函数要加取地址符
	compare temp;
	fun = std::bind(&compare::compare_member, temp, std::placeholders::_1, std::placeholders::_2);
	result = fun(10, 1);
	cout << "类普通成员函数输出, result is " << result << endl;
}