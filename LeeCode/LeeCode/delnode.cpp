#include "node.h"
#include <stdlib.h>


/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
/************************************************************************/
/* ���дһ��������ʹ�����ɾ��ĳ�������и����ģ���ĩβ���ڵ㡣���뺯����Ψһ����Ϊ
Ҫ��ɾ���Ľڵ� ��

����һ������ -- head = [4,5,1,9]�������Ա�ʾΪ:

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/delete-node-in-a-linked-list
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע�������� */
/************************************************************************/




void deleteNode(ListNode *node)
{
    struct ListNode n1 = { 4, nullptr };
    struct ListNode n2 = { 5, nullptr };
    struct ListNode n3 = { 1, nullptr };
    struct ListNode n4 = { 9, nullptr };
    Head *head = (Head*)malloc(sizeof(Head));
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    head->node.next = &n1;
    head->size = 4;

    struct ListNode *tmpnode = &(head->node);

    for (; tmpnode->next != nullptr; tmpnode = tmpnode->next) {
        if (tmpnode->next->val == node->val) {
            if (tmpnode->next->next == nullptr)
                return;
            tmpnode->next = tmpnode->next->next;

        }
    }
	system("pause");
    return;
}






