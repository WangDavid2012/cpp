//moduleB头文件
#ifndef __MODULE_B_H //很明显这一部分也是为了防止重复引用
#define __MODULE_B_H


//而这一部分就是告诉编译器，如果定义了__cplusplus
// (即如果是cpp文件， extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#ifdef __cplusplus 
extern "C" {
#endif
//告诉编译器，下面的代码以C语言的方式进行编译
//如果将 extern "C" 注释掉，编译会报错

#include"moduleA.h"

#ifdef __cplusplus
}
#endif

#endif

/***************************************************************
extern "C"的使用要点总结

1，可以是如下的单一语句：
extern "C" double sqrt(double);

2，可以是复合语句, 相当于复合语句中的声明都加了extern "C"
extern "C"
{
	double sqrt(double);
	int min(int, int);
}

3，可以包含头文件，相当于头文件中的声明都加了extern "C"
extern "C"
{
	＃include <cmath>
}
不可以将extern "C" 添加在函数内部
如果函数有多个声明，可以都加extern "C", 也可以只出现在第一次声明中，后面的声明会接受第一个链接指示符的规则。
除extern "C", 还有extern "FORTRAN" 等。
*************************************************************/