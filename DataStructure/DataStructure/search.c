//�㷨ȫ���μӡ������ݽṹ��
#include <stdio.h>
#include "search.h"



/************************************************
˳�������㷨
�������⣬���key��������ô�죿 ���key���ڵ�0��Ԫ��
�޷�����ڱ� ������
************************************************/
int Sequential_Search1(int *a,int lenth,int key)
{
	for (int i = 1; i < lenth; i++)
	{
		if (*(a + i) == key)
			return i;
	}
	return 0;
}
int Sequential_Search2(int *a, int lenth, int key)
{
	a[0] = key;
	int i = lenth;
	while(a[i] != key)
	{
		i--;
	}
	return i;
}

/*****************************************************
���ֲ���
���ҵ�ǰ�����������Ա��еļ�¼�����ǹؼ������������Ա����
˳��洢
�Լ�д���㷨��
	�������⣬��������У�������keyԪ�أ��޷�����whileѭ��
*****************************************************/
int MY_Binary_Search(int *a, int n, int key)
{
	int left = 0;
	int right = n - 1;
	int mid = (left + right) / 2;
	
	while (key != a[mid])
	{
		if (a[mid]<key)
		{

			left = mid;
		}
		else
		{
			right = mid;
		}
		mid = (left + right) / 2;
	}
	
	return mid;
}
/***********************************************
�������⣺
	a[11] = {0,1,2,3,4,5,6,7,8,9,10};
	�������Ԫ��8������������
	Binary_Search(a,10,8);
	ע��n�������10������������һ���±�ֵ�������������
	���鳤�ȡ�
	�������⣬�������Ԫ��22���򷵻�ֵ��0
	�㷨���ǲ�������
************************************************/
int Binary_Search(int *a, int n, int key)
{
	int low = 1;
	int high = n;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;

		if (key > a[mid])
		{
			low = mid + 1;
			
		}
		else if (key < a[mid])
		{
			high = mid - 1;
		}
		else
			return mid;
	}
	return 0;
}
/**************************************************************
쳲����������㷨��
	�����˻ƽ�ָ��ԭ��
쳲���������
0 1 1 2 3 5 8 13 21......
***************************************************************/
int Fibonacci_Search(int *a,int n,int key)
{
}


/***********************************************************
�ݹ���Ҷ������������Ƿ���key
ָ��fָ��T��˫�ף����ʼ����ֵΪnull
�����ҳɹ�����ָ��Pָ�������Ԫ�ؽڵ㣬������true
����ָ��pָ�����·���Ϸ��ʵ����һ���ڵ㲢����false
*************************************************************/
bool SearchBST(pBinTree T,int key, pBinTree f, pBinTree *p)
{
	if (!T)
	{
		*p = f;
		return false;
	}
}






void SearchTest()
{
	//���ֲ����㷨����
	int a[10] = {1,3,6,8,9,12,14,67,89,100};
	int b[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
	int index = Binary_Search(a, 10, 89);
	printf("the index is %d\n", index);
	int index1 = Binary_Search(b, 10, 22);
	printf("the array b[] index1 is %d\n", index1);
}