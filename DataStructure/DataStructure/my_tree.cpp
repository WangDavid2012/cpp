
#include <iostream>
#include "my_tree.h"

using namespace std;

my_Node* createBinaryTree()
{
	my_Node *p;
	int ch;
	cin >> ch;
	if (ch == '#')     //�������Ҷ�ӽڵ㣬�����������������ֱ�ֵΪ#
	{
		p = NULL;
	}
	else
	{
		p = (my_Node*)malloc(sizeof(my_Node));
		p->data = ch;
		cout << "creat left tree!" << endl;
		p->Left = createBinaryTree();   //�ݹ鴴��������
		cout << "creat right tree!" << endl;
		p->Right = createBinaryTree();  //�ݹ鴴��������
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
//�������ڵ���ͳ��
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
//������Ҷ�ӽڵ���
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


//�����������Ĳ���
//1����������һ�����ڵ㣬ָ���
//2���ڸ��ڵ�Ļ����ϣ���������������������
//3��ע�⣬����������ʱ���������Ҷ�ӽڵ㣬���������ڵ�����뱾������Ϊ'#'
//4�������������ɹ����ڵ��Ա�������������
int my_tree_test()
{
	my_Node *root = NULL;
	root = createBinaryTree();
	printf("�����������ɹ�");
	cout << endl;

	cout << "�������ܽڵ���Ϊ��" << Nodenum(root) << endl;

	cout << "���������Ϊ��" << DepthOfTree(root) << endl;

	cout << "������Ҷ�ӽڵ���Ϊ��" << Leafnum(root) << endl;

	cout << "ǰ��������:" << endl;
	my_preOrderTraverse(root);
	cout << endl;

	cout << "����������:" << endl;
	my_inOrderTraverse(root);
	cout << endl;

	cout << "����������:" << endl;
	my_lastOrderTraverse(root);
	cout << endl;

	return 0;
}



