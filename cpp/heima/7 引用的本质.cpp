#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


struct TypeA
{
	int *a;
};

struct TypeB
{
	double &a;
};

struct Teacher
{
	int id;
	char name[64];
};


void motifyTeacher(Teacher &t) //
{
	t.id = 100; // 如果说t是一个常指针， *t 就是指针指向内存空间  (*t).id = 100
	//当你要试图修改或者获取已经初始化的引用的时候， 编译器会有一个隐藏的*的操作
}

void motifyA(int *const a)   //常指针 也是一个常量， 也是必须要初始化，  也不能被修改
{
	*a = 100;
}

void motifyB(int &a)
{
	a = 1000; //a 实际上是一个常量指针， 但是如果你给一个a赋值，编译器会有一个隐形的操作， *
}

//在研究引用的时候 ，可以将引用理解为 一个 常指针
//在理解引用的时候， 可以将引用理解为 一个变量的别名

void test()
{
	int value = 20;
	Teacher t1 = { 1, "zhangsan" };

	motifyA(&value);

	cout << "value = " << value << endl;

	motifyB(value);  // int value --> int &a  , int& a = value 给引用指定指向哪个变量的时候， 编译器提供又有了一个隐形的操作
						// a = &value;

	cout << "value = " << value << endl;

	motifyTeacher(t1);  //如果说 motifyTeacher 的形参是一个常指针，Teacher *const t = &t1;
								//编译器发现 Teacher &t 形参是一个引用， Teacher &t = &t1;
								//当给引用初始化的时候， 会有一个&  的隐形操作
}


void motifyAA(int *a)
{
	*a = 100;   //间接的赋值
}

void motifyBB(int &a) //int &a = a;    a = &a;
{
	a = 200; //*a = 200
}

void test2()
{
	int a = 10; //条件一


	motifyAA(&a); //int*a = &a; //建立了关联

	motifyBB(a);
}


int main(void)
{
	int a = 10;
	int b = 20;

	const int c_a = 10;

	//c_a = 20;//常量在初始化之后，不能够再修改了

	int &re = a; //引用必须初始化.  引用在初始化之后，也不能够被改变
	re = b; // a = b 而不是 让re引用指向b

	cout << "re = " << re << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	re = 100; //是该的a 还是b？

	cout << "re = " << re << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	//1 引用 可能是一个 常量？

	cout << "sizeof(TypeA): " << sizeof(TypeA) << endl;
	cout << "sizeof(TypeB):" << sizeof(TypeB) << endl;

	//通过对引用求大小， 发现不管引用是什么类型 都是4个字节，都跟指针的大小一样。

	//2 引用可能是一个 指针？


	test();
	
	return 0;
}