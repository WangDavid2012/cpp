#include "stack.h"


/***********************************************
栈的抽象模型：
	1、栈的初始化
	2、入栈操作
	3、出栈操作
	4、栈空判断
	5、栈满判断
	6、栈的深度读取
	7、栈的销毁
*************************************************/

/************************************************
 栈的初始化说明：
 初始化一个长度为lenth的栈，指针指向栈顶位置
 例如：开辟深度为5的栈

     ________ptop指针位置
	|________|
	|________|
	|________|
	|________|
	|________|

david 2018-10-09 日重新阅读自己编写的栈初始化函数
函数存在问题 ：
	1、初始化一个栈，栈顶应该与栈底相等   ptop = pbottom
	2、栈满的判断条件  ptop指向了开辟空间顶部  if ((S.top - S.base) >= S.stacksize)
	3、栈空的判断条件 ptop = pbottom
自己编写的关于栈的相关操作是错误的，以后也不要采用，切记
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
//栈的深度，表示已经使用的栈的大小
int StackDeep(s_Stack *stack)
{
	return stack->lenth -(stack->ptop - stack->pbase);
}
/**********************************************************
//判断栈是否满了
	判断条件，栈顶 减去 栈首  如果等于1 则认为栈已经满了
	david 2018-09-18 测试
***********************************************************/
int StackIsFull(s_Stack *stack)
{
	if (stack->ptop - stack->pbase == 1)
		return 1;
	else
		return 0;
}

/*********************************************************
 栈空判断
	判断方式：判断 栈顶  减去 栈底   等于  开辟栈的空间长度
	认为栈是空的
**********************************************************/
int StackIsEmpty(s_Stack *stack)
{

	if (stack->ptop - stack->pbase == stack->lenth)
		return 1;
	else
		return 0;
}

//入栈之前，应该判断栈是否已经满了
void PopStack(s_Stack *stack, int data)
{
	if (StackIsFull(stack))
		printf("The stack is full,pop stack failed!\n");
	else
	{
		--stack->ptop;
		*(stack->ptop) = data;
		//&(stack->ptop) = data;    //错误，表达式必须是可以修改的左值
		//printf("The top point is 0x%08X\n", &stack->ptop);
		printf("The top point is 0x%08X\n", stack->ptop);
	}
	/************************************************************
	出现问题解答：
		stack->ptop 表示的是一个指针
		& stack->ptop 表示的是这个指针的存放地址
		* (stack->ptop) 表示的是这个指针指向的数据
		所以对 &stack->ptop 赋值会出现错误
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
//打印栈中的内容，从栈顶位置开始打印
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



//测试栈函数实现
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


