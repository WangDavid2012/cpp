#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

struct teacher
{
	int id;
	char name[64];
};

//2 对全局变量的检测能力加强， 一个变量不管是声明，还是定义，只能出现一次
int g_val ; //全局变量
//int g_val = 10;// 右一个全局变量

//1 实用性的增强， 对于变量的定义的位置，可以随意，没有要求
int test1(void)
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{

	}

	for (int i = 0; i < 10; i++) {
	}
	
	return 0;
}

//2 
void test2()
{
	//teacher t1; //C++中 在使用struct 时候不需要再将 struct 写进来
}

//3 

void f(int i)
{
	cout << "i = " << i << endl;
}

//4 bool类型
void test3()
{
	bool flag = true; //就代表逻辑真
	flag = false;       //就代表逻辑假

	cout << "bool:sizeof() : " << sizeof(flag) << endl; //bool占一个字节。

	flag = true; // 为真 
	cout << "flag = " << flag << endl; //当bool类型为true 他的数值是1

	flag = false; //为假
	cout << "flag = " << flag << endl;//当bool类型为false 他的数值是0

	//flag = 10;
	cout << "flag = " << flag << endl;

	//flag = 100;
	cout << "flag = " << flag << endl;

	//flag = -100;
	cout << "flag = " << flag << endl; //不管给bool赋值什么样的非0数值，他是都是true 1 


	//flag = 0;
	cout << "flag = " << flag << endl; 

	//bool类型的取值，只有0 和1 


	if (flag == true) { //默认判断flag 是否为true

	}

}


void test5()
{
	int a = 10;
	int b = 20;

	(a < b ? a : b) = 30; //返回是a变量的别名 
	//a
	cout << "a = " << a << endl;
	(a < b ? 10 : b); //三木运算符 如果作为左值， 那么 返回的结果不能有常量
}

//c++对const的加强
void test6() {
	const int a = 10; //c++的const 确实对a起了保护的作用，不能通过指针的间接赋值概念a的值
							//
	//int const b; //const int , int const 是等价的

	int *p = (int*)&a; //当c++编译器 发现 对一个const的常量符号取地址，
	*p = 20;//C语言中可以通过指针的间接赋值改变const变量 
				//*p 是改变的临时的变量 而不是 常量a符号

	printf("a = %d\n", a);
}

#define A (3)
#define B (4)

void test7()
{
	const int a = 3;
	const int b = 4;  //此时说明 c++中的const 就是一个常量， 永远不会被改变
								//c++语言对const 的增强，将const 变量真正变成了常量

	int array[a + b] = { 0 };

	int array_2[A + B] = { 0 };  // define 和const 变量 在编译的阶段不一样， define是预处理器 const 是编译器

//#define ff (10)
	const int ff = 10; //const 是编译器出 完全符合编译器的逻辑判断和此法分析
}

void test8()
{
	//cout << "ff = " << ff << endl; //没有区域的划分
}

enum season {
	SPR ,
	SUM ,
	AUT  ,
	WIN
};

void test9()
{
	enum season s = SPR;

	s = SUM; //为了增加枚举的可读性， 
	s = AUT;
	s = WIN;

}

struct student
{
	int id;
	char name[64];
};

void change_stu(struct student *s)
{
	s ->id = 10;
}

void change_stu2(const struct student *s)
{
	//s->id = 10; //此时s所指向的区域是一个常量 不能够被修改
	struct student s2;
	s = &s2;
}

void change_stu3(struct student *const s)
{
	s->id = 10;
	//struct student s2;
	//s = &s2;  //s是一个常量指针
}

void change_stu4(const struct student *const s)
{
	//s->id = 10;
	//struct student s2;
	//s = &s2;  //s是一个常量指针
}

int g(int a, int b, int c)
{
	return 100;
}
//函数一定要有返回值， 如过函数没有返回值，也要加void




int main(void)
{
	//f(1, 2, 3); //error 对于函数传参的检测能力更加的严格，
	//g(1, 2, 3); //C_++编译器 对函数形参传递  函数返回值 做了严格的检查
	//test3();
	//test5();
	//test6();
	test7();
	test8();
	return 0;
}