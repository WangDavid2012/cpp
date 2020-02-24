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

//API 接口函数
//初始化函数
CircleLinkList * Init_CircleLinkList();
//插入数据
void Insert_CircleLinkList(CircleLinkList *clist,int pos,CircleLinkNode *data);

//获得第一个元素
CircleLinkNode * Front_CircleLinkList(CircleLinkList *clist);

//根据位置删除
void RemoveByPos_CircleLinkList(CircleLinkList *clist,int pos);
//根据值删除
int RemoveByValue_CircleLinkList(CircleLinkList *clist,CircleLinkNode *data, COMPARENODE compare);

int Size_CircleLinkList(CircleLinkList *clist);

int Find_CircleLinkList(CircleLinkList *clist, CircleLinkNode *data, COMPARENODE compare);

void Print_CircleLinkList(CircleLinkList *clist,PRINTNODE print);

void Free_CircleLinkList(CircleLinkList *clist);




