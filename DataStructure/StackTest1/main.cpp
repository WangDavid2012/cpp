//网上资料，程序不是特别好
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int EleType;


typedef struct StackNode {  
	EleType data;                //结点数据域
	struct StackNode* next;      //结点指针域
}StackNode, *LinkStackPoi;
//链栈的数据结构
typedef struct LinkStack {
	LinkStackPoi top;             //栈顶结点
	int count;                    //元素个数
}LinkStack;
//初始化
Status InitLinkStack(LinkStack* stack)
{
	if (!stack)
	{
		return	ERROR;
	}
	stack->top = NULL;
	stack->count = 0;
	return OK;
}
//清空数据，释放结点内存，实际上就是pop所有数据
Status ClearLinkStack(LinkStack* stack)
{
	if (!stack || !stack->count)
	{
		return	ERROR;
	}
	while (stack->count)
	{
		StackNode* node = stack->top;
		stack->top = node->next;
		free(node);
		stack->count--;
	}
	return OK;
}
//判断链栈是否为空
Status EmptyLinkStack(LinkStack* stack) 
{
	if (!stack)
	{
		return ERROR;
	}
	return stack->count == 0 ? 1 : 0;
}
//获取元素个数
int GetLengthLinkStack(LinkStack* stack)
{
	if (!stack)
	{
		return	-1;
	}
	return stack->count;
}
Status GetTop(LinkStack* stack, StackNode** stackNode)
{
	if (!stack)
	{
		return	ERROR;
	}
	*stackNode = stack->top;//将栈顶元素的指针返回，获取指向可修改栈顶元素内容。
	return OK;
}
//Status GetTop(LinkStack* stack, StackNode* stackNode)
//{
//	if (!stack)
//	{
//		return	ERROR;
//	}
//	*stackNode = *(stack->top);//将栈顶元素的副本内容，修改不会影响到栈顶元素。
//	return OK;
//}
/*
弹栈
栈顶指针指向要弹出元素前置结点，然后释放弹出元素内存空间，然后count-1
*/
Status pop(LinkStack* stack, EleType *e)
{
	if (!stack && stack->count)
	{
		return	ERROR;
	}
	StackNode* node = stack->top;
	*e = node->data;
	stack->top = node->next;//栈顶指针指向新的栈顶元素
	free(node);             //释放元素空间
	stack->count--;
	return OK;
}
/*
压栈
先将压入元素放入到链表表中，然后再将栈顶指针指向压入的元素，然后count+1.
*/
Status push(LinkStack* stack, EleType e)
{
	if (!stack)
	{
		return ERROR;
	}
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->next = stack->top;            //将元素加入链表中
	node->data = e;
	stack->top = node;                   //栈顶元素指向压入元素
	stack->count++;
	return OK;
}
Status PrintfLinkStack(LinkStack* stack)
{
	if (!stack&&stack->count)
	{
		return ERROR;
	}
	StackNode* node = stack->top;
	while (node)
	{
		printf("%d,", node->data);
		node = node->next;
	}
	puts("");
	return OK;
}
int main(int argc, char *argv[])
{
	LinkStack stack;
	InitLinkStack(&stack);//初始化
	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);
	puts("链栈元素：");
	PrintfLinkStack(&stack);
	printf("链栈元素个数：%d\n", GetLengthLinkStack(&stack));
	EleType e1, e2;
	pop(&stack, &e1);
	printf("弹出第一个元素：%d\n", e1);
	pop(&stack, &e2);
	printf("弹出第二个元素：%d\n", e2);
	puts("链栈元素：");
	PrintfLinkStack(&stack);
	printf("链栈元素个数：%d", GetLengthLinkStack(&stack));
	printf("\n");
	getchar();
	return 0;
}

//-------------------- -
//作者：Laymond_
//来源：CSDN
//原文：https ://blog.csdn.net/qq_29542611/article/details/78899772?utm_source=copy 
//版权声明：本文为博主原创文章，转载请附上博文链接！