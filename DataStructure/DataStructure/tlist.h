#pragma once


// tinyOS链表的结点类型
typedef struct _tNode
{
	// 该结点的前一个结点
	struct _tNode * preNode;
	// 该结点的后一个结点
	struct _tNode * nextNode;
}tNode;




// tinyOS链表类型
typedef struct _tList
{
	// 该链表的头结点
	tNode headNode;

	// 该链表中所有结点数量
	int nodeCount;
}tList;



typedef struct _tTask
{
	int prio;
	tNode delayNode;
	int state;
}tTask;






void tNodeInit(tNode * node);

/**********************************************************************************************************
** Function name        :   tNodeParent
** Descriptions         :   获取结点所在的父struct结构首地址
** parameters           :   无
** Returned value       :   父struct结构首地址
***********************************************************************************************************/
#define tNodeParent(node, parent, name) (parent *)((int)node - (int)&((parent *)0)->name)

/**********************************************************************************************************
** Function name        :   tListInit
** Descriptions         :   链表初始化
** parameters           :   无
** Returned value       :   无
***********************************************************************************************************/
void tListInit(tList * list);

/**********************************************************************************************************
** Function name        :   tListCount
** Descriptions         :   返回链表中结点的数量
** parameters           :   无
** Returned value       :   结点数量
***********************************************************************************************************/
int tListCount(tList * list);

/**********************************************************************************************************
** Function name        :   tListFirst
** Descriptions         :   返回链表的首个结点
** parameters           :   list 查询的链表
** Returned value       :   首个结点，如果链表为空，则返回0
***********************************************************************************************************/
tNode * tListFirst(tList * list);

/**********************************************************************************************************
** Function name        :   tListLast
** Descriptions         :   返回链表的最后一个结点
** parameters           :   list 查询的链表
** Returned value       :   最后的结点，如果链表为空，则返回0
***********************************************************************************************************/
tNode * tListLast(tList * list);

/**********************************************************************************************************
** Function name        :   tListPre
** Descriptions         :   返回链表中指定结点的前一结点
** parameters           :   list 查询的链表
** parameters           :   node 参考结点
** Returned value       :   前一结点结点，如果结点没有前结点（链表为空），则返回0
***********************************************************************************************************/
tNode * tListPre(tList * list, tNode * node);

/**********************************************************************************************************
** Function name        :   tListNext
** Descriptions         :   返回链表中指定结点的后一结点
** parameters           :   list 查询的链表
** parameters           :   node 参考结点
** Returned value       :   后一结点结点，如果结点没有前结点（链表为空），则返回0
***********************************************************************************************************/
tNode * tListNext(tList * list, tNode * node);

/**********************************************************************************************************
** Function name        :   tListRemoveAll
** Descriptions         :   移除链表中的所有结点
** parameters           :   list 待清空的链表
** Returned value       :   无
***********************************************************************************************************/
void tListRemoveAll(tList * list);

/**********************************************************************************************************
** Function name        :   tListAddFirst
** Descriptions         :   将指定结点添加到链表的头部
** parameters           :   list 待插入链表
** parameters			:   node 待插入的结点
** Returned value       :   无
***********************************************************************************************************/
void tListAddFirst(tList * list, tNode * node);

/**********************************************************************************************************
** Function name        :   tListAddLast
** Descriptions         :   将指定结点添加到链表的末尾
** parameters           :   list 待插入链表
** parameters			:   node 待插入的结点
** Returned value       :   无
***********************************************************************************************************/
void tListAddLast(tList * list, tNode * node);

/**********************************************************************************************************
** Function name        :   tListRemoveFirst
** Descriptions         :   移除链表中的第1个结点
** parameters           :   list 待移除链表
** Returned value       :   如果链表为空，返回0，否则的话，返回第1个结点
***********************************************************************************************************/
tNode * tListRemoveFirst(tList * list);

/**********************************************************************************************************
** Function name        :   tListInsertAfter
** Descriptions         :   将指定的结点插入到某个结点后面
** parameters           :   list 			待插入的链表
** parameters           :   nodeAfter 		参考结点
** parameters           :   nodeToInsert 	待插入的结构
** Returned value       :   无
***********************************************************************************************************/
void tListInsertAfter(tList * list, tNode * nodeAfter, tNode * nodeToInsert);

/**********************************************************************************************************
** Function name        :   tListRemove
** Descriptions         :   将指定结点从链表中移除
** parameters           :   list 	待移除的链表
** parameters           :   node 	待移除的结点
** Returned value       :   无
***********************************************************************************************************/
void tListRemove(tList * list, tNode * node);



void ParentNodeAddr_Test();
