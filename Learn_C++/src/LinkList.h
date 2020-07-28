#pragma once

typedef struct _LINKNODE
{
	struct _LINKNODE *next;
}LinkNode;

typedef struct _LINKLIST
{
	LinkNode head;
	int size;
}LinkList;

typedef void(*MYPRINT)(LinkNode *);
typedef int(*MYCOMPARE)(LinkNode *, LinkNode *);

LinkList* Init_LinkList();
int Insert_LinkList(LinkList *list, int pos, LinkNode *data);
int Remove_LinkList(LinkList *list, int pos);
int Find_LinkList(LinkList *list, LinkNode *data, MYCOMPARE comparefun);
void Print_LinkList(LinkList *list, MYPRINT print);
int Size_LinkList(LinkList *list);
void Free_LinkList(LinkList *list);
