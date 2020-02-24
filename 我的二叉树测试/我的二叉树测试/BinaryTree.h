#pragma once
#include <stdlib.h>
#include <stdio.h>


typedef struct BinaryTreeNode
{
    char data;
    struct BinaryTreeNode* lchild;
    struct BinaryTreeNode* rchild;
}BinaryTree,BinaryTreeNode;

//使用# 法创建二叉树
BinaryTree* Create_BinaryTree();
//二叉树的前序遍历
void Preorder_Traversal(BinaryTree* root);


//二叉树的中序遍历
void Inorder_Traversal(BinaryTree* root);

//二叉树的后序遍历
void Postorder_Traversal(BinaryTree* root);
//求二叉树的深度
int Depth_BinaryTree(BinaryTree* root);
//求二叉树的叶子节点个数
void  LeafCount_BinaryTree(BinaryTree* root,int *count);




void PrintfBinaryTree(BinaryTree* root);