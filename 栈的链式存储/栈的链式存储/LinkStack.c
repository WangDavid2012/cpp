#include "LinkStack.h"



int Size_LinkStack(LinkStack * stack)
{
    if (stack == NULL)
        return -1;
    return stack->size;
}

void Free_LinkStack(LinkStack * stack)
{
    if (stack == NULL)
        return;
    free(stack);
}

LinkStack * Init_LinkStack()
{
    LinkStack *stack = (LinkStack*)malloc(sizeof(LinkStack));
    stack->head.next = NULL;
    stack->size = 0;
    return stack;
}

void Push_LinkStack(LinkStack * stack, StackNode * node)
{
    if (stack == NULL)
        return;
    if (node == NULL)
        return;
    node->next = stack->head.next;
    stack->head.next = node;
    stack->size++;

}

int Pop_LinkStack(LinkStack * stack, StackNode ** node)
{
    if (stack == NULL)
        return -1;
    if (stack->size == 0)
        return -1;
    *node = stack->head.next;
    stack->head.next = stack->head.next->next;

    return stack->size--;

   
}
