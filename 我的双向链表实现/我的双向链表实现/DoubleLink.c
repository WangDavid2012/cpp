#include "DoubleLink.h"

DoubleLinkList * Init_DoubleLinkList()
{
    DoubleLinkList *dlist = (DoubleLinkList*)malloc(sizeof(DoubleLinkList));
    dlist->head.next = &(dlist->head);
    dlist->head.pre = &(dlist->head);
    dlist->size = 0;
    return dlist;
}

void Insert_DoubleLinkList(DoubleLinkList * dlist, int pos, DoubleLinkNode * pnew)
{
    if (dlist == NULL)
        return;
    if (pnew == NULL)
        return;
    if (pos > dlist->size)
        return;
    DoubleLinkNode *pCurrent = &(dlist->head);
    for (int i = 0; i < pos; i++)
    {
        pCurrent = pCurrent->next;
    }

    pnew->next = pCurrent->next;
    pCurrent->next->pre = pnew;
    pnew->pre = pCurrent;
    pCurrent->next = pnew;

    dlist->size++;
}

void Delete_DoubleLinkList(DoubleLinkList * dlist, int pos)
{
    if (dlist == NULL)
        return;
    if (pos >= dlist->size)
        return;
    DoubleLinkNode* pCurrent = &(dlist->head);
    for (int i = 0; i <= pos; i++)
        //for (int i = 0; i < pos; i++) ����
    {
        pCurrent = pCurrent->next;
    }
    pCurrent->next->pre = pCurrent->pre;
    pCurrent->pre->next = pCurrent->next;
    dlist->size--;

    //for (a; b; c)
    //    ִ��˳��
    //    ��ִ��a
    //    ���ж�b�Ƿ�Ϊ�棬��Ϊ��
    //    ִ��ѭ���壬
    //    ִ��c
    //    Ȼ���ٴ��ж�b�Ƿ�Ϊ�棬��Ϊ��
    //    ִ��ѭ����
    //    ִ��c
}

void DeleteByValue_DoubleLinkList(DoubleLinkList * dlist, DoubleLinkNode * data, DOUBLELINKCOMPARE compare)
{
    if (dlist == NULL)
        return;
    if (data == NULL)
        return;
    DoubleLinkNode* pCurrent = &(dlist->head);

    for (int i = 0; i < dlist->size; i++)
    {
        pCurrent = pCurrent->next;
        if (compare(pCurrent, data))
        {
            pCurrent->next->pre = pCurrent->pre;
            pCurrent->pre->next = pCurrent->next;
            dlist->size--;
            break;
        }
    }
}

DoubleLinkNode * Front_DoubleLinkList(DoubleLinkList * dlist)
{
    return dlist->head.next;
}

void Print_DoubleLinkList(DoubleLinkList * dlist, DOUBLELINKPRINT myprintf)
{
    DoubleLinkNode* pCurrent = &(dlist->head);
    for (int i = 0; i < dlist->size; i++)
    {
        pCurrent = pCurrent->next;
        myprintf(pCurrent);
    }
}
