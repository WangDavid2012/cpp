#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	//默认构造函数。 就是一个无参数的构造函数，
	//如果不显示提供构造函数，系统就是调用默认的构造函数
	/*
	Test() {} 默认的构造函数，已经手动提供，默认就被隐藏
	*/

	//如果我们提供了一个显示的构造函数，那么默认的构造函数就被隐藏掉了。
	//构造函数一旦手动提供， 默认将不复存在。
	Test(int x, int y)
	{

		m_x = x;
		m_y = y;
		cout << "调用了有参数的构造函数" << endl;
	}

	//无参数的构造函数
	Test(){
		m_x = 0;
		m_y = 0;
		cout << "调用了无参数的构造函数" << endl;
	}


	//拷贝构造函数 ，想通过另一个Test对象 another 将本对象进行拷贝
	Test(const Test & another)
	{
		m_x = another.m_x;
		m_y = another.m_y;
		cout << "调用了拷贝构造函数" << endl;
	}

	//等号操作符
	void operator = (const Test &t)
	{
		cout << "调用了=号操作符" << endl;
		m_x = t.m_x;
		m_y = t.m_y;
	}

	void printT()
	{
		cout << "x : " << m_x << ", y : " << m_y << endl;
	}

	//提供一个析构函数
	~Test()
	{
		cout << "~Test（）析构函数被执行了" << endl;
		cout << "(" << m_x << ", " << m_y << ")" << "被析构了" << endl;
	}

private:
	int m_x;
	int m_y;
};


//拷贝构造函数的第一个场景
void test1()
{
	Test t1(1, 2);
	Test t2(t1);
	//通过t1 给t2 进行赋值

	t2.printT();
}

//拷贝构造函数的第二场景
void test2()
{
	Test t1(1, 2);
	Test t2;
	t2 = t1; //调用的不是拷贝构造函数，调用的是 =号操作符，也能够完成将t1的值给t2 但不是调用t2的拷贝构造函数。
}


void func(Test t) //Test t = test1::t1; //会调用局部变量t的拷贝构造函数
{
	cout << "func begin..." << endl;
	t.printT();
	cout << "func end..." << endl;

}

//场景三
void test3()
{
	cout << "test3 begin ..." << endl;
	Test t1(10, 20); //创建了一个t1的对象。通过t1的有参数的构造函数
	func(t1);

	cout << "test3 end..." << endl;
}


int func(void)
{
	int a = 10;
	return a;
}
//场景四
Test func2()
{
	cout << "func2 begin..." << endl;
	Test temp(10, 20); //调用temp的带参数构造函数  
	cout << "func2 end.." << endl;
	return temp; // 有一个临时的匿名对象 = temp ，把temp的数据给到了临时的匿名对象,  ,会调用这个临时匿名
						//对象的拷贝构造函数， 将temp穿进去。
}

void test4() 
{
	cout << "test4 begin " << endl;
	func2();

	//匿名对象在此被析构了， 如果一个临时的匿名对象，没有任何变量去接收它，编译器认为这个临时匿名对象没有用处。
	//编译器会立刻销毁这个临时的匿名对象
	cout << "test4 end" << endl;
}

void test5()
{
	cout << "test5 begin ..." << endl;
	Test t1 = func2();//如果有一个变量去接收这个临时的匿名对象， 编译器认为这个匿名对象转正了，就不会立刻给他销毁。
							//t1 = 匿名的临时对象 为什么不会发生拷贝构造
							//	此时的t1 去接收这个匿名的临时对象不是 重新创建一个t1 而是给这个匿名对象起个名字就叫t1
							//一旦这个匿名对象有了自己的名字，编译器就不会立刻给这个匿名对象销毁了，
							//就当普通局部变量处理了

	cout << "test5 end..." << endl;

	//在此时析构的t1
}

void test6()
{
	cout << "test6 begin..." << endl;
	Test t1; //调用t1的无参数构造函数
	t1 = func2(); //调用的=号操作符 ,,t1 = 匿名对象。 调用了t1的=号操作符。
						//此时匿名没有被转正，匿名没有自己的名字， 匿名对象这个内存没有自己的别名， 编译器就会立刻销毁。
	cout << "test6 end..." << endl;
}


int main(void)
{
	
	//test3();
	//test4();

	//func();

	//test5();
	test6();


	return 0;
}