#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "MyArray.h"

using namespace std;

int main(void)
{
	MyArray array1(10); //调用MyArray 有参数构造函数


	//设置一个数组的所有元素
	for (int i = 0; i< array1.getLen(); i++) {
		array1.setData(i, i + 10);
	}

	cout << " -------- " << endl;

	//遍历一个数组的所有元素
	for (int i = 0; i < array1.getLen(); i++)  {
		cout << array1.getData(i) << endl;
	}

	cout << " ---一下是拷贝构造函数测试----" << endl;
	MyArray array2 = array1; //调用了array2的拷贝构造函数

	for (int i = 0; i < array2.getLen(); i++) {
		cout << array2.getData(i) << endl;
	}
	
	return 0;
}