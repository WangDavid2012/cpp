#include <iostream>

using namespace std;

class Xushu
{
private:
    int a;
    int b;
public:
    Xushu()
    {
        this->a = 0;
        this->b = 0;
    }
    Xushu(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    ///<  ���ز�����+ david 2019/01/21
    Xushu operator+(Xushu &another)
    {
        ///< ���ʣ�����ֵ��һ�����ã���������ʹ�õ��Ǿֲ��������᲻��������
        ///< ��������ã��������⣬���Ժ��޸�
        Xushu temp(this->a+another.a,this->b+another.b);
        return temp;
    }
    ///< ���ز�����-
    Xushu operator-(Xushu &another)
    {
      /*  Xushu temp = new Xushu;*/
        Xushu temp(0,0);   ///< ��ô��ʼ���Ͷ�
        //Xushu temp();    ///< Ϊʲô��ô��ʼ���Ͳ���
        temp.a = this->a - another.a;
        temp.b = this->b - another.b;
        return temp;
    }
    ///< ���ز����� += 
    ///< += ���÷��� a += b;
    ///< ���ʹ�����������ģ��������ͣ�������ʵ����
    ///< ���ڷ���ֵ���� Ϊʲô��Ҫ����һ������
    Xushu &operator+=(Xushu& another)
    {
        this->a += another.a;
        this->b += another.b;
        return *this;     ///< Ϊʲô����*this
    }

    ///< ʵ�� a++ ����
    ///< Ŀǰ������� a++ �� ++a�����𣬲�֪��ΪʲôҪһ��ռλ��
    Xushu &operator ++(int)
    {
        this->a++;
        this->b++;
        return *this;
    }
    Xushu &operator ++ ()
    {
        ++ this->a;
        ++ this->b;
        return *this;
    }


    void print()
    {
        cout << "������:" << a << "+" << b << "i" << endl;
    }
};



int main()
{
    Xushu a(8,9);
    Xushu b(9, 5);
    a.print();
    b.print();
    Xushu c = a + b;
    c.print();
    c++;
    c.print();
    
    

    Xushu *d = new Xushu();
    //Xushu d = new Xushu(); //ʹ�����ַ�ʽ�Ǵ�ģ�new���ڴ���һ��ջ�ռ�
    delete d;

    Xushu e = a - b;
    e.print();

    getchar();
    return 0;
}