#include	<iostream>
using namespace	std;
//构造中调⽤构造是危险的⾏为


class	MyTest
{
public:
	MyTest(int	a, int	b, int	c) //有参 构造函数
	{
		_a = a;
		_b = b;
		_c = c;
	}

	MyTest(int	a, int	b) //有参数的构造函数，两个参数
	{
		_a = a;
		_b = b;
		//构造函数中，无法嵌套构造函数 来通过构造函数给自己的成员变量赋值，
		//此构造函数已经又创建了另一个对象。
		MyTest(a, b, 100);	//产⽣新的匿名对象
		//新的匿名对象 a->1 b->2 c ->100

	}
	~MyTest()
	{
		printf("MyTest~:%d,	%d,	%d\n", _a, _b, _c);
	}

	int	getC()
	{
		return	_c;
	}
	void	setC(int	val)
	{
		_c = val;
	}

private:
	int	_a;
	int	_b;
	int	_c;
};

int	main()
{
	MyTest	t1(1, 2); //t1.a -->1  t1.b -->2 t1.c--->? 


	printf("c:%d\n", t1.getC());	//请问c的值是？

	return 0;
}