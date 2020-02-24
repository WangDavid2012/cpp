#pragma once



typedef struct CIRCLELINKNODE
{
    struct CIRCLELINKNODE *next;
}CircleLinkNode;
typedef struct CIRCLELINKLIST
{
    CircleLinkNode head;
    int size;
}CircleLinkList;

typedef int(*COMPARENODE)(CircleLinkNode *, CircleLinkNode *);
typedef int(*PRINTNODE)(CircleLinkNode *);

//API �ӿں���
//��ʼ������
CircleLinkList * Init_CircleLinkList();
//��������
void Insert_CircleLinkList(CircleLinkList *clist,int pos,CircleLinkNode *data);

//��õ�һ��Ԫ��
CircleLinkNode * Front_CircleLinkList(CircleLinkList *clist);

//����λ��ɾ��
void RemoveByPos_CircleLinkList(CircleLinkList *clist,int pos);
//����ֵɾ��
int RemoveByValue_CircleLinkList(CircleLinkList *clist,CircleLinkNode *data, COMPARENODE compare);

int Size_CircleLinkList(CircleLinkList *clist);

int Find_CircleLinkList(CircleLinkList *clist, CircleLinkNode *data, COMPARENODE compare);

void Print_CircleLinkList(CircleLinkList *clist,PRINTNODE print);

void Free_CircleLinkList(CircleLinkList *clist);




