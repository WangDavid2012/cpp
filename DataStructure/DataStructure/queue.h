#pragma once


/*****************************************
 * �ļ�˵����
 * ѭ�����е���ز���    david 2018-09-17 �ܽ�
 * ADT
 * ��Ҫ�������º�����
 * 1�����еĳ�ʼ��
 * 2���������
 * 3�����еĳ���
 * 4�����п��ж�
 * 5�����е����ж�
 * 6�����в���Ԫ��
 * 7������ɾ��Ԫ��
********************************************/

#define SIZE 100

typedef struct _Queue
{
	unsigned int data[SIZE];
	unsigned int front;
	unsigned int rear;
	unsigned int lenth;
}sQueue;

void QueueInit(sQueue *queue);
void QueueFunction_Test(void);


