//栈的操作比较标准，清晰易懂
//此例程很有价值，注意经常复习
//david 2018-10-09


#include "bz_stack.h"

//typedef struct _NODE {
//	int data;
//	struct _NODE *pNext;    //实质是指向的上一个节点
//}*PNODE,NODE;


//typedef struct Stack {
//	PNODE pTop;
//	PNODE pBottom;
//}STACK, *PSTACK;



/**栈的初始化*/
void init(PSTACK pS) 
{

	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if (pS->pTop == NULL) {
		printf("内存分配失败退出");
		return;
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;
	}
}
/**是否为空栈*/
int isEmpty(PSTACK pS)
{
	if (pS->pTop == pS->pBottom)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*********************************************
压栈

@param pS 执行压栈的栈指针
@param val 被压栈的值

说明：ptop 指向栈顶，ptop->data 即使栈顶元素
david:2018-10-09 
***********************************************/
void push(PSTACK pS, int val) 
{
	// 创建新节点，放到栈顶
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = val;
	pNew->pNext = pS->pTop;

	pS->pTop = pNew;    // 栈顶指针指向新元素
}

/*****************************************
出栈

@param pS 执行出栈的栈地址
@param val 出栈值的地址
@return 是否出栈成功
***************************************/
int pop(PSTACK pS, int *val) 
{

	if (isEmpty(pS)) {
		printf(" 空栈 ，出栈失败");
		return 0;
	}
	else
	{
		PNODE p = pS->pTop;
		pS->pTop = p->pNext;

		if (val != NULL) {
			*val = p->data;
		}
		free(p);                // 释放原来top内存
		p = NULL;
		return 1;
	}
}
/**清空栈*/
void clearStack(PSTACK pS) {

	if (isEmpty(pS)) {
		return;
	}
	else {
		PNODE p = pS->pTop;
		PNODE q = NULL;

		while (p != pS->pBottom) {
			q = p->pNext;
			free(p);        // 释放原栈顶元素空间
			p = q;
		}
		pS->pTop = pS->pBottom;
	}


	//    偷懒的做法
	//    while (!isEmpty(pS)) {
	//        pop(pS, NULL);
	//    }
}


/**遍历打印栈*/
void traverse(PSTACK pS) 
{

	// 只要不是空栈，就一直输出
	PNODE p = pS->pTop;
	while (p != pS->pBottom) {

		printf("%d   ", p->data);

		p = p->pNext;  // 把top的下一个节点付给top，继续遍历
	}
	printf("\n");
}

//栈的应用，十进制数字转化成8进制
void conversion(void) {

	// 创建栈
	STACK S;
	init(&S);
	int N;

	// 用户输入十进制数
	scanf_s("%d", &N);

	// 放入栈中
	while (N) {
		push(&S, N % 8);
		N = N / 8;
	}

	// 打印出来
	printf("对应八进制数字为:");
	int a;
	while (!isEmpty(&S)) {
		pop(&S, &a);
		printf("%d", a);
	}
	printf("\n");
}
/**
检测括号(本实例用数字代替括号)

[ ]    -->    1 , 2
( )    -->    3 , 4

*/
void checkBracelet(void)
{
	// 创建栈
	STACK S;
	init(&S);

	// 用户输入括号
	int N;
	printf("请输入对应的括号(end结束):\n");
	scanf_s("%d", &N);

	if (isEmpty(&S)) {
		push(&S, N);
		printf("第一个括号输入\n");
		traverse(&S);       // 打印此时栈内容
	}

	while (!isEmpty(&S)) {

		// 用户输入括号
		int N;
		printf("请输入对应的括号(0结束):\n");
		scanf_s("%d", &N);

		if (N == 0) {
			break;  // 用户输入0直接退出
		}

		// 判断当前栈顶是否符合标准，
		if (S.pTop->data == N) {
			printf("消除一对\n");
			pop(&S, NULL);
			traverse(&S);       // 打印此时栈内容
		}
		else
		{
			printf("未消除\n");
			push(&S, N);
			traverse(&S);       // 打印此时栈内容
		}
	}
}

//栈的其他应用：行编辑，迷宫求解，表达式求值
void bz_stackTest()
{
	STACK stack;    // 声明一个栈
	init(&stack);   // 初始化

    // 压栈操作，调试过程中，观察栈顶元素的指针值，及next值，有助于理解程序
	//david 2018-10-09 阅读
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);
	push(&stack, 40);
	push(&stack, 50);

	traverse(&stack);   // 遍历打印栈

	int val;
	int isPopSuccess = pop(&stack, &val);
	if (isPopSuccess) {
		printf("pop 的值为 %d\n", val);
	}

	traverse(&stack);

	clearStack(&stack);   // 清空栈
	traverse(&stack);
}