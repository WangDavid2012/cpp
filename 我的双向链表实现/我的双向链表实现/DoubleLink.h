#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef struct DoubleLinkNode
{
    struct DoubleLinkNode *pre;
    struct DoubleLinkNode *next;
}DoubleLinkNode;

typedef struct DoubleLinkList
{
    DoubleLinkNode head;
    int size;
}DoubleLinkList;

typedef void(*DOUBLELINKPRINT)(DoubleLinkNode *);
typedef int(*DOUBLELINKCOMPARE)(DoubleLinkNode *, DoubleLinkNode *);

//˫�������ʼ��
DoubleLinkList * Init_DoubleLinkList();

//����ڵ����
void Insert_DoubleLinkList(DoubleLinkList *dlist,int pos,DoubleLinkNode *node);

//ɾ���ڵ����,����λ��ɾ��
void Delete_DoubleLinkList(DoubleLinkList* dlist,int pos);
void DeleteByValue_DoubleLinkList(DoubleLinkList* dlist,DoubleLinkNode *data, DOUBLELINKCOMPARE compare);

//�����׽ڵ�
DoubleLinkNode* Front_DoubleLinkList(DoubleLinkList* dlist);

//��ӡ˫��������ÿ��Ԫ��
void Print_DoubleLinkList(DoubleLinkList* dlist,DOUBLELINKPRINT printf);







