#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int main(void)
{
    double PI = 3.14159265;

    //int num = PI;
    int num2 = (int)PI; //C���Ե�ת����ʽ
    //static_cast ���ӿɶ��ԣ�������ͨ���͵�ǿ��ת����
    //static_cast ʵ�������ֱ������ڱ����ʱ����Ѿ���PI���ͳ�num������
    int num3 = static_cast<int>(PI);

    cout << "num2" << num2 << endl;
    cout << "num3" << num3 << endl;


    return 0;
}