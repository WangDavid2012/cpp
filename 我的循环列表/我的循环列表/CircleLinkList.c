#include <stdlib.h>
#include <stdio.h>

#include "CircleLinkList.h"


//��ʼ��ѭ���б�
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
    //�ҵ�����λ�õ�ǰһ��λ��
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;  
    }
    //�������
    data->next = pCurrent->next;
    pCurrent->next = data;
    clist->size++;
}

CircleLinkNode * Front_CircleLinkList(CircleLinkList * clist)
{
    CircleLinkNode *ptmp = clist->head.next;
    return ptmp;
}
//����λ�ã�ɾ��һ���ڵ�
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
//����ֵ��ɾ��һ���ڵ�,����ɾ���ڵ��λ��
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
//��ӡ���飬���ڲ���ѭ������
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
    