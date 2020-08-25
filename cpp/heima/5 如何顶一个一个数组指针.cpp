#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//如何顶一个一个数组指针

//方法一
//定义一个数组类型
typedef int(ARRAY_INT_10_TYPE)[10];

//方法二
//直接定义一种数组指针
typedef int(*ARRAY_INT_10_TYPE_POINTER)[10];

int main(void)
{
	int array[10];
	ARRAY_INT_10_TYPE array2;
	ARRAY_INT_10_TYPE * array_p = NULL; //指向数组类型的指针
	ARRAY_INT_10_TYPE_POINTER array_p3 = NULL;

	*array; // 数组第一个元素  int ， array是数组的名字，首元素的地址
			  //是一个 存放int数组的第一个元素。
	*array_p;//是一个存放数组（int[10]）的数组的第一个元素。

	for (int i = 0; i < 10; i++) {
		(*array_p)[i] = 10;
	}

	for (int i = 0; i < 10; i++) {
		array[i] = 10;
		array2[i] = 10;
	}
	
	return 0;
}