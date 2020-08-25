#include <iostream>
#include <iostream>
#include <algorithm>
#include <functional>


using namespace std;
class A
{
public:
	void fun_3(int k, int m)
	{
		cout << k << " " << m << endl;
	}
};

void fun(int x, int y, int z)
{
	cout << x << "  " << y << "  " << z << endl;
}

void fun_2(int &a, int &b)
{
	a++;
	b++;
	cout << a << "  " << b << endl;
}

int bind_test1()
{
	auto f1 = std::bind(fun, 1, 2, 3); //表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
	f1(); //print:1  2  3

	auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
	//表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
	f2(1, 2);//print:1  2  3

	auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
	//表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别有调用 f3 的第二，一个参数指定
	//注意： f2  和  f3 的区别。
	f3(1, 2);          //print:2  1  3

	int n = 2;
	int m = 3;

	auto f4 = std::bind(fun_2, n, placeholders::_1);
	f4(m); //print:3  4

	cout << m << endl;//print:4  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的
	cout << n << endl;//print:2  说明：bind对于预先绑定的函数参数是通过值传递的

	A a;
	auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
	f5(10, 20);//print:10 20
			   //定义了一个函数指针 fc，返回值是void，参数 int int
	std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
	fc(10, 20);//print:10 20

	return 0;
}



//less()是一个二元函数，less(a, b)表示判断a<b是否成立。

int bind_test2()
{
	int numbers[] = { 10,20,30,40,50,10 };
	int cx;
	cx = count_if(numbers, numbers + 6, bind(less<int>(), std::placeholders::_1, 40));
	cout << "There are " << cx << " elements that are less than 40.\n";

	cx = count_if(numbers, numbers + 6, bind(less<int>(), 40, std::placeholders::_1));
	cout << "There are " << cx << " elements that are not less than 40.\n";

	system("pause");
	return 0;
}
