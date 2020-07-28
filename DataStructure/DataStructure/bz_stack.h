#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "common.h"



/**********************************************************
�ļ�˵����
	bz��ͷ���ļ����Ǳ�׼�ļ����ǹٷ��ṩ�����ݽṹʵ�ַ�ʽ��
	�������ļ������Լ�д��ʵ�ַ�ʽ
*************************************************************/


/*****************************************************
ջ�����֪ʶ��
	��̬ջ����̬ջ�ĺ��������飬������һ���������ڴ����飬����ֻ�ܲ�����ջ��Ԫ��
	��̬ջ����̬ջ�ĺ��������飬������һ���������ڴ����飬����ֻ�ܲ�����ջ���ڵ�
******************************************************************/

/********************************************************/
//ջ�Ļ�����������ʼ����ѹջ����ջ���пգ����������
/*********************************************************/


//typedef struct _NODE {
//	int data;
//	struct _NODE *pNext;    //ʵ����ָ�����һ���ڵ�
//}*PNODE,NODE;


typedef struct Stack {
	PNODE pTop;
	PNODE pBottom;
}STACK,*PSTACK;


/**ջ�ĳ�ʼ��*/
void init(PSTACK);
/**ѹջ*/
void push(PSTACK, int);
/**��ջ*/
int pop(PSTACK, int *);
/**������ӡջ*/
void traverse(PSTACK);
/**�Ƿ�Ϊ��ջ*/
int isEmpty(PSTACK);
/**���ջ*/
void clearStack(PSTACK);
void bz_stackTest();