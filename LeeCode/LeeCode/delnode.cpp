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
/* 请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点。传入函数的唯一参数为
要被删除的节点 。

现有一个链表 -- head = [4,5,1,9]，它可以表示为:

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/delete-node-in-a-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */
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






