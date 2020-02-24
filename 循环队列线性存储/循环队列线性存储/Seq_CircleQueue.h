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

//循环队列初始化
CircleQueue * Init_CircleQueue();


//判断队列是否是空，如果是空，返回1，否则返回0
int Empty_CircleQueue(CircleQueue* queue);

//判断队列是否是满，如果满，返回1，否则返回0
int Full_CircleQueue(CircleQueue* queue);


//入队操作
int Put_CircleQueue(CircleQueue *queue, void *data);

//出队操作
int Get_CircleQueue(CircleQueue* queue, void **data);