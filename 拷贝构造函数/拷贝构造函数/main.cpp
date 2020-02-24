#include<iostream>
using namespace std;
class CExample
{
private:
    int a;
public:
    //���캯��
    CExample(int b)
    {
        a = b;
        printf("constructor is called\n");
    }
    //�������캯��
    CExample(const CExample & c)
    {
        a = c.a;
        printf("copy constructor is called\n");
    }
    //��������
    ~CExample()
    {
        cout << "destructor is called\n";
    }
    void Show()
    {
        cout << a << endl;
    }
};
int main()
{
    CExample A(100);
    CExample B = A;
    B.Show();
    getchar();
    return 0;
}
//���н����
//constructor is called
//copy constructor is called
//100