
#pragma once


typedef struct LinkNode
{
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList
{
    LinkNode head;
    int size;
}LinkList;

//定义了两个函数指针
typedef void(*PRINTNODE)(LinkNode *);
typedef int(*COMPARENODE)(LinkNode *, LinkNode *);

//链表初始化
LinkList * initLinkList();
//插入
void InsertLinkList(LinkList *list,unsigned int pos,LinkNode *data);
//删除操作
void RemoveLinkList(LinkList *list, int pos);
//返回链表大小
int Size_LinkList(LinkList *list);
//打印链表
void PrintLinkList(LinkList *list, PRINTNODE print);
//释放链表内存
void FreeSpace_LinkList(LinkList *list);
//查找节点
int  FindLinkList(LinkList *list, LinkNode *data, COMPARENODE compare);
