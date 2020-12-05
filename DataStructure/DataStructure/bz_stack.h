#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "common.h"



/**********************************************************
文件说明：
	bz开头的文件，是标准文件，是官方提供的数据结构实现方式，
	其他的文件，是自己写的实现方式
*************************************************************/


/*****************************************************
栈的相关知识：
	静态栈：静态栈的核心是数组，类似于一个连续的内存数组，我们只能操作其栈顶元素
	动态栈：动态栈的核心是数组，类似于一个连续的内存数组，我们只能操作其栈顶节点
******************************************************************/

/********************************************************/
//栈的基本操作：初始化，压栈，出栈，判空，遍历，清空
/*********************************************************/


//typedef struct _NODE {
//	int data;
//	struct _NODE *pNext;    //实质是指向的上一个节点
//}*PNODE,NODE;


typedef struct Stack {
	PNODE pTop;
	PNODE pBottom;
}STACK,*PSTACK;


/**栈的初始化*/
void init(PSTACK);
/**压栈*/
void push(PSTACK, int);
/**出栈*/
int pop(PSTACK, int *);
/**遍历打印栈*/
void traverse(PSTACK);
/**是否为空栈*/
int isEmpty(PSTACK);
/**清空栈*/
void clearStack(PSTACK);
void bz_stackTest();