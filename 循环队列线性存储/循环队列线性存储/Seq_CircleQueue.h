#pragma once


#include <stdlib.h>
#include <stdio.h>


#define MAXSIZE 10
typedef struct CircleQueue
{
    void* data[MAXSIZE];
    int front;
    int rear;
    int size;
}CircleQueue;

//ѭ�����г�ʼ��
CircleQueue * Init_CircleQueue();


//�ж϶����Ƿ��ǿգ�����ǿգ�����1�����򷵻�0
int Empty_CircleQueue(CircleQueue* queue);

//�ж϶����Ƿ������������������1�����򷵻�0
int Full_CircleQueue(CircleQueue* queue);


//��Ӳ���
int Put_CircleQueue(CircleQueue *queue, void *data);

//���Ӳ���
int Get_CircleQueue(CircleQueue* queue, void **data);