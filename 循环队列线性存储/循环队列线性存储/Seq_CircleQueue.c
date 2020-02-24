#include "Seq_CircleQueue.h"

CircleQueue * Init_CircleQueue()
{
    CircleQueue *queue = (CircleQueue*)malloc(sizeof(CircleQueue));
    queue->size = 0;
    queue->front = queue->rear = 0;
    return queue;
}


int Empty_CircleQueue(CircleQueue * queue)
{
    if (queue->front == queue->rear)
        return 1;
    return 0;
}

int Full_CircleQueue(CircleQueue * queue)
{
    if ((queue->rear + 1) % MAXSIZE == queue->front)
        return 1;
    return 0;
}

int Put_CircleQueue(CircleQueue * queue, void * data)
{
    if (Full_CircleQueue(queue))
        return -1;
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return queue->size++;
}

int Get_CircleQueue(CircleQueue * queue, void ** data)
{
    if (Empty_CircleQueue(queue))
        return -1;
    *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    return --queue->size;
    //return queue->size--;  //注意这种返回方式不对
}
