#include <iostream>
using namespace std;


//指向整形数的指针
int test1()
{
    int a = 5;
    int *p = &a;
    cout << "a  = " << a << endl
         << "&a = " << &a << endl
         << "*p = " << *p << endl
         << "p  = " << p << endl
         << "&p = " << &p << endl;

    return 0;
}

//指向字符串的指针
int test2()
{
    char a[] = "hello";
    char *p = a;

    cout << "p = " << p << endl
         << "p = " << (void *)p << endl
         << "*p = " << *p << endl
         << "&p = " << &p << endl;

    for (int i = 0; i < 5; i++) {
        cout << "&a[" << i << "] = " << (void *)&a[i] << endl;
    }
    return 0;
}

//指向数组的指针
int test3()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    int *p = a;
    int **point = &p;

    cout << "a = " << a << endl
         << "p = " << p << endl
         << "&p = " << &p << endl
         << "point = " << point << endl
         << "&point = " << &point << endl;

    for (int i = 0; i < 5; i++) {
        cout << "&a[" << i << "] = " << &a[i] << endl;
    }
    return 0;
}


//指向指针的指针
int test4()
{
    char *a[] = { "Wel", "To", "China" };
    char **p = a;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < strlen(a[i]) + 1; j++) {
            cout << a[i][j] << "\t" << (void *)&a[i][j] << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        cout << "a[" << i << "] = " << (void *)a[i] << endl
             << "&a[" << i << "] = " << &a[i] << endl;
    }
    cout << "p  = " << p << endl
         << "&p = " << &p << endl;
    return 0;
}


//测试对指针变量赋值的方法，注意需要有 *
void test6(int *a)
{
    *a = 10;
    cout << "the addr of a is: " << a << endl;
}



//p的不同含义（指向整形数/执行字符串）
int point_test()
{
    cout << "指向整数的指针测试" << endl;
    test1();
    cout << "指向字符串的指针测试" << endl;
    test2();
    cout << "指向数组的指针测试" << endl;
    test3();
    cout << "指向指针的指针测试" << endl;
    test4();

    //测试指针变量赋值的方式
    int kk = 8;
    test6(&kk);
    cout << "the kk value is :" << kk << endl;

    system("pause");
    return 0;
}