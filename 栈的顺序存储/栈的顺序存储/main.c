#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

typedef struct Person
{
    char name[32];
    int age;
}Person;




int main()
{
    Person p1 = { "aaa",10 };
    Person p2 = { "bbb",20 };
    Person p3 = { "ccc",30 };
    Person p4 = { "ddd",40 };
    Person p5 = { "eee",50 };
    Person p6 = { "fff",60 };
    Person p7 = { "ggg",70 };
    Person p8 = { "hhh",80 };

    SeqStack *stack = Init_SeqStack();

    Push_SeqStack(stack, &(p1));
    Push_SeqStack(stack, &(p2));
    Push_SeqStack(stack, &(p3));
    Push_SeqStack(stack, &(p4));
    Push_SeqStack(stack, &(p5));
    Push_SeqStack(stack, &(p6));
    Push_SeqStack(stack, &(p7));
    Push_SeqStack(stack, &(p8));

    printf("the value of stack is %d\n",Size_SeqStack(stack));

    int size = Size_SeqStack(stack);

    //for (int i = 0; i < Size_SeqStack(stack); i++)
    for (int i = 0; i < size; i++)
    {
        Person *ptmp = NULL;
        PosAndStore_SeqStack(stack,&ptmp);
        printf("the name of p1 %s\n",(char*)&(ptmp->name));
    }
    

    Free_SeqStack(stack);
    system("pause");
    return 0;
}