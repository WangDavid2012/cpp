#define _CRT_SECURE_NO_WARNINGS

#include "LinkList.h"
#include <stdlib.h>
#include <AccCtrl.h>


LinkList* Init_LinkList()
{
	LinkList *list = (LinkList *)malloc(sizeof(LinkList));
	list->head.next = NULL;
	list->size = 0;
	return list;
}
int Insert_LinkList(LinkList *list, int pos, LinkNode *data)
{
	if ((list == NULL) || (data == NULL)) {
		return -1;
	}

	if (pos <0 || pos > list->size) {
		pos = list->size;
	}
	LinkNode * pCurrent = &(list->head);
	for (int i = 0; i < pos; i++) {
		pCurrent = pCurrent->next;
	}
	data->next = pCurrent->next;
	pCurrent->next = data;
	list->size++;
	return 0;
}
int Remove_LinkList(LinkList *list, int pos)
{
	if ((list == NULL) || (pos < 0) || (pos >= list->size))
		return -1;
	//pCur 执行的是要删除元素的前一个元素
	LinkNode *pCur = &(list->head);
	for (int i = 0; i < pos; i++) {
		pCur = pCur->next;
	}

	//pCur->next = pCur->next->next;
	//或者
	LinkNode *pDel = pCur->next;
	pCur->next = pDel->next;
	// 	free(pDel);    //没有开辟内存空间，所以不用释放
	list->size--;
	return 0;
}
int Find_LinkList(LinkList *list, LinkNode *data, MYCOMPARE comparefun)
{
	if (list == NULL || data == NULL) {
		return -1;
	}
	LinkNode *pCur = &(list->head);
	int index = 0;
	for (int i = 0; i < list->size; i++) {
		//如果相等，则退出
		if (0 == comparefun(pCur->next, data)) {
			break;
		}
		pCur = pCur->next;
		index++;

	}
	if (index >= list->size)
		return -1;
	else
		return index;
}

void Print_LinkList(LinkList *list, MYPRINT print)
{
	LinkNode *pCur = &(list->head);
	for (int i = 0; i < list->size; i++) {
		pCur = pCur->next;
		print(pCur);
	}
}

void Free_LinkList(LinkList *list)
{
	if (list == NULL) {
		return;
	}
	free(list);
}










