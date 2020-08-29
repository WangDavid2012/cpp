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

int main(void)
{
	Test t1; //调用无参的构造函数
	Test t2(10, 20);
	//Test t3(10, 20, 30);
	t2.printT();
	Test t3(t2); //调用t3的拷贝构造函数  //调用拷贝构造函数的方式
	t3.printT();
	//Test t4 = t2; // 依然是调用t4的拷贝构造函数，

	Test t4(100, 200); //调用t4 的两个参数的构造函数

	Test t5; //先调用无惨构造。
	t5 = t2; //不会调用拷贝构造函数 //调用=号重载操作符  赋值操作符


	//析构函数的调用顺序， 跟对象的构造顺序相反， 谁先构造，谁最后一个被析构。
	
	return 0;
}