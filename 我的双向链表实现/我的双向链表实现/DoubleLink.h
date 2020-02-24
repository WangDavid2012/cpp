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

//双向链表初始化
DoubleLinkList * Init_DoubleLinkList();

//插入节点操作
void Insert_DoubleLinkList(DoubleLinkList *dlist,int pos,DoubleLinkNode *node);

//删除节点操作,按照位置删除
void Delete_DoubleLinkList(DoubleLinkList* dlist,int pos);
void DeleteByValue_DoubleLinkList(DoubleLinkList* dlist,DoubleLinkNode *data, DOUBLELINKCOMPARE compare);

//返回首节点
DoubleLinkNode* Front_DoubleLinkList(DoubleLinkList* dlist);

//打印双向链表中每个元素
void Print_DoubleLinkList(DoubleLinkList* dlist,DOUBLELINKPRINT printf);







