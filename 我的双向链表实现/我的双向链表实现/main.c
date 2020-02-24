#include <stdlib.h>
#include <stdio.h>
#include "DoubleLink.h"

typedef struct Person
{
    DoubleLinkNode node;
    char name[32];
    int age;
}Person;

void MyPrintf(DoubleLinkNode * node)
{
    Person *p = (Person*)node;
    printf("the name is %s\n",p->name);
}

int main()
{
    Person p1, p2, p3, p4, p5;
    strcpy(p1.name,"aaa");
    strcpy(p2.name,"bbb");
    strcpy(p3.name,"ccc");
    strcpy(p4.name,"ddd");
    strcpy(p5.name, "wangzhanbei");
    p1.age = 1;
    p2.age = 2;
    p3.age = 3;
    p4.age = 4;

    DoubleLinkList *dlist = Init_DoubleLinkList();
    
    Insert_DoubleLinkList(dlist, 0,(DoubleLinkNode*)&p1);
    Insert_DoubleLinkList(dlist, 1, (DoubleLinkNode*)&p2);
    Insert_DoubleLinkList(dlist, 2, (DoubleLinkNode*)&p3);
    Insert_DoubleLinkList(dlist, 3, (DoubleLinkNode*)&p4);
    
    Print_DoubleLinkList(dlist,MyPrintf);
    printf("Insert Myname \n");
    Insert_DoubleLinkList(dlist, 0, (DoubleLinkNode*)&p5);
    Print_DoubleLinkList(dlist, MyPrintf);

    printf("Delete pos 0 node\n");
    Delete_DoubleLinkList(dlist,0);
    Print_DoubleLinkList(dlist, MyPrintf);

    free(dlist);

    system("pause");
    return 0;
}

