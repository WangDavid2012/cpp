#pragma once
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 1024

typedef struct SeqStack
{
    void* data[MAXSIZE];
    int size;
}SeqStack;


//顺序栈初始化
SeqStack * Init_SeqStack();

//入栈操作
void Push_SeqStack(SeqStack *stack,void *data);

//出栈操作
int Pop_SeqStack(SeqStack* stack);

//栈顶元素
void *Front_SeqStack(SeqStack* stack);

//返回栈中元素个数
int Size_SeqStack(SeqStack* stack);

//遍历栈中元素

int PosAndStore_SeqStack(SeqStack *stack,void ** data);

void Free_SeqStack(SeqStack *stack);



