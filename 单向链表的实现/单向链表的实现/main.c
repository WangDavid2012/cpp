#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

//����ʵ���˵�������ĸ���API�ӿڣ��ø���
//time:2019/02/15
//david
//�������Ժ������Ϊ��ϰ����

//֪ʶ�ܽ᣺
//�����ͷ���
//����ָ��Ķ��壬ʹ��typedef��ʽ
//�ص�������ʹ��
//����ĳ�ʼ����ʽ��ע�����������ݷ��룬��������ֻ��һ������

typedef struct PERSON
{
    LinkNode node;
    char name[64];
    int age;
}Person;

void MyPrint(LinkNode *node)
{
    Person *per = (Person *)node;
    printf("name:%s,age:%d\r\n",per->name,per->age);
}


int  CompareNode(LinkNode *node1, LinkNode *node2)
{
    Person *p1 = (Person*)&node1;
    Person *p2 = (Person*)&node2;

    return strcmp(p1->name, p2->name);
}



int main()
{
    printf("test start!\r\n");
    LinkList *list = initLinkList();
    Person p1, p2, p3, p4, p5;
    strcpy(p1.name,"aaa");
    strcpy(p2.name, "bbb");
    strcpy(p3.name, "ccc");
    strcpy(p4.name, "ddd");
    strcpy(p5.name, "eee");
    p1.age = 10;
    p2.age = 20;
    p3.age = 30;
    p4.age = 40;
    p5.age = 50;
    InsertLinkList(list, 0, (LinkNode*)&p1);
    InsertLinkList(list, 0, (LinkNode*)&p2);
    InsertLinkList(list, 0, (LinkNode*)&p3);
    InsertLinkList(list, 0, (LinkNode*)&p4);
    InsertLinkList(list, 0, (LinkNode*)&p5);

    PrintLinkList(list, MyPrint);
    printf("\n");
    printf("delete list node \r\n");
    RemoveLinkList(list,1);
    PrintLinkList(list, MyPrint);

    int value = FindLinkList(list,&p1, CompareNode);
    printf("the index is %d\n",value);

    FreeSpace_LinkList(list);
    system("pause");
    return 0;

}