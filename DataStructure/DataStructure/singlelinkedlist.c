//���ļ�����������д���Ŀǰ��û�в��ҳ���ԭ�� 2018-09-19

#include<stdio.h>
#include "stdlib.h"
#include "singlelinkedlist.h"

//������ĳ�ʼ��
//pLinkedList LinkedListInit() {
//	s_Node *L;
//	L = (s_Node *)malloc(sizeof(s_Node));   //������ռ� 
//	if (L == NULL) {                        //�ж��Ƿ����㹻���ڴ�ռ� 
//		printf("�����ڴ�ռ�ʧ��\n");
//	}
//	L->next = NULL;                         //��next����ΪNULL,��ʼ����Ϊ0�ĵ����� 
//	return L;
//}




void InseartData(pLinkedList pList, int data)
{
	
	s_Node *ptmpNode = pList->next;    //����ͷָ��ָ���һ���ڵ㣨ͷ���ĺ���һ���ڵ㣩
	s_Node *pnode;
	while (ptmpNode != NULL)
	{
		ptmpNode = pList->next;
	}
	pnode = (s_Node *)malloc(sizeof(s_Node));
	if (pnode == NULL)
		printf("malloc Node failed!\n");
	else
	{
		pnode->data = data;
		pnode->next = NULL;
		
		ptmpNode = pnode;
	}
}


void PrintfLinkData(pLinkedList pList)
{
	s_Node *ptmp = pList->next;
	while (ptmp)
	{
		printf("The Value is %d\n",ptmp->data);
		ptmp = pList->next->next;
	}

	printf("printf finish!\n");
}


void SingleLinkedList_Test()
{

	//pLinkedList pList = LinkedListInit();
	//InseartData(pList,1);
	//InseartData(pList, 2);
	//InseartData(pList, 3);
	//InseartData(pList, 4);
	//InseartData(pList, 5);
	//InseartData(pList, 6);
	//InseartData(pList, 7);
	//InseartData(pList, 8);
	//InseartData(pList, 9);
	//PrintfLinkData(pList);


}


