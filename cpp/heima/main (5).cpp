#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "MyArray.h"

using namespace std;

int main(void)
{
	MyArray array1(10); //����MyArray �в������캯��


	//����һ�����������Ԫ��
	for (int i = 0; i< array1.getLen(); i++) {
		//array1.setData(i, i + 10);
		//array1.setData(0, 10); //�������һ��Ԫ������Ϊ10
		array1[i] = i + 10;//ͨ������ ������ ���и�ֵ
	}

	cout << " -----  [] ������ ���� --- " << endl;

	//����һ�����������Ԫ��
	/*
	for (int i = 0; i < array1.getLen(); i++)  {
		//cout << array1.getData(i) << endl;
		cout << array1[i] << endl;
		//array[i] == array1.getDate(i);
	}
	*/

	cout << array1 << endl;
	

	cout << " ---һ���ǿ������캯������----" << endl;
	MyArray array2 = array1; //������array2�Ŀ������캯��

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

	//array3 = array2; //����array3��=, array3.operator=(array2);
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