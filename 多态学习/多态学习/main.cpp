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
        cout << "parent 打印 a :" << a << endl;
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
        cout << "Child 打印 b :" << b << endl;
    }
private:
    int b;

};


void howToPrint(Parent *base)
{
    base->print();   // 一种调用语句，有多种表现形态

}
void howToPrint2(Parent &base)
{
    base.print();   // 一种调用语句，有多种表现形态

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
        cout << "英雄打败敌人，胜利！" << endl;
    }
    else
    {
        cout << "英雄牺牲" << endl;
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



/// 多态成立的条件：
/// 1、要有继承
/// 2、要有虚函数重写
/// 3、要有父类指针（父类引用）指向子类对象
/// 多态是设计模式的基础，多态是框架的基础














