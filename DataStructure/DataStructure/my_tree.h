#pragma once



typedef struct BinaryTreeNode
{
	int data;
	struct BinaryTreeNode *Left;
	struct BinaryTreeNode *Right;
}my_Node;

my_Node* createBinaryTree(void);

int my_tree_test(void);