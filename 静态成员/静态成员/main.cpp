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
//ִ�н����ȫ����12
//����ִ�н��˵����
//C++������еĳ�Ա�����ͳ�Ա�����Ƿֿ��洢��
//��ͨ��Ա�������洢�ڶ����У���struct��������ͬ���ڴ沼�ֺ��ֽڶ��뷽ʽ
//��̬��Ա�������洢��ȫ����������
//��Ա�������洢�ڴ������