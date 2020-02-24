#include <stdio.h>
#include <stdlib.h>
#include "Linklist.h"



//�����ʼ��
LinkList * initLinkList()
{
    LinkList *list = (LinkList*)malloc(sizeof(LinkList));
    list->head.next = NULL;
    list->size = 0;
    return list;
}
//����һ���ڵ�
// ����ķ�ʽ 0 1 2 3 ���pnew�ڵ����λ����0��������
// pnew 0 1 2 3------> pnew ����Ϊ�µ�0�Žڵ㣬�Ժ�Ľڵ�����1
// ɾ��ͬ�����
void InsertLinkList(LinkList * list, unsigned int pos, LinkNode * data)
{
    if (list == NULL)
    {
        printf("the linklist is null!\r\n");
        return;
    }
    if (data == NULL)
    {
        printf("the insert data is null!\r\n");
        return;
    }
    if (pos < 0 || pos > list->size)
    {
        
        pos = list->size;
        printf("the pos value is %d\n",pos);
        printf("the parameter is wrong!\r\n");

    }
    LinkNode *ptmp = &(list->head);
    for (int i = 0; i < pos; i++)
    {
        ptmp = ptmp->next;
    }
    data->next = ptmp->next;
    ptmp->next = data;
    list->size++;

}
//ɾ��һ���ڵ�
void RemoveLinkList(LinkList * list, int pos)
{
    if (pos<0 || pos >= list->size)
    {
        printf("error parameter!\r\n");
        return;
    }
        //return;
    LinkNode *pCurrent = &(list->head);
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }
    LinkNode *ptmp = pCurrent;
    pCurrent->next = pCurrent->next->next;
    list->size--;
    //free((void *)ptmp); ����Ҫ�ͷ��ڴ�
}

int Size_LinkList(LinkList * list)
{
    return list->size;
}

void PrintLinkList(LinkList * list, PRINTNODE print)
{
    if (list == NULL)
        return;
    LinkNode *pCurrent = &(list->head);

    for (int i = 0; i < list->size; i++)
    {
        pCurrent = pCurrent->next;
        print(pCurrent);
    }
}

void FreeSpace_LinkList(LinkList * list)
{
    if (list == NULL)
        return;
    free(list);
}



int FindLinkList(LinkList *list, LinkNode *data, COMPARENODE compare)
{
    int index = 0;
    LinkNode *pCurrent = list->head.next;
    while (pCurrent != NULL)
    {
        if (compare(pCurrent, data) == 0)
            break;
        pCurrent = pCurrent->next;
        index++;
    }
    return index;
}
