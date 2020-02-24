#include "BinaryTree.h"

//学习二叉树
//2019/02/20  david

//使用#创建法创建二叉树
//注意输入方法：AB##C##  创建一个二叉树，如果是一个字符一个字符的
//输入，会出现错误------------目前不知道错误的原因
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


//先序遍历
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

//一个节点的左子树和右子树同时是空时，这个节点是叶子节点
void LeafCount_BinaryTree(BinaryTree * root,int *count)
{
    if (root == NULL)
        return;

    if (root->lchild == NULL && root->rchild == NULL)
    {
        (*count)++;   //注意此处，*count++; 这种写法不对，会出问题. 因为++优先级高于* 取地址
    }
        LeafCount_BinaryTree(root->lchild,count);
        LeafCount_BinaryTree(root->rchild,count);

}
