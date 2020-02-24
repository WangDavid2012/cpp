#include "SeqStack.h"

SeqStack * Init_SeqStack()
{
    SeqStack *stack = (SeqStack*)malloc(sizeof(SeqStack));
    stack->size = 0;
    for (int i = 0; i < MAXSIZE; i++)
    {
        stack->data[i] = NULL;
    }
    return stack;
}

void Push_SeqStack(SeqStack * stack, void * data)
{
    if (stack == NULL)
        return;
    if (data == NULL)
        return;
    if (stack->size == MAXSIZE)
        return;
    stack->data[stack->size] = data;
    stack->size++;
}

int Pop_SeqStack(SeqStack * stack)
{
    if (stack == NULL)
        return -1;
    if (stack->size == 0)
        return -1;
    stack->data[stack->size] = NULL;
    return  stack->size--;
}

void * Front_SeqStack(SeqStack * stack)
{
    if (stack == NULL)
        return NULL;
    if (stack->size == 0)
        return NULL;
    return stack->data[stack->size];
}

int Size_SeqStack(SeqStack * stack)
{
    if (stack == NULL)
        return -1;
    return stack->size;
}

int PosAndStore_SeqStack(SeqStack * stack, void ** data)
{
    if (stack == NULL)
        return -1;
    if (stack->size == 0)
        return -1;
    stack->size--;
    *data = stack->data[stack->size];
    return 0;
}

void Free_SeqStack(SeqStack * stack)
{
    if (stack == NULL)
        return;
    free(stack);
}

