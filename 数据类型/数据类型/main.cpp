#include <iostream>
using namespace std;


int main()
{
    int a = 10;       //���߱�����������4���ֽڵ��ڴ�
    int b[10];         //���߱�����������4*10���ֽڵ��ڴ�


    ///< b+1 ��&b+1 �Ľ����һ��
    ///< ��Ϊb��&b��ָ���������Ͳ�һ��
    ///< b��ʾ����Ԫ�ص��׵�ַ
    ///< &b ��ʾ��������ĵ�ַ
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
//ִ�н����
//b: 0x0035FDE0
//b+1:0x0035FDE4
//&b:0x0035FDE0
//&b+1:0x0035FE08