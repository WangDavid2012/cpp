#include <stdlib.h>
#include <stdio.h>
#include "BinaryTree.h"

int main()
{
    printf("Creat Binary Tree!\n");
    BinaryTree *tree = Create_BinaryTree();
    printf("printf binary tree!\n");
    PrintfBinaryTree(tree);
    printf("\n");

    Inorder_Traversal(tree);
    printf("\n");

    Postorder_Traversal(tree);
    printf("\n");
    int deep = Depth_BinaryTree(tree);
    printf("the deep of tree is %d\n",deep);

    int sum = 0;

    LeafCount_BinaryTree(tree,&sum);

    printf("the leaf count is %d\n",sum);

    system("pause");
    return 0;
}