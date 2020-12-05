#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


void QueueInit(sQueue *queue)
{
	queue->lenth = 0;
	queue->front = queue->rear = 0;
}


//ע���ж϶����Ƿ�����������
//(queue->front + 1) % SIZE == queue->rear ? 1 : 0;   //�����
int QueueIsFull(sQueue *queue)
{
	return (queue->rear + 1) % SIZE == queue->front ? 1:0;
	//if ((queue->rear + 1) % SIZE == queue->front)
	//	return 1;
	//else
	//	return 0;
}

int QueueIsEmpty(sQueue *queue)
{
	return queue->front == queue->rear ? 1 : 0;
}

int PutQueue(sQueue *queue,unsigned int data)
{
	if (QueueIsFull(queue))
	{
		printf("The queue is full!\n");
		return 0;
	}
		
	
	queue->data[queue->rear] = data;
	queue->rear = (queue->rear + 1) % SIZE;
	queue->lenth++;
	return 1;
}



//����ֵ������ô���������鿴������������ʽ
int GetQueue(sQueue *queue)
{
	unsigned int tmp = 0;
	if (QueueIsEmpty(queue))
		return -1;
	tmp = queue->data[queue->front];
	queue->front = (queue->front + 1) % SIZE;
	queue->lenth--;
	return tmp;
	//queue->data[queue->rear] = data;
	//queue->rear = (queue->rear + 1) % SIZE;
	//queue->lenth++;
}

void QueueFunction_Test()
{
	sQueue tmp_queue;
	QueueInit(&tmp_queue);
	PutQueue(&tmp_queue,10);
	PutQueue(&tmp_queue,20);
	printf("The queue lenth is %d\n",tmp_queue.lenth);

	for (unsigned int i = 0; i < tmp_queue.lenth; i++)
	{
		printf("%d\t",tmp_queue.data[(tmp_queue.front+i)%SIZE]);
	}
	printf("\n");
	PutQueue(&tmp_queue, 30);
	PutQueue(&tmp_queue, 40);

	for (int i = 0; i < tmp_queue.lenth; i++)
	{
		printf("%d\t", tmp_queue.data[(tmp_queue.front + i) % SIZE]);
	}
	printf("\n");
	printf("The queue lenth is %d\n", tmp_queue.lenth);
	int tmp = GetQueue(&tmp_queue);
	printf("The queue lenth is %d\n", tmp_queue.lenth);


	for (int i = 0; i < tmp_queue.lenth; i++)
	{
		printf("%d\t", tmp_queue.data[(tmp_queue.front + i) % SIZE]);
	}
	printf("\n");
}
//��ȡ���еĳ���
int QueueLenth(sQueue *queue)
{
	return queue->lenth;
	// return (queue->rear + SIZE -queue->front)%SIZE;

}


//���ڶ��г�ʼ��������
// �������µĶ��巽ʽ
#define MAXQSIZE 100
typedef int QElemtype;
typedef int status;

typedef struct {
	QElemtype *base;
	int front;
	int rear;
}SqQueue;

//SqQueue* InitQueue()
//{
//	SqQueue *q;
//	q = new SqQueue;
//	q->base = new int[MAXQSIZE];
//	q->rear = q->front = 0;
//	return q;
//}
//SqQueue *q;
//q = (SqQueue*)malloc(sizeof(SqQueue));
//q = InitQueue(q);