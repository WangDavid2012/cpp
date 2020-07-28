#include "stack.h"


/***********************************************
ջ�ĳ���ģ�ͣ�
	1��ջ�ĳ�ʼ��
	2����ջ����
	3����ջ����
	4��ջ���ж�
	5��ջ���ж�
	6��ջ����ȶ�ȡ
	7��ջ������
*************************************************/

/************************************************
 ջ�ĳ�ʼ��˵����
 ��ʼ��һ������Ϊlenth��ջ��ָ��ָ��ջ��λ��
 ���磺�������Ϊ5��ջ

     ________ptopָ��λ��
	|________|
	|________|
	|________|
	|________|
	|________|

david 2018-10-09 �������Ķ��Լ���д��ջ��ʼ������
������������ ��
	1����ʼ��һ��ջ��ջ��Ӧ����ջ�����   ptop = pbottom
	2��ջ�����ж�����  ptopָ���˿��ٿռ䶥��  if ((S.top - S.base) >= S.stacksize)
	3��ջ�յ��ж����� ptop = pbottom
�Լ���д�Ĺ���ջ����ز����Ǵ���ģ��Ժ�Ҳ��Ҫ���ã��м�
**********************************************/
s_Stack * StackInit(int lenth)
{
	s_Stack *ptmpStack = (s_Stack *)malloc(sizeof(s_Stack));

	ptmpStack->pbase = (int *)malloc(sizeof(int)*lenth);

	ptmpStack->lenth = lenth;

	ptmpStack->ptop = ptmpStack->pbase + lenth;
	return ptmpStack;
}


void StackDestory(s_Stack *stack)
{
	free(stack->pbase);
	free(stack);
}
//ջ����ȣ���ʾ�Ѿ�ʹ�õ�ջ�Ĵ�С
int StackDeep(s_Stack *stack)
{
	return stack->lenth -(stack->ptop - stack->pbase);
}
/**********************************************************
//�ж�ջ�Ƿ�����
	�ж�������ջ�� ��ȥ ջ��  �������1 ����Ϊջ�Ѿ�����
	david 2018-09-18 ����
***********************************************************/
int StackIsFull(s_Stack *stack)
{
	if (stack->ptop - stack->pbase == 1)
		return 1;
	else
		return 0;
}

/*********************************************************
 ջ���ж�
	�жϷ�ʽ���ж� ջ��  ��ȥ ջ��   ����  ����ջ�Ŀռ䳤��
	��Ϊջ�ǿյ�
**********************************************************/
int StackIsEmpty(s_Stack *stack)
{

	if (stack->ptop - stack->pbase == stack->lenth)
		return 1;
	else
		return 0;
}

//��ջ֮ǰ��Ӧ���ж�ջ�Ƿ��Ѿ�����
void PopStack(s_Stack *stack, int data)
{
	if (StackIsFull(stack))
		printf("The stack is full,pop stack failed!\n");
	else
	{
		--stack->ptop;
		*(stack->ptop) = data;
		//&(stack->ptop) = data;    //���󣬱��ʽ�����ǿ����޸ĵ���ֵ
		//printf("The top point is 0x%08X\n", &stack->ptop);
		printf("The top point is 0x%08X\n", stack->ptop);
	}
	/************************************************************
	����������
		stack->ptop ��ʾ����һ��ָ��
		& stack->ptop ��ʾ�������ָ��Ĵ�ŵ�ַ
		* (stack->ptop) ��ʾ�������ָ��ָ�������
		���Զ� &stack->ptop ��ֵ����ִ���
	*************************************************************/
}

int PushStack(s_Stack *stack, int *data)
{
	if (StackIsEmpty(stack))
		return 0;
	else
	{
		*data = *stack->ptop;
		stack->ptop++;
	}
}
//��ӡջ�е����ݣ���ջ��λ�ÿ�ʼ��ӡ
void PrintfStack(s_Stack *stack)
{
	int lenth = StackDeep(stack);
	int *p = stack->ptop;
	
	for (int i = 0; i < lenth; i++)
	{
		printf("0x%08X\t",*p);
		p++;
	}
	printf("\n");
}



//����ջ����ʵ��
//time:2018-09-18  david
void StackTest()
{
	s_Stack *p;
	p = StackInit(100);

	PopStack(p,0xA5);
	PopStack(p,0x55AA);
	PopStack(p, 0x58A);
	PopStack(p, 0x23);
	PopStack(p, 0x45);
	PopStack(p, 0x67);
	PrintfStack(p);
	int tmp = 0;
	PushStack(p,&tmp);
	printf("The tmp value is 0x%08X\n",tmp);
	PushStack(p, &tmp);
	printf("The tmp value is 0x%08X\n", tmp);
	PushStack(p, &tmp);
	printf("The tmp value is 0x%08X\n", tmp);
	PushStack(p, &tmp);
	printf("The tmp value is 0x%08X\n", tmp);
	PrintfStack(p);
	printf("The Stack deep is %d\n", StackDeep(p));
	StackDestory(p);
	printf("The stack is destoryed!\n");
}


