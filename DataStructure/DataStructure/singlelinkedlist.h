#pragma once
#include <stdio.h>

/****************************************************************
ADT:
	1、链表的初始化
	2、向链表中插入数据
	3、链表中取出数据
	4、链表中数据排序
*****************************************************************/
typedef int ElemType;

//定义结点类型 
typedef struct Node {
	ElemType data;              //单链表中的数据域 
	struct Node *next;          //单链表的指针域 
}s_Node, *pLinkedList;


void SingleLinkedList_Test(void);