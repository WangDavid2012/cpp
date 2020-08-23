#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "LinkList.h"
#include "debug.h"


LinkList* Init_LinkList()
{
	LinkList *list = (LinkList *)malloc(sizeof(LinkList));
	list->head.next = nullptr;
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
	++list->size;
	return 0;
}
int Remove_LinkList(LinkList *list, int pos)
{
	if ((list == NULL) || (pos < 0) || (pos >= list->size))
		return -1;
	//pCur ִ�е���Ҫɾ��Ԫ�ص�ǰһ��Ԫ��
	LinkNode *pCur = &(list->head);
	for (int i = 0; i < pos; i++) {
		pCur = pCur->next;
	}

	//pCur->next = pCur->next->next;
	
	LinkNode *pDel = pCur->next;
	pCur->next = pDel->next;    
	--list->size;
	return 0;
}
int Find_LinkList(LinkList *list, LinkNode *data, MYCOMPARE comparefun)
{
	if (list == NULL || data == NULL) {
		return -1;
	}
	mydebug << "The list size is :" << list->size << endl;
	LinkNode *pCur = &(list->head);
	int index = 0;
	for (int i = 0; i < list->size; i++) {
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










