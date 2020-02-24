#pragma once

#include <stdio.h>
#include <stdlib.h>


//栈的链式存储的 数据结构定义
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

//push操作
void Push_LinkStack(LinkStack *stack,StackNode *node);

//pop 操作
int Pop_LinkStack(LinkStack* stack,StackNode **node);

int Size_LinkStack(LinkStack* stack);

void Free_LinkStack(LinkStack* stack);

