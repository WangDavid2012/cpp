/********************************************************************
�ļ�˵����
	��Ҫ���ܽ����ݽṹ������д�Ĵ����Ƿ������������
	ʵ�ֵĹ������£�
	����ѭ������    
	���ԶѵĲ���
	����ջ�Ĳ���
	���Ե�������
	����˫������
	���Զ�����
	������������
	���Զ�����ǰ�����򣬺������
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "heap.h"
#include "singlelinkedlist.h"
#include "bz_stack.h"
#include "my_tree.h"
#include "search.h"
#include "tlist.h"


int main()
{
	//�⼸���㷨������������֤

	ParentNodeAddr_Test();
	QueueFunction_Test();   //����ѭ������
	StackTest();             //����ջ����
	SearchTest();           //�����㷨����
	bz_stackTest();         //ջ��������



	//�������Ĳ������������⣬����������  david  2018-10-09
	//MyTreeTest();
	//my_tree_test();
	getchar();

	return 0;
}