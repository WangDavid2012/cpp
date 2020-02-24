#include "BinaryTree.h"

//ѧϰ������
//2019/02/20  david

//ʹ��#����������������
//ע�����뷽����AB##C##  ����һ���������������һ���ַ�һ���ַ���
//���룬����ִ���------------Ŀǰ��֪�������ԭ��
BinaryTree * Create_BinaryTree()
{
 /*   fflush(stdin);*/
    char ch;
    BinaryTree * node;
    scanf_s("%c",&ch);
    if (ch == '#')
    {
        return NULL;
    }
    else
    {
       node = (BinaryTree*)malloc(sizeof(BinaryTree));
       node->data = ch;
       node->lchild = Create_BinaryTree();
       node->rchild = Create_BinaryTree();
    }
    return node;
}


void PrintfBinaryTree(BinaryTree* root)
{
    if (root == NULL)
        return;
    printf("%c ", root->data);
    PrintfBinaryTree(root->lchild);
    PrintfBinaryTree(root->rchild);
}


//�������
void Preorder_Traversal(BinaryTree * root)
{
    if (root == NULL)
        return;
    printf("%c",root->lchild);
    Preorder_Traversal(root->lchild);
    Preorder_Traversal(root->rchild);
}

void Inorder_Traversal(BinaryTree * root)
{
    if (root == NULL)
        return;
    Inorder_Traversal(root->lchild);
    printf("%c",root->data);
    Inorder_Traversal(root->rchild);
}

void Postorder_Traversal(BinaryTree * root)
{
    if (root == NULL)
        return;
    Postorder_Traversal(root->lchild);
    Postorder_Traversal(root->rchild);
    printf("%c", root->data);
 
}

int Depth_BinaryTree(BinaryTree * root)
{
    if (root == NULL)
        return 0;
    int left = Depth_BinaryTree(root->lchild);
    int right = Depth_BinaryTree(root->rchild);

    return left >= right ? left + 1 : right + 1;
   
}

//һ���ڵ����������������ͬʱ�ǿ�ʱ������ڵ���Ҷ�ӽڵ�
void LeafCount_BinaryTree(BinaryTree * root,int *count)
{
    if (root == NULL)
        return;

    if (root->lchild == NULL && root->rchild == NULL)
    {
        (*count)++;   //ע��˴���*count++; ����д�����ԣ��������. ��Ϊ++���ȼ�����* ȡ��ַ
    }
        LeafCount_BinaryTree(root->lchild,count);
        LeafCount_BinaryTree(root->rchild,count);

}
