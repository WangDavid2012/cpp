#include <iostream>

using namespace std;

void func(int &a)
{
    a = 5;
}
void func(int *const a)
{
    *a = 5;
}

int getA1()
{
    int a;
    a = 10;
    return a;
}
int& getA2()
{
    int a;
    a = 10;
    return a;
}

int main()
{
    int a = 10;
	int &b = a;
	a = 11;

	int *p = &a;
	*p = 12;
	cout << a << endl;


	b = 14;
	cout << "a = " << a << ", b = " << b << endl;
    int x = 10;
    func(x);
    cout << "the x value is " << x << endl;

    int m1 = 0;
    int m2 = 0;

    m1 = getA1();
    //将一个引用，赋值给一个变量，会有拷贝的动作
    //理解：编译器类似做出了如下隐藏操作 m2 = *(getA2())
    m2 = getA2();
    //将引用赋值给另一个引用，由于是栈的操作，内存非法
    int &m3 = getA2();

    cout << "m1 = " << m1 << endl;
    cout << "m2 = " << m2 << endl;
    cout << "m3 = " << m3 << endl;


	getchar();
	return 0;

}


// 执行结果： 12    a=14,b=14


// 引用没有定义，是一种关系型声明。声明它和原有的某一个变量的关系，故而类型与原类型保持一致，
// 且不分配内存。与被引用的变量具有相同的地址
// 声明的时候必须初始化，一经声明，不可更改
// 重点：&符号前有数据类型时，是引用。其它皆为取地址。
// 引用的本质-----> 一个常量指针
// 可以如下描述：Type &name   等价于  type * const name
// C++ 编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同




