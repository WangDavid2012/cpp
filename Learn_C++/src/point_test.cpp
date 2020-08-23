#include <iostream>
using namespace std;


//ָ����������ָ��
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

//ָ���ַ�����ָ��
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

//ָ�������ָ��
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


//ָ��ָ���ָ��
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


//���Զ�ָ�������ֵ�ķ�����ע����Ҫ�� *
void test6(int *a)
{
    *a = 10;
    cout << "the addr of a is: " << a << endl;
}



//p�Ĳ�ͬ���壨ָ��������/ִ���ַ�����
int point_test()
{
    cout << "ָ��������ָ�����" << endl;
    test1();
    cout << "ָ���ַ�����ָ�����" << endl;
    test2();
    cout << "ָ�������ָ�����" << endl;
    test3();
    cout << "ָ��ָ���ָ�����" << endl;
    test4();

    //����ָ�������ֵ�ķ�ʽ
    int kk = 8;
    test6(&kk);
    cout << "the kk value is :" << kk << endl;

    system("pause");
    return 0;
}