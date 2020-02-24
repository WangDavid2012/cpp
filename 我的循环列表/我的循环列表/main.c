#include <stdlib.h>
#include <stdio.h>
#include "CircleLinkList.h"

typedef struct Person
{
    CircleLinkNode node;
    char name[64];
    int age;
}Person;

void MyPrint(CircleLinkNode *node)
{
    Person *p = (Person*)node;
    printf("the name is %s,the age is %d.\n",p->name,p->age);

}

int MyCompare(CircleLinkNode *node1, CircleLinkNode *node2)
{
    Person *p1 = (Person *)node1;
    Person *p2 = (Person *)node2;
    return strcmp(p1->name,p2->name);
}


int main()
{
    Person p1, p2, p3, p4, p5;
    strcpy(p1.name, "aaa");
    strcpy(p2.name, "bbb");
    strcpy(p3.name, "ccc");
    strcpy(p4.name, "ddd");
    strcpy(p5.name, "eee");
    p1.age = 1;
    p2.age = 2;
    p3.age = 3;
    p4.age = 4;
    p5.age = 5;


    CircleLinkList *clist = Init_CircleLinkList();
    Insert_CircleLinkList(clist, 0, (CircleLinkNode *)&p1);
    Insert_CircleLinkList(clist, 1, (CircleLinkNode *)&p2);
    Insert_CircleLinkList(clist, 2, (CircleLinkNode *)&p3);
    Insert_CircleLinkList(clist, 3, (CircleLinkNode *)&p4);
    Insert_CircleLinkList(clist, 4, (CircleLinkNode *)&p5);

    Print_CircleLinkList(clist, MyPrint);

    //测试显示，index的值是2，表示链表从0开始排序
    int index = RemoveByValue_CircleLinkList(clist,(CircleLinkNode *)&p3,MyCompare);
    int size = Size_CircleLinkList(clist);


    printf("the index value is %d\n",index);
    printf("the clist size is %d\n",size);

    RemoveByPos_CircleLinkList(clist,3);
    Print_CircleLinkList(clist, MyPrint);
  
    system("pause");
    return 0;
}

