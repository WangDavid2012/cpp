#include <iostream>
using namespace std;

class Parent
{
public:
    Parent(int a)
    {
        this->a = a;
        cout << "parent  a  is " << a << endl;
    }
    void print()
    {
        cout << "parent ��ӡ a :" << a << endl;
    }
private:
    int a;

};
class Child : public Parent
{
public:
    Child(int b) :Parent(10)
    {
        this->b = b;
        cout << "Child  b  is " << b << endl;
    }
    void print()
    {
        cout << "Child ��ӡ b :" << b << endl;
    }
private:
    int b;

};


void howToPrint(Parent *base)
{
    base->print();   // һ�ֵ�����䣬�ж��ֱ�����̬

}
void howToPrint2(Parent &base)
{
    base.print();   // һ�ֵ�����䣬�ж��ֱ�����̬

}

//int main()
//{
//    Parent *base = NULL;
//    Parent p1(20);
//    Child c1(30);
//
//    base = &p1;
//    base->print();
//
//    base = &c1;
//    base->print();
//
//    Parent &base2 = p1;
//    base2.print();
//
//    Parent &base3 = c1;
//    base3.print();
//
//    howToPrint(&p1);
//    howToPrint(&c1);
//
//    howToPrint2(p1);
//    howToPrint2(c1);
//
//    getchar();
//    return 0;
//}

class HeroFighter
{
public:
    virtual int ackPower()
    {
        return 10;
    }
};
class AdvHeroFight : public HeroFighter
{
public:
    virtual int ackPower()
    {
        return HeroFighter::ackPower() * 2;
    }
};

class enemyFighter
{
public:
    int destoryPower()
    {
        return 15;
    }
};


void objPK(HeroFighter *hf, enemyFighter *enemyF)
{
 
    if (hf->ackPower() > enemyF->destoryPower())
    {
        cout << "Ӣ�۴�ܵ��ˣ�ʤ����" << endl;
    }
    else
    {
        cout << "Ӣ������" << endl;
    }
}
void main()
{
    HeroFighter hf;
    enemyFighter ef;
    objPK(&hf,&ef);
    AdvHeroFight advhf;
    objPK(&advhf,&ef);
    getchar();
}



/// ��̬������������
/// 1��Ҫ�м̳�
/// 2��Ҫ���麯����д
/// 3��Ҫ�и���ָ�루�������ã�ָ���������
/// ��̬�����ģʽ�Ļ�������̬�ǿ�ܵĻ���














