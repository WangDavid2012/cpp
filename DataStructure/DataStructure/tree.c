#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "common.h"
#include "bz_stack.h"

/**********************************************
//前序遍历，根节点，左子树，右子树
使用递归算法

如果不使用递归算法，可以使用栈操作的方法完成
递归操作效率比较低

先序遍历和后续遍历的非递归算法？？？？？
***********************************************/
void PreOrderTraverse(pBinTree t)
{
	if (t == NULL)
		return;
	printf("%c",t->data);
	PreOrderTraverse(t->p_lchild);
	PreOrderTraverse(t->p_rchild);
}





/***************************************************
中序遍历：
左子树，根节点，右子树
递归程序虽然简洁，但是执行效率不高，所以下面给出非递归算法。
由图可知，三种遍历的路线是一样的：都是从根结点开始沿左子树深入下去，
当深入到最左端，无法继续深入下去时，则沿原路返回，每遇到一个结点便进入其右子树，
如此地深入和返回，直到最后从根结点的右子树返回根节点为止。先序遍历是在深入时遇到结点就访问，
中序遍历是在从左子树返回时遇到结点就访问，后序遍历是从右子树返回时遇到结点就访问。
在这一过程中，返回结点的顺序与进入节点的顺序相反，即后进入先返回，正好符合堆栈结构后进先出的特点。
由此，可以利用堆栈实现这一遍历路线。
在中序遍历二叉树时，遇到一个结点，就把它入栈，并去遍历它的左子树；
当左子树便利结束后，从栈顶弹出并访问这个结点，然后按其右指针中序遍历该结点的右子树。
代码如下：
****************************************************/


//void my_InOrderTraversal(pBinTree BT)
//{
//	//pBinTree T;
//	//STACK S;
//	//init(&S);
//	//T = BT;
//	//while (T || !IsEmpty(S)) {
//	//	while (T) {
//	//		Push(S, T);
//	//		T = T->p_lchild;
//	//	}
//	//	if (!IsEmpty(S)) {
//	//		T = Pop(S);
//	//		printf("%d ", T->data);
//	//		T = T->p_rchild;
//	//	}
//	//}
//}
//使用递归算法实现中序遍历
void InOrderTraversal(pBinTree BT)
{
	if (BT) {
		InOrderTraversal(BT->p_lchild);
		printf("%d ", BT->data);
		InOrderTraversal(BT->p_rchild);
	}
}
/*************************************************
后序遍历：
左子树，右子树，根节点
****************************************************/
void PostOderTraversal(pBinTree BT)
{
	if (BT) 
	{
		InOrderTraversal(BT->p_lchild);
		InOrderTraversal(BT->p_rchild);
		printf("%d ", BT->data);
	}
}

/***********************************************
创建二叉树
 使用前序遍历的方式
 #表示空树

为什么需要用到一个二维指针   不是特别的理解
**************************************************/
void CreateBinTree(pBinTree *tree)
{
	int ch;
	printf("please input data\n");
	scanf_s("%d",&ch);
	if (ch == '#')
		*tree = NULL;
	else
	{
		*tree = (pBinTree)malloc(sizeof(pBinTree));
		if (*tree == NULL)
			return;
		(*tree)->data = ch;

		CreateBinTree(&(*tree)->p_lchild);
		CreateBinTree(&(*tree)->p_rchild);
	}
}
//不知道什么问题，调试过程中发现，输入A后，再次输入，
//调试到 BiTree *tree;语句后，tree值已经被修改
//使用C++ 调试时，不会出现这个问题
pBinTree MyCreateBinTree( )
{
	char ch;
	BiTree *tree;
	printf("please input data\n");
	scanf_s("%c", &ch,1);
	if (ch == '#')
		tree = NULL;
	else
	{
		tree = (BiTree *)malloc(sizeof(BiTree));
		(tree)->data = ch;
		tree->p_lchild = MyCreateBinTree();
		tree->p_rchild = MyCreateBinTree();
	}
	return tree;
}





/******************************************************
二叉树的一些知识：
1、如果一个二叉树有n个节点，则这个二叉树有2n个指针域，有n+1个空的指针域
2、
*******************************************************/

/******************************************************
霍夫曼树:
	通信中可以用于编码，解码
	通信过程中，词汇出现的概率不同，根据概率给编码
********************************************************/



/*********************************************************
中序遍历+先序遍历  可以还原树
中序遍历+后续遍历  可以还原树
先序遍历+后续遍历     不能还原树
**********************************************************/



/*********************************************************
二叉树的应用举例    遍历算法的应用--------
  这些应用会用到二叉树的遍历算法
1、查询二叉树中的某个节点
2、统计二叉树中叶子节点的个数
3、求二叉树的深度（后序遍历）
4、复制二叉树（后序遍历）
5、建立二叉树的存储结构
*********************************************************/


/**************************************************
查询二叉树中的某个节点
***************************************************/


//线索二叉树创建
//线索二叉树的遍历（不用递归，也不用栈）
//因为有前驱和后继节点
//先建立线索链表，找到第一个节点，不断找后继，完成遍历

//中序线索话链表的遍历算法




//二叉树测试程序
void MyTreeTest()
{

	pBinTree t = NULL;
	//CreateBinTree(t);
	t = MyCreateBinTree();
	PreOrderTraverse(t);


}