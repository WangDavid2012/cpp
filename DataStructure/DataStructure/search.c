//算法全部参加《大话数据结构》
#include <stdio.h>
#include "search.h"



/************************************************
顺序表查找算法
存在问题，如果key不存在怎么办？ 如果key存在第0个元素
无法理解哨兵 的作用
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
二分查找
查找的前提条件是线性表中的记录必须是关键码有序，且线性表采用
顺序存储
自己写的算法：
	存在问题，如果数组中，不存在key元素，无法跳出while循环
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
存在问题：
	a[11] = {0,1,2,3,4,5,6,7,8,9,10};
	如果查找元素8，则如下输入
	Binary_Search(a,10,8);
	注意n输入的是10，是数组的最后一个下标值，而不是输入的
	数组长度。
	存在问题，如果查找元素22，则返回值是0
	算法还是不完美。
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
斐波那契查找算法：
	采用了黄金分割的原理
斐波那契数列
0 1 1 2 3 5 8 13 21......
***************************************************************/
int Fibonacci_Search(int *a,int n,int key)
{
}


/***********************************************************
递归查找二叉排序树中是否含有key
指针f指向T的双亲，其初始调用值为null
若查找成功，则指针P指向该数据元素节点，并返回true
否则指针p指向查找路径上访问的最后一个节点并返回false
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
	//二分查找算法测试
	int a[10] = {1,3,6,8,9,12,14,67,89,100};
	int b[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
	int index = Binary_Search(a, 10, 89);
	printf("the index is %d\n", index);
	int index1 = Binary_Search(b, 10, 22);
	printf("the array b[] index1 is %d\n", index1);
}