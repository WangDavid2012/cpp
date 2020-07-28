//此文件中链表操作有错误，目前还没有查找出来原因 2018-09-19

#include<stdio.h>
#include "stdlib.h"
#include "singlelinkedlist.h"

//单链表的初始化
//pLinkedList LinkedListInit() {
//	s_Node *L;
//	L = (s_Node *)malloc(sizeof(s_Node));   //申请结点空间 
//	if (L == NULL) {                        //判断是否有足够的内存空间 
//		printf("申请内存空间失败\n");
//	}
//	L->next = NULL;                         //将next设置为NULL,初始长度为0的单链表 
//	return L;
//}




void InseartData(pLinkedList pList, int data)
{
	
	s_Node *ptmpNode = pList->next;    //定义头指针指向第一个节点（头结点的后面一个节点）
	s_Node *pnode;
	while (ptmpNode != NULL)
	{
		ptmpNode = pList->next;
	}
	pnode = (s_Node *)malloc(sizeof(s_Node));
	if (pnode == NULL)
		printf("malloc Node failed!\n");
	else
	{
		pnode->data = data;
		pnode->next = NULL;
		
		ptmpNode = pnode;
	}
}


void PrintfLinkData(pLinkedList pList)
{
	s_Node *ptmp = pList->next;
	while (ptmp)
	{
		printf("The Value is %d\n",ptmp->data);
		ptmp = pList->next->next;
	}

	printf("printf finish!\n");
}


void SingleLinkedList_Test()
{

	//pLinkedList pList = LinkedListInit();
	//InseartData(pList,1);
	//InseartData(pList, 2);
	//InseartData(pList, 3);
	//InseartData(pList, 4);
	//InseartData(pList, 5);
	//InseartData(pList, 6);
	//InseartData(pList, 7);
	//InseartData(pList, 8);
	//InseartData(pList, 9);
	//PrintfLinkData(pList);


}


