#pragma once
#include <stdio.h>



//��ȷһ��stack��Ҫ�õ��Ľṹ��
//����ջ�ռ䣬���ȿɱ�
//ջ�ռ��ջ��λ��
typedef struct _STACK
{
	int *pbase;
	int lenth;
	int *ptop;
}s_Stack;

void StackTest(void);