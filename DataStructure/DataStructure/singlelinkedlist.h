#pragma once
#include <stdio.h>

/****************************************************************
ADT:
	1������ĳ�ʼ��
	2���������в�������
	3��������ȡ������
	4����������������
*****************************************************************/
typedef int ElemType;

//���������� 
typedef struct Node {
	ElemType data;              //�������е������� 
	struct Node *next;          //�������ָ���� 
}s_Node, *pLinkedList;


void SingleLinkedList_Test(void);