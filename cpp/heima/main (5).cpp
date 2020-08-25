#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "MyArray.h"

using namespace std;

int main(void)
{
	MyArray array1(10); //调用MyArray 有参数构造函数


	//设置一个数组的所有元素
	for (int i = 0; i< array1.getLen(); i++) {
		//array1.setData(i, i + 10);
		//array1.setData(0, 10); //给数组第一个元素设置为10
		array1[i] = i + 10;//通过【】 操作符 进行赋值
	}

	cout << " -----  [] 操作符 测试 --- " << endl;

	//遍历一个数组的所有元素
	/*
	for (int i = 0; i < array1.getLen(); i++)  {
		//cout << array1.getData(i) << endl;
		cout << array1[i] << endl;
		//array[i] == array1.getDate(i);
	}
	*/

	cout << array1 << endl;
	

	cout << " ---一下是拷贝构造函数测试----" << endl;
	MyArray array2 = array1; //调用了array2的拷贝构造函数

	/*
	for (int i = 0; i < array2.getLen(); i++) {
		cout << array2.getData(i) << endl;
	}
	*/

	cout << array2 << endl;


	cout << " -------array 3----" << endl;

	MyArray array3(5);

	cin >> array3;

	cout << array3;

	//array3 = array2; //调用array3的=, array3.operator=(array2);
	cout << "---- array 3 = array2  ----- " << endl;

	cout << array3;


	if (array3 == array2)
	{
		cout << "array 3 == array 2" << endl;
	}

	if (array3 != array2)
	{
		cout << "array 3 != array 2" << endl;
	}
	else {
		cout << "array 3 == array 2" << endl;
	}
	
	return 0;
}