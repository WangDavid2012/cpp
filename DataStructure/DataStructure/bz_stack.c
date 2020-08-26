//ջ�Ĳ����Ƚϱ�׼�������׶�
//�����̺��м�ֵ��ע�⾭����ϰ
//david 2018-10-09


#include "bz_stack.h"

//typedef struct _NODE {
//	int data;
//	struct _NODE *pNext;    //ʵ����ָ�����һ���ڵ�
//}*PNODE,NODE;


//typedef struct Stack {
//	PNODE pTop;
//	PNODE pBottom;
//}STACK, *PSTACK;



/**ջ�ĳ�ʼ��*/
void init(PSTACK pS) 
{

	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if (pS->pTop == NULL) {
		printf("�ڴ����ʧ���˳�");
		return;
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;
	}
}
/**�Ƿ�Ϊ��ջ*/
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
ѹջ

@param pS ִ��ѹջ��ջָ��
@param val ��ѹջ��ֵ

˵����ptop ָ��ջ����ptop->data ��ʹջ��Ԫ��
david:2018-10-09 
***********************************************/
void push(PSTACK pS, int val) 
{
	// �����½ڵ㣬�ŵ�ջ��
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = val;
	pNew->pNext = pS->pTop;

	pS->pTop = pNew;    // ջ��ָ��ָ����Ԫ��
}

/*****************************************
��ջ

@param pS ִ�г�ջ��ջ��ַ
@param val ��ջֵ�ĵ�ַ
@return �Ƿ��ջ�ɹ�
***************************************/
int pop(PSTACK pS, int *val) 
{

	if (isEmpty(pS)) {
		printf(" ��ջ ����ջʧ��");
		return 0;
	}
	else
	{
		PNODE p = pS->pTop;
		pS->pTop = p->pNext;

		if (val != NULL) {
			*val = p->data;
		}
		free(p);                // �ͷ�ԭ��top�ڴ�
		p = NULL;
		return 1;
	}
}
/**���ջ*/
void clearStack(PSTACK pS) {

	if (isEmpty(pS)) {
		return;
	}
	else {
		PNODE p = pS->pTop;
		PNODE q = NULL;

		while (p != pS->pBottom) {
			q = p->pNext;
			free(p);        // �ͷ�ԭջ��Ԫ�ؿռ�
			p = q;
		}
		pS->pTop = pS->pBottom;
	}


	//    ͵��������
	//    while (!isEmpty(pS)) {
	//        pop(pS, NULL);
	//    }
}


/**������ӡջ*/
void traverse(PSTACK pS) 
{

	// ֻҪ���ǿ�ջ����һֱ���
	PNODE p = pS->pTop;
	while (p != pS->pBottom) {

		printf("%d   ", p->data);

		p = p->pNext;  // ��top����һ���ڵ㸶��top����������
	}
	printf("\n");
}

//ջ��Ӧ�ã�ʮ��������ת����8����
void conversion(void) {

	// ����ջ
	STACK S;
	init(&S);
	int N;

	// �û�����ʮ������
	scanf_s("%d", &N);

	// ����ջ��
	while (N) {
		push(&S, N % 8);
		N = N / 8;
	}

	// ��ӡ����
	printf("��Ӧ�˽�������Ϊ:");
	int a;
	while (!isEmpty(&S)) {
		pop(&S, &a);
		printf("%d", a);
	}
	printf("\n");
}
/**
�������(��ʵ�������ִ�������)

[ ]    -->    1 , 2
( )    -->    3 , 4

*/
void checkBracelet(void)
{
	// ����ջ
	STACK S;
	init(&S);

	// �û���������
	int N;
	printf("�������Ӧ������(end����):\n");
	scanf_s("%d", &N);

	if (isEmpty(&S)) {
		push(&S, N);
		printf("��һ����������\n");
		traverse(&S);       // ��ӡ��ʱջ����
	}

	while (!isEmpty(&S)) {

		// �û���������
		int N;
		printf("�������Ӧ������(0����):\n");
		scanf_s("%d", &N);

		if (N == 0) {
			break;  // �û�����0ֱ���˳�
		}

		// �жϵ�ǰջ���Ƿ���ϱ�׼��
		if (S.pTop->data == N) {
			printf("����һ��\n");
			pop(&S, NULL);
			traverse(&S);       // ��ӡ��ʱջ����
		}
		else
		{
			printf("δ����\n");
			push(&S, N);
			traverse(&S);       // ��ӡ��ʱջ����
		}
	}
}

//ջ������Ӧ�ã��б༭���Թ���⣬���ʽ��ֵ
void bz_stackTest()
{
	STACK stack;    // ����һ��ջ
	init(&stack);   // ��ʼ��

    // ѹջ���������Թ����У��۲�ջ��Ԫ�ص�ָ��ֵ����nextֵ��������������
	//david 2018-10-09 �Ķ�
	push(&stack, 10);
	push(&stack, 20);
	push(&stack, 30);
	push(&stack, 40);
	push(&stack, 50);

	traverse(&stack);   // ������ӡջ

	int val;
	int isPopSuccess = pop(&stack, &val);
	if (isPopSuccess) {
		printf("pop ��ֵΪ %d\n", val);
	}

	traverse(&stack);

	clearStack(&stack);   // ���ջ
	traverse(&stack);
}