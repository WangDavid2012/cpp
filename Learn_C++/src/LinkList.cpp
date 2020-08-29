<<<<<<< HEAD
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
	//pCur Ö´ÐÐµÄÊÇÒªÉ¾³ýÔªËØµÄÇ°Ò»¸öÔªËØ
	LinkNode *pCur = &(list->head);
	for (int i = 0; i < pos; i++) {
		pCur = pCur->next;
	}

	//pCur->next = pCur->next->next;
	//»òÕß
	LinkNode *pDel = pCur->next;
	pCur->next = pDel->next;
	// 	free(pDel);    //Ã»ÓÐ¿ª±ÙÄÚ´æ¿Õ¼ä£¬ËùÒÔ²»ÓÃÊÍ·Å
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
		//Èç¹ûÏàµÈ£¬ÔòÍË³ö
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










=======
ï»¿#define _CRT_SECURE_NO_WARNINGS

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
	//pCur æ‰§è¡Œçš„æ˜¯è¦åˆ é™¤å…ƒç´ çš„å‰ä¸€ä¸ªå…ƒç´ 
	LinkNode *pCur = &(list->head);
	for (int i = 0; i < pos; i++) {
		pCur = pCur->next;
	}

	//pCur->next = pCur->next->next;
	//æˆ–è€…
	LinkNode *pDel = pCur->next;
	pCur->next = pDel->next;
	// 	free(pDel);    //æ²¡æœ‰å¼€è¾Ÿå†…å­˜ç©ºé—´ï¼Œæ‰€ä»¥ä¸ç”¨é‡Šæ”¾
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
		//å¦‚æžœç›¸ç­‰ï¼Œåˆ™é€€å‡º
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
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
