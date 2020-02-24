#pragma once

#include <stdio.h>
#include <stdlib.h>


//ջ����ʽ�洢�� ���ݽṹ����
typedef struct StackNode
{
    struct StackNode* next;
}StackNode;


typedef struct LinkStack
{
    StackNode head;
    int size;
}LinkStack;

LinkStack* Init_LinkStack();

//push����
void Push_LinkStack(LinkStack *stack,StackNode *node);

//pop ����
int Pop_LinkStack(LinkStack* stack,StackNode **node);

int Size_LinkStack(LinkStack* stack);

void Free_LinkStack(LinkStack* stack);

