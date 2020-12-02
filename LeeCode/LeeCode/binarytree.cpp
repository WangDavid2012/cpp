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

������������У���������Ҷ�ӣ��ֱ��� 9 �� 15�����Է��� 24

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/sum-of-left-leaves
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������

����һ�Ŷ���������Ҷ�ӽڵ��ֵ��
	��������Ҷ�ӽڵ���ж�������
		1������ڵ�
		2������ڵ�û���ӽڵ�
	Ȼ�����ݴ������ݹ�
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
        if (root->left) { //���ӽڵ�
            if (root->left->left || root->left->right) {}
            else //Ҷ��
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