#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Complext.h"
#include "Complext.hpp" //���ܹ�����cpp
#include <vector>

//ģ����� ������ʵ�ֲ��ܹ��ö��ļ���д��
//���ʵ�ֶ��ļ��� ���ڶ��α��� ������ʵ��������cpp�ļ�����ġ���Ҫ����cppͷ�ļ���

using namespace std;



int main(void)
{
	
	Complex<int> c1(10, 20);
	c1.pirntComplex();

	Complex<int> c2(1, 2);

	Complex<int> c3; //�����޲ι���
	c3 = c1 + c2;

	c3.pirntComplex();

	return 0;
}