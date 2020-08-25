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
	auto f1 = std::bind(fun, 1, 2, 3); //��ʾ�󶨺��� fun �ĵ�һ��������������ֵΪ�� 1 2 3
	f1(); //print:1  2  3

	auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
	//��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��ɵ��� f2 �ĵ�һ����������ָ��
	f2(1, 2);//print:1  2  3

	auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
	//��ʾ�󶨺��� fun �ĵ���������Ϊ 3����fun �ĵ�һ�����������ֱ��е��� f3 �ĵڶ���һ������ָ��
	//ע�⣺ f2  ��  f3 ������
	f3(1, 2);          //print:2  1  3

	int n = 2;
	int m = 3;

	auto f4 = std::bind(fun_2, n, placeholders::_1);
	f4(m); //print:3  4

	cout << m << endl;//print:4  ˵����bind���ڲ����Ȱ󶨵Ĳ�����ͨ��std::placeholders���ݵĲ�����ͨ�����ô��ݵ�
	cout << n << endl;//print:2  ˵����bind����Ԥ�Ȱ󶨵ĺ���������ͨ��ֵ���ݵ�

	A a;
	auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
	f5(10, 20);//print:10 20
			   //������һ������ָ�� fc������ֵ��void������ int int
	std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
	fc(10, 20);//print:10 20

	return 0;
}



//less()��һ����Ԫ������less(a, b)��ʾ�ж�a<b�Ƿ������

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
