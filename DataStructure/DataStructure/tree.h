#pragma once



typedef struct BiNode
{
	int data;
	struct BiNode *p_lchild, *p_rchild;
}BiTree,*pBinTree;

//通常规定：对某一结点，若无左子树，将lchild指向前驱结点；若无右子树，将rchild指向后继结点。
//还需要设置左右两个tag，用来标记当前结点是否有子树。
//若ltag == 1, lchild指向结点前驱；若rtag == 1，rchild指向结点后继。

//线索二叉树
typedef struct ThreadNode 
{
	int data;
	struct ThreadNode *lchild, *rchild;
	int ltag, rtag;
}ThreadNode, *ThreadTree;


//二叉树的遍历分为前序遍历，中序遍历，后续遍历

void PreOrderTraverse(pBinTree t);
pBinTree MyCreateBinTree();

void MyTreeTest();