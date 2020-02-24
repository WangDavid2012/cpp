#include <stdlib.h>
#include <stdio.h>
#include "Seq_CircleQueue.h"

//轻松完成了循环队列的线性存储方式
//david
//2019/02/18

typedef struct Person
{
    char name[32];
    int age;
}Person;


int main()
{
    Person p0 = { "aaa",10 };
    Person p1 = {"bbb",20};
    Person p2 = { "ccc",30 };
    Person p3 = { "ddd",40 };
    Person p4 = { "eee",50 };
    Person p5 = { "fff",60 };
    Person p6 = { "ggg",70 };
    Person p7 = { "hhh",80 };
    Person p8 = { "iii",90 };
    Person p9 = { "jjj",100 };

    CircleQueue *queue = Init_CircleQueue();
    int size = Put_CircleQueue(queue,&p0);
    printf("the size is %d\n",size);
    size = Put_CircleQueue(queue, &p1);
    printf("the size is %d\n", size);

    size = Put_CircleQueue(queue, &p2);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p3);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p4);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p5);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p6);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p7);
    printf("the size is %d\n", size);
    size = Put_CircleQueue(queue, &p8);
    printf("the size is %d\n", size);

    size = Put_CircleQueue(queue, &p9);
    printf("the size is %d\n", size);

    Person *p = NULL;

    
    printf("the new size is %d\n", Get_CircleQueue(queue, &p));
    printf("the name of p is %s\n",p->name);
   

    free(queue);
    system("pause");
    return 0;
}