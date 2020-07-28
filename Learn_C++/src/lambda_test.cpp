/***********************************************************************
ISO C++ 11 标准的一大亮点是引入Lambda表达式。基本语法如下：
[capture list] (parameter list) ->return type { function body }

简单的讲一下各个部分的作用
1.[capture list]捕获列表，捕获到函数体中，使得函数体可以访问
2.(parameter list)参数列表，用来表示lambda表达式的参数列表
3.->return type函数返回值 {function body}就是函数体

lambda表达式可以理解为一个匿名函数（但本质并不是），如果要使用lambda表达式声明的函数，需要给他“命名”

lambda表达式可以表示闭包，因为本身就是这个类
闭包是指可以包含自由变量的代码块 （未绑定到特定的对象：举个std::function就可以产生一个对象，或者一个未指向任何函数的函数指针）
闭包讲的通俗一些有以下几点
1.自带上下文的函数，闭包可以储存运行时需要的上下文，这样就可以在上下文不存在的时候还可以使用闭包（变量a生命周期到了被销毁，但是在闭包中还可以拿来用）
2.可以把闭包看成一个重载了operator()的类，带有状态的意思就可以解释成通过this指针使用成员变量
3.capture list就是lambda表达式实现闭包的方式
*************************************************************************************/
#include<iostream>
using namespace std;

void lambda_test0()
{
	int a = 1;
	int b = 2;

	auto func = [=, &b](int c)->int {return b += a + c; };
	cout << "the b: " << b << endl;
	cout << endl;
}
