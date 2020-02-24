
#pragma once


typedef struct LinkNode
{
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList
{
    LinkNode head;
    int size;
}LinkList;

//��������������ָ��
typedef void(*PRINTNODE)(LinkNode *);
typedef int(*COMPARENODE)(LinkNode *, LinkNode *);

//�����ʼ��
LinkList * initLinkList();
//����
void InsertLinkList(LinkList *list,unsigned int pos,LinkNode *data);
//ɾ������
void RemoveLinkList(LinkList *list, int pos);
//���������С
int Size_LinkList(LinkList *list);
//��ӡ����
void PrintLinkList(LinkList *list, PRINTNODE print);
//�ͷ������ڴ�
void FreeSpace_LinkList(LinkList *list);
//���ҽڵ�
int  FindLinkList(LinkList *list, LinkNode *data, COMPARENODE compare);
