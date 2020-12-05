#pragma once


/*****************************************
 * 文件说明：
 * 循环队列的相关操作    david 2018-09-17 总结
 * ADT
 * 需要包括以下函数：
 * 1、队列的初始化
 * 2、队列入队
 * 3、队列的出对
 * 4、队列空判断
 * 5、队列的满判断
 * 6、队列插入元素
 * 7、队列删除元素
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


