#pragma once
#include <stdlib.h>
#include <stdio.h>


typedef struct BinaryTreeNode
{
    char data;
    struct BinaryTreeNode* lchild;
    struct BinaryTreeNode* rchild;
}BinaryTree,BinaryTreeNode;

//ʹ��# ������������
BinaryTree* Create_BinaryTree();
//��������ǰ�����
void Preorder_Traversal(BinaryTree* root);


//���������������
void Inorder_Traversal(BinaryTree* root);

//�������ĺ������
void Postorder_Traversal(BinaryTree* root);
//������������
int Depth_BinaryTree(BinaryTree* root);
//���������Ҷ�ӽڵ����
void  LeafCount_BinaryTree(BinaryTree* root,int *count);




void PrintfBinaryTree(BinaryTree* root);