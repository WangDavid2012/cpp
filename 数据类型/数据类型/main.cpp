#include <iostream>
using namespace std;


int main()
{
    int a = 10;       //告诉编译器，分配4个字节的内存
    int b[10];         //告诉编译器，分配4*10个字节的内存


    ///< b+1 和&b+1 的结果不一样
    ///< 因为b和&b所指的数据类型不一样
    ///< b表示数组元素的首地址
    ///< &b 表示整体数组的地址
    cout << "b: " << b << endl;
    cout << "b+1:   " << b + 1 << endl;
    cout << "&b:    " << &b << endl;
    cout << "&b+1:  " << &b + 1 << endl;

    cout << "sizeof(a): " << sizeof(a) << endl;
    cout << "sizeof(int *): " << sizeof(int *) << endl;
    cout << "sizeof(b): " << sizeof(b) << endl;
    cout << "sizeof(b[0]):  " << sizeof(b[0]) << endl;
    cout << "sizeof(*b):    " << sizeof(*b) << endl;


    getchar();
    return 0;
}
//执行结果：
//b: 0x0035FDE0
//b+1:0x0035FDE4
//&b:0x0035FDE0
//&b+1:0x0035FE08