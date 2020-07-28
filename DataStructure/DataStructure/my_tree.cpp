
#include <iostream>
#include "my_tree.h"

using namespace std;

my_Node* createBinaryTree()
{
	my_Node *p;
	int ch;
	cin >> ch;
	if (ch == '#')     //如果到了叶子节点，接下来的左、右子树分别赋值为#
	{
		p = NULL;
	}
	else
	{
		p = (my_Node*)malloc(sizeof(my_Node));
		p->data = ch;
		cout << "creat left tree!" << endl;
		p->Left = createBinaryTree();   //递归创建左子树
		cout << "creat right tree!" << endl;
		p->Right = createBinaryTree();  //递归创建右子树
	}
	return p;
}
void my_preOrderTraverse(my_Node* root)
{
	if (root)
	{
		cout << root->data << ' ';
		my_preOrderTraverse(root->Left);
		my_preOrderTraverse(root->Right);
	}
}
void my_inOrderTraverse(my_Node* root)
{
	if (root)
	{
		my_inOrderTraverse(root->Left);
		cout << root->data << ' ';
		my_inOrderTraverse(root->Right);
	}
}

void my_lastOrderTraverse(my_Node* root)
{
	if (root)
	{
		my_lastOrderTraverse(root->Left);
		my_lastOrderTraverse(root->Right);
		cout << root->data << ' ';
	}
}
//二叉树节点数统计
int Nodenum(my_Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + Nodenum(root->Left) + Nodenum(root->Right);
	}
}
int DepthOfTree(my_Node* root)
{
	if (root)
	{
		return DepthOfTree(root->Left)>DepthOfTree(root->Right) ? DepthOfTree(root->Left) + 1 : DepthOfTree(root->Right) + 1;
	}
	if (root == NULL)
	{
		return 0;
	}
}
//二叉树叶子节点数
int Leafnum(my_Node* root)
{
	if (!root)
	{
		return 0;
	}
	else if ((root->Left == NULL) && (root->Right == NULL))
	{
		return 1;
	}
	else
	{
		return  (Leafnum(root->Left) + Leafnum(root->Right));
	}
}


//二叉树创建的步骤
//1、首先声明一个根节点，指向空
//2、在根节点的基础上，创建左子树，右子树，
//3、注意，创建二叉树时，如果遇到叶子节点，后续两个节点的输入本函数中为'#'
//4、创建二叉树成功后，在调试遍历等其他函数
int my_tree_test()
{
	my_Node *root = NULL;
	root = createBinaryTree();
	printf("二叉树建立成功");
	cout << endl;

	cout << "二叉树总节点数为：" << Nodenum(root) << endl;

	cout << "二叉树深度为：" << DepthOfTree(root) << endl;

	cout << "二叉树叶子节点数为：" << Leafnum(root) << endl;

	cout << "前序遍历结果:" << endl;
	my_preOrderTraverse(root);
	cout << endl;

	cout << "中序遍历结果:" << endl;
	my_inOrderTraverse(root);
	cout << endl;

	cout << "后序遍历结果:" << endl;
	my_lastOrderTraverse(root);
	cout << endl;

	return 0;
}



