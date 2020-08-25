#include	<iostream>
using namespace	std;


int	Max(int	a, int	b)
{
	cout << "int	Max(int	a,	int	b)" << endl;
	return	a > b ? a : b;
}

template<typename	T>
T	Max(T	a, T	b)
{
	cout << "T	Max(T	a,	T	b)" << endl;
	return	a > b ? a : b;
}

template<typename	T>
T	Max(T	a, T	b, T	c)
{
	cout << "T	Max(T	a,	T	b,	T	c)" << endl;
	return	Max(Max(a, b), c);
}

int	main()
{
	int	a = 1;
	int	b = 2;

	cout << Max(a, b) << endl;	//当函数模板和普通函数都符合调⽤时,优先选择普通函数

	cout << Max<>(a, b) << endl;	//若显⽰使⽤函数模板,则使⽤<>	类型列表
	cout << Max(3.0, 4.0) << endl;	//如果 函数模板产⽣更好的匹配 使⽤函数模板
	cout << Max(5.0, 6.0, 7.0) << endl;	//重载
	cout << Max('a', 100) << endl;		//调⽤普通函数 可以隐式类型转换
	return 0;
}