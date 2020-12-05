#pragma once



typedef struct BiNode
{
	int data;
	struct BiNode *p_lchild, *p_rchild;
}BiTree,*pBinTree;

//ͨ���涨����ĳһ��㣬��������������lchildָ��ǰ����㣻��������������rchildָ���̽�㡣
//����Ҫ������������tag��������ǵ�ǰ����Ƿ���������
//��ltag == 1, lchildָ����ǰ������rtag == 1��rchildָ�����̡�

//����������
typedef struct ThreadNode 
{
	int data;
	struct ThreadNode *lchild, *rchild;
	int ltag, rtag;
}ThreadNode, *ThreadTree;


//�������ı�����Ϊǰ������������������������

void PreOrderTraverse(pBinTree t);
pBinTree MyCreateBinTree();

void MyTreeTest();