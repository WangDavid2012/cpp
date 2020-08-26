
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
    int offsize1 = (int) & (p->age) - int(p);   //age相对于结构体的偏移量
    int offsize2 = (int) & (((Teacher_t *)0)->age); //绝对地址0，age的偏移量
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
//  执行结果：偏移值都是64
//  因为是64位系统，所以struct A 大小是24


