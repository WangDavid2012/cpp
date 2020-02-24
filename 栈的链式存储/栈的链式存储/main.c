#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"


//历经艰难险阻，完成API接口和测试例程
//david
//time:2019/02/18
typedef struct Person
{
    //StackNode *node;  //注意，此种方式错误，一定注意
    StackNode node;
    char name[32];
    int age;
}Person;


int main()
{
    Person p1, p2, p3, p4, p5, p6, p7, p8;

    strcpy(p1.name,"aaa");
    strcpy(p2.name, "bbb");
    strcpy(p3.name, "ccc");
    strcpy(p4.name, "ddd");
    strcpy(p5.name, "eee");
    strcpy(p6.name, "fff");
    strcpy(p7.name, "ggg");
    strcpy(p8.name, "hhh");

    p1.age = 10;
    p2.age = 20;
    p3.age = 30;
    p4.age = 40;
    p5.age = 50;
    p6.age = 60;
    p7.age = 70;
    p8.age = 80;


    LinkStack *stack = Init_LinkStack();

    Push_LinkStack(stack, (StackNode*)&(p1));
    Push_LinkStack(stack, (StackNode*)&(p2));
    Push_LinkStack(stack, (StackNode*)&(p3));
    Push_LinkStack(stack, (StackNode*)&(p4));
    Push_LinkStack(stack, (StackNode*)&(p5));
    Push_LinkStack(stack, (StackNode*)&(p6));
    Push_LinkStack(stack, (StackNode*)&(p7));
    Push_LinkStack(stack, (StackNode*)&(p8));

    printf("the value of stack is %d\n", Size_LinkStack(stack));

    int size = Size_LinkStack(stack);

    //for (int i = 0; i < Size_SeqStack(stack); i++)
    for (int i = 0; i < size; i++)
    {
        Person *ptmp = NULL;
        Pop_LinkStack(stack, (StackNode*)&ptmp);
        printf("the name of p1 %s\n", (Person*)&ptmp->name);
    }
    Free_LinkStack(stack);
    system("pause");
    return 0;
}