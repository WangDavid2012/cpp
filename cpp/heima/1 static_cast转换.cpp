#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main(void)
{
    double PI = 3.14159265;

    //int num = PI;
    int num2 = (int)PI; //C语言的转换方式
    //static_cast 增加可读性，代表普通类型的强制转换，
    //static_cast 实际上是又编译器在编译的时候就已经将PI解释成num类型了
    int num3 = static_cast<int>(PI);

    cout << "num2" << num2 << endl;
    cout << "num3" << num3 << endl;


    return 0;
}