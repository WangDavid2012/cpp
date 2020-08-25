#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test()
	{
		this->a = 0;
		this->b = 0;
	}

	Test(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	void printT()
	{
		cout << "a = " << a << ", b = " << b << endl;
	}

	int getA()
	{
		return this->a;
	}

	int getB()
	{
		return this->b;
	}

	//成员函数
	Test TestAdd01(Test &t1, Test &t2)
	{
		Test temp(t1.getA() + t2.getA(), t1.getB() + t2.getB());
		return temp;
	}

	Test TestAdd02(Test &another)
	{
		//Test temp(this->a + another.getA(), this->b + another.getB());
		Test temp(this->a + another.a, this->b + another.b);

		return temp;
	}


	void TestAdd03(Test &another)
	{
		this->a += another.a;
		this->b += another.b;
	}


	Test & TestAdd04(Test &another)
	{
		this->a += another.a;
		this->b += another.b;

		//返回自己
		return *this;
	}//temp引用 = *this 

private:
	int a;
	int b;
};

//提供一个方法来实现两个Test对象相加
//全局函数
Test TestAdd(Test &t1, Test &t2)
{
	Test temp(t1.getA() + t2.getA(), t1.getB() + t2.getB());

	return temp;
}//此时会析构temp

int main(void)
{
	Test t1(10, 20);
	Test t2(100, 200);
	 
	Test t3 = TestAdd(t1, t2); //调用了一个全局函数 

	t3.printT();
	
	Test t4 = t1.TestAdd01(t1, t2);
	t4.printT();

	Test t5 = t1.TestAdd02(t2); //创建临时的开销

	t5.printT();

	t1.TestAdd03(t2);
	t1.printT();

	(t1.TestAdd04(t2)).printT(); //t1的别名

	return 0;
}