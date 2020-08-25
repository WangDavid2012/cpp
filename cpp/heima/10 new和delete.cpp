#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test()
	{
		m_a = 0;
		m_b = 0;
		cout << "0，0 构造" << endl;
	}
	Test(int a, int b)
	{
		m_a = a;
		m_b = b;
		cout << "a = " << m_a << ", b = " << m_b << "构造 " << endl;
	}

	void setA(int a)
	{
		m_a = a;
	}
	void setB(int b)
	{
		m_b = b;
	}

	void printT()
	{
		cout << "a = " << m_a << ", b = " << m_b << endl;
	}

	~Test()
	{
		cout << "a = " << m_a << ", b = " << m_b << "析构 " << endl;
	}
private:
	int m_a;
	int m_b;
};


//C语言中
void test1()
{
	int *p = (int*)malloc(sizeof(int));
	*p = 10;
	cout << *p << endl;
	if (p != NULL) {
		free(p);
		//delete p; //delete 可以释放malloc的开辟的内存
	}

	int *array_p = (int*)malloc(sizeof(int)* 10);
	for (int i = 0; i < 10; i++) {
		array_p[i] = i + 10;
	}

	for (int i = 0; i < 10; i++) {
		cout << array_p[i] << endl;
	}

	if (array_p != NULL) {
		free(array_p);
	}


	cout << " --------  " << endl;

	Test *tp = (Test*)malloc(sizeof(Test)); //不会调用对象的构造函数
	//p(10, 20);
	tp->setA(10);
	tp->setB(20); //malloc出来的对象指针，只能够通过成员函数来进行初始化
	tp->printT();

	if (tp != NULL) {
		free(tp); //不会调用对象的析构
	}
}

//malloc 和free 在对于普通变量是可以混合使用的，但是malloc和free是函数，
//new 和delete 是操作符。不是一个函数。

//C++中的new delete
void test2()
{
	//new 能够完成所有malloc的需求
	int *p = new int; //在堆上动态开辟4个字节
	*p = 10;
	cout << *p << endl;

	if (p != NULL) {
		//delete p; //delete 一个变量
		free(p); //用new开辟的内存， free也能够释放。
	}

	cout << "-----" << endl;

	int *array_p = new int[10];
	for (int i = 0; i < 10; i++) {
		array_p[i] = i + 10;
	}
	for (int i = 0; i < 10; i++) {
		cout << array_p[i] << endl;
	}

	if (array_p != NULL) {
		delete[]   array_p; //delete 一个数组
	}


	cout << "-------" << endl;
	//Test *tp = new Test(10, 20);//调用了有参数的构造函数 //new 在创建一个对象的时候，会调用对象的构造函数
	Test *tp = new Test;//调用了无参构造函数
	tp->printT();
	if (tp != NULL) {
		delete tp; //delete在释放一个对象指针的时候，会调用对象析构函数
	}
}

int main(void)
{
	//test1();
	test2();
	
	return 0;
}