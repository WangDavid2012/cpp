
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Teacher
{
    char name[64];
    int age;
    int p;
} Teacher_t;

struct A
{
    char c;
    double d;
    short s;
    int i;
};


int offset_test()
{
    Teacher_t t1;
    Teacher_t *p = NULL;
    p = &t1;
    int offsize1 = (int) & (p->age) - int(p);   //age����ڽṹ���ƫ����
    int offsize2 = (int) & (((Teacher_t *)0)->age); //���Ե�ַ0��age��ƫ����
    printf("offsize1:%d \n", offsize1);
    printf("offsize2:%d \n", offsize2);

    struct A a;
    printf("the lenth of struct A is:%d\n", sizeof(struct A));
    printf("char &c:%d\n \
                double &d:%d\n \
                short &s:%d\n \
                int &i:%d\n", \
           &a.c, &a.d, &a.s, &a.i);

    getchar();
    return 0;
}
//  ִ�н����ƫ��ֵ����64
//  ��Ϊ��64λϵͳ������struct A ��С��24


