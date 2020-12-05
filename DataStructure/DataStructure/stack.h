#pragma once
#include <stdio.h>



//明确一下stack需要用到的结构体
//开辟栈空间，长度可变
//栈空间的栈顶位置
typedef struct _STACK
{
	int *pbase;
	int lenth;
	int *ptop;
}s_Stack;

void StackTest(void);