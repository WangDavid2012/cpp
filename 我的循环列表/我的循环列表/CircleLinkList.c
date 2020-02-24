#include <stdlib.h>
#include <stdio.h>

#include "CircleLinkList.h"


//初始化循环列表
CircleLinkList * Init_CircleLinkList()
{
    CircleLinkList *clist = (CircleLinkList*)malloc(sizeof(CircleLinkList));
    clist->head.next = &(clist->head);
    clist->size = 0;
    return clist;
}

void Insert_CircleLinkList(CircleLinkList * clist, int pos, CircleLinkNode * data)
{
    if (clist == NULL)
        return;
    if (pos < 0 || pos >= clist->size)
        pos = clist->size;

    CircleLinkNode *pCurrent = &(clist->head);
    //找到插入位置的前一个位置
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;  
    }
    //插入操作
    data->next = pCurrent->next;
    pCurrent->next = data;
    clist->size++;
}

CircleLinkNode * Front_CircleLinkList(CircleLinkList * clist)
{
    CircleLinkNode *ptmp = clist->head.next;
    return ptmp;
}
//根据位置，删除一个节点
void RemoveByPos_CircleLinkList(CircleLinkList * clist, int pos)
{
    if (clist == NULL)
        return;
    if (pos < 0 || pos >= clist->size)
        return;
    CircleLinkNode *pCurrent = &(clist->head);
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pCurrent->next->next;
    clist->size--;

}
//根据值，删除一个节点,返回删除节点的位置
int RemoveByValue_CircleLinkList(CircleLinkList * clist, CircleLinkNode * data, COMPARENODE compare)
{
    if (clist == NULL)
        return;
    if (data == NULL)
        return;
    CircleLinkNode *pCurrent = clist->head.next;
    int flag = -1;

    for (int i = 0; i < clist->size; i++)
    {
        if (compare(pCurrent, data) == 0)
        {
            pCurrent->next = pCurrent->next->next;
            flag = i;
            clist->size--;
            break;
        }
        pCurrent = pCurrent->next;
    }

    return flag;
}

int Size_CircleLinkList(CircleLinkList * clist)
{
    return clist->size;
}

int Find_CircleLinkList(CircleLinkList * clist, CircleLinkNode * data, COMPARENODE compare)
{
    int flag = -1;
    if (clist == NULL)
        return -1;
    if (data == NULL)
        return -1;

    CircleLinkNode *pCurrent = clist->head.next;

    for (int i = 0; i < clist->size; i++)
    {
        if (!compare(pCurrent, data))
        {
            flag = i;
            break;
        }
        pCurrent = pCurrent->next;

    }
    return flag;
}
//打印两遍，用于测试循环链表
void Print_CircleLinkList(CircleLinkList * clist, PRINTNODE print)
{
    if (clist == NULL)
        return;
    CircleLinkNode *pCurrent = &(clist->head);
    for (int i = 0; i < (clist->size) ; i++)
    {
        pCurrent = pCurrent->next;
        print(pCurrent);
    }
}

void Free_CircleLinkList(CircleLinkList * clist)
{
    if (clist == NULL)
        return;
    free(clist);
}
    