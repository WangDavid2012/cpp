#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	//构造函数(构造器)， 是为了给对象提供初始化而出现的。
	//函数名字跟类型是一样的，没有返回值，并且可以重载

	//无参数的构造函数
	Test()
	{
		m_x = 0;
		m_y = 0;
		p = (char*)malloc(100);
		strcpy(p, "123");
	}

	//带参数的构造函数
	Test(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	//一个参数的构造函数
	Test(int x)
	{
		m_x = x;
		m_y = 0;
	}


	//析构函数 : ~+类型  没有任何的参数
	~Test()
	{
		cout << "Test 的析构函数~Test() 被调用了" << endl;
		if (p != NULL) {
			cout << "p的堆空间被释放了" << endl;
			free(p);
			p = NULL;
		}
	}


	void printT()
	{
		cout << "x : " << m_x << ", y: " << m_y << endl;
	}

	void init(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
private:
	int m_x;
	int m_y;
	char *p;
};

void test1()
{
	Test t1; //调用无参数的构造函数
		//t1 是一个局部变量， 生命周期是test1（）一样的， 在test1（）函数执行完毕需要 先销毁t1变量
	//t1对象销毁之前，系统就会默认的调用t1的析构函数
	t1.printT();


	return;
}

int main(void)
{
	//Test t1; //t1 在开辟内存之后，t1中的m_x  m_y 是随机值
	//
	//t1.init(10, 20); //每次都需要显示的调用一个初始化的函数。

	//能不能提供一个 在创建一个对象的时候就给他初始化呢？

	test1();

	//Test t1;  //创建一个对象， 这个对象会直接调用无参数的构造函数。

	//Test t2(10, 20); //在创建对象完毕之后， 就已经将对象的一些成员变量初始化了

	//Test t3(10);
	
	return 0;
}