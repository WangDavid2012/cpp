#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;



//注意!!!!!!!!!!!!!!!!!!!
//建立链表数据结构时，链表和NODE节点其实是一样的，一个链表
//需要一个头指针既可以，头指针指向头结点
//定义结点类型 
typedef struct Node {
	ElemType data;              //单链表中的数据域 
	struct Node *next;          //单链表的指针域 
}Node, *LinkedList;



/**********************************************************
单链表的初始化，建立一个单链表，只含有一个元素，即头结点，头结点的数据域是0，
指针域指向空
time:2018-09-19
author:david
***********************************************************/
LinkedList LinkedListInit() 
{
	Node *L;
	L = (Node *)malloc(sizeof(Node));   //申请结点空间 
	if (L == NULL) {                    //判断是否有足够的内存空间 
		printf("申请内存空间失败\n");
	}
	L->data = 0;                         //头结点的数据域可以用于表示链表的长度
	L->next = NULL;                      //将next设置为NULL,初始长度为0的单链表 
	return L;
}


//单链表的建立1，头插法建立单链表
LinkedList LinkedListCreatH() 
{
	Node *L;
	L = (Node *)malloc(sizeof(Node));       //申请头结点空间
	L->next = NULL;                         //初始化一个空链表

	ElemType x;                             //x为链表数据域中的数据
	while (scanf_s("%d", &x) != EOF) {
		Node *p;
		p = (Node *)malloc(sizeof(Node));   //申请新的结点 
		p->data = x;                        //结点数据域赋值 
		p->next = L->next;                  //将结点插入到表头L-->|2|-->|1|-->NULL 
		L->next = p;
	}
	return L;
}


//单链表的建立2，尾插法建立单链表
LinkedList LinkedListCreatT() 
{
	Node *L;
	L = (Node *)malloc(sizeof(Node));   //申请头结点空间
	L->next = NULL;                     //初始化一个空链表
	Node *r;
	r = L;                              //r始终指向终端结点，开始时指向头结点 
	ElemType x;                         //x为链表数据域中的数据
	while (scanf_s("%d", &x) != EOF) {
		Node *p;
		p = (Node *)malloc(sizeof(Node));   //申请新的结点 
		p->data = x;                        //结点数据域赋值 
		r->next = p;                        //将结点插入到表头L-->|1|-->|2|-->NULL 
		r = p;
	}
	r->next = NULL;

	return L;
}


//单链表的插入，在链表的第i个位置插入x的元素
//i的取值范围 1 <= i < lenth 链表长度 
LinkedList LinkedListInsert(LinkedList L, int i, ElemType x) 
{
	Node *pre;                           //pre为前驱结点 
	pre = L;
	int tempi = 0;
	for (tempi = 1; tempi < i; tempi++) 
	{
		pre = pre->next;                 //查找第i个位置的前驱结点 
	}
	Node *p;                             //插入的结点为p
	p = (Node *)malloc(sizeof(Node));
	p->data = x;
	p->next = pre->next;
	pre->next = p;

	return L;
}


//单链表的删除，在链表中删除值为x的元素
LinkedList LinkedListDelete(LinkedList L, ElemType x)
{
	Node *p, *pre;                      //pre为前驱结点，p为查找的结点。 
	p = L->next;
	while (p->data != x) {              //查找值为x的元素 
		pre = p;
		p = p->next;
	}
	//pre->next = p->next;                //删除操作，将其前驱next指向其后继。 
	free(p);
	return L;
}


void LinkList_Test()
{
	LinkedList list, start;
	printf("请输入单链表的数据：");
	list = LinkedListCreatH();
	for (start = list->next; start != NULL; start = start->next) {
		printf("%d ", start->data);
	}
	printf("\n");
	int i;
	ElemType x;
	printf("请输入插入数据的位置：");
	scanf_s("%d", &i);
	printf("请输入插入数据的值：");
	scanf_s("%d", &x);
	LinkedListInsert(list, i, x);
	for (start = list->next; start != NULL; start = start->next) {
		printf("%d ", start->data);
	}
	printf("\n");
	printf("请输入要删除的元素的值：");
	scanf_s("%d", &x);
	LinkedListDelete(list, x);
	for (start = list->next; start != NULL; start = start->next) {
		printf("%d ", start->data);
	}
	printf("\n");


}