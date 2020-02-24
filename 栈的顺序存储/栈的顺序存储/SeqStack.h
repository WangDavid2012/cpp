#pragma once
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 1024

typedef struct SeqStack
{
    void* data[MAXSIZE];
    int size;
}SeqStack;


//˳��ջ��ʼ��
SeqStack * Init_SeqStack();

//��ջ����
void Push_SeqStack(SeqStack *stack,void *data);

//��ջ����
int Pop_SeqStack(SeqStack* stack);

//ջ��Ԫ��
void *Front_SeqStack(SeqStack* stack);

//����ջ��Ԫ�ظ���
int Size_SeqStack(SeqStack* stack);

//����ջ��Ԫ��

int PosAndStore_SeqStack(SeqStack *stack,void ** data);

void Free_SeqStack(SeqStack *stack);



