/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
		 3
		/ \
	   9  20
		  /  \
		 15   7

在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-left-leaves
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

计算一颗二叉树的左叶子节点的值：
	首先是左叶子节点的判断条件：
		1、是左节点
		2、这个节点没有子节点
	然后依据此条件递归
*/

typedef struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    //TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

} TreeNode;

class Solution
{
public:
    int sumOfLeftLeaves(TreeNode *root) {
        if (root == nullptr) return 0;
        int res = 0;
        if (root->left) { //左子节点
            if (root->left->left || root->left->right) {}
            else //叶子
                res = root->left->val;
        }
        res += sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
        return res;


    }
};

int treetest1()
{
    TreeNode node1 = { 3, nullptr, nullptr};
    TreeNode node2 = { 9, nullptr, nullptr };
    TreeNode node3 = { 20, nullptr, nullptr };
    TreeNode node4 = { 15, nullptr, nullptr };
    TreeNode node5 = { 7, nullptr, nullptr };

    node1.left = &node2;
    node1.right = &node3;
    node3.left = &node4;
    node3.right = &node5;

    Solution so;
    int value = so.sumOfLeftLeaves(&node1);

    return value;

}