//�������ϣ��������ر��
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
	EleType data;                //���������
	struct StackNode* next;      //���ָ����
}StackNode, *LinkStackPoi;
//��ջ�����ݽṹ
typedef struct LinkStack {
	LinkStackPoi top;             //ջ�����
	int count;                    //Ԫ�ظ���
}LinkStack;
//��ʼ��
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
//������ݣ��ͷŽ���ڴ棬ʵ���Ͼ���pop��������
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
//�ж���ջ�Ƿ�Ϊ��
Status EmptyLinkStack(LinkStack* stack) 
{
	if (!stack)
	{
		return ERROR;
	}
	return stack->count == 0 ? 1 : 0;
}
//��ȡԪ�ظ���
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
	*stackNode = stack->top;//��ջ��Ԫ�ص�ָ�뷵�أ���ȡָ����޸�ջ��Ԫ�����ݡ�
	return OK;
}
//Status GetTop(LinkStack* stack, StackNode* stackNode)
//{
//	if (!stack)
//	{
//		return	ERROR;
//	}
//	*stackNode = *(stack->top);//��ջ��Ԫ�صĸ������ݣ��޸Ĳ���Ӱ�쵽ջ��Ԫ�ء�
//	return OK;
//}
/*
��ջ
ջ��ָ��ָ��Ҫ����Ԫ��ǰ�ý�㣬Ȼ���ͷŵ���Ԫ���ڴ�ռ䣬Ȼ��count-1
*/
Status pop(LinkStack* stack, EleType *e)
{
	if (!stack && stack->count)
	{
		return	ERROR;
	}
	StackNode* node = stack->top;
	*e = node->data;
	stack->top = node->next;//ջ��ָ��ָ���µ�ջ��Ԫ��
	free(node);             //�ͷ�Ԫ�ؿռ�
	stack->count--;
	return OK;
}
/*
ѹջ
�Ƚ�ѹ��Ԫ�ط��뵽������У�Ȼ���ٽ�ջ��ָ��ָ��ѹ���Ԫ�أ�Ȼ��count+1.
*/
Status push(LinkStack* stack, EleType e)
{
	if (!stack)
	{
		return ERROR;
	}
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->next = stack->top;            //��Ԫ�ؼ���������
	node->data = e;
	stack->top = node;                   //ջ��Ԫ��ָ��ѹ��Ԫ��
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
	InitLinkStack(&stack);//��ʼ��
	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);
	puts("��ջԪ�أ�");
	PrintfLinkStack(&stack);
	printf("��ջԪ�ظ�����%d\n", GetLengthLinkStack(&stack));
	EleType e1, e2;
	pop(&stack, &e1);
	printf("������һ��Ԫ�أ�%d\n", e1);
	pop(&stack, &e2);
	printf("�����ڶ���Ԫ�أ�%d\n", e2);
	puts("��ջԪ�أ�");
	PrintfLinkStack(&stack);
	printf("��ջԪ�ظ�����%d", GetLengthLinkStack(&stack));
	printf("\n");
	getchar();
	return 0;
}

//-------------------- -
//���ߣ�Laymond_
//��Դ��CSDN
//ԭ�ģ�https ://blog.csdn.net/qq_29542611/article/details/78899772?utm_source=copy 
//��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�