#include <iostream>
using namespace std;


class C1
{
public:
    int i;
    int j;
    int k;
};
class C2
{
public:
    int i;
    int j;
    int k;
    static int m;
public:
    int getK() const { return k; }
    void setK(int val) { k = val; }
};

class S1
{
public:
    int i;
    int j;
    int k;
};
class S2
{
public:
    int i;
    int j;
    int k;
    static int m;
};
int main()
{
    cout << "c1:    " << sizeof(C1) << endl;
    cout << "c2:    " << sizeof(C2) << endl;
    cout << "S1:    " << sizeof(S1) << endl;
    cout << "S2:    " << sizeof(S2) << endl;
    getchar();
    return 0;

}
//执行结果：全部是12
//以上执行结果说明：
//C++类对象中的成员变量和成员函数是分开存储的
//普通成员变量，存储于对象中，与struct变量有相同的内存布局和字节对齐方式
//静态成员变量，存储于全局数据区中
//成员函数，存储于代码段中