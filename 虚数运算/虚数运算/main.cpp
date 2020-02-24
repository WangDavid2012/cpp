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
    ///<  重载操作符+ david 2019/01/21
    Xushu operator+(Xushu &another)
    {
        ///< 疑问，返回值是一个引用，我这里面使用的是局部变量，会不会有问题
        ///< 如果是引用，会有问题，测试后修改
        Xushu temp(this->a+another.a,this->b+another.b);
        return temp;
    }
    ///< 重载操作符-
    Xushu operator-(Xushu &another)
    {
      /*  Xushu temp = new Xushu;*/
        Xushu temp(0,0);   ///< 这么初始化就对
        //Xushu temp();    ///< 为什么这么初始化就不对
        temp.a = this->a - another.a;
        temp.b = this->b - another.b;
        return temp;
    }
    ///< 重载操作符 += 
    ///< += 的用法是 a += b;
    ///< 疑问关于输入参数的：引用类型，或者是实类型
    ///< 关于返回值问题 为什么需要返回一个引用
    Xushu &operator+=(Xushu& another)
    {
        this->a += another.a;
        this->b += another.b;
        return *this;     ///< 为什么返回*this
    }

    ///< 实现 a++ 运算
    ///< 目前还不理解 a++ 与 ++a的区别，不知道为什么要一个占位符
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
        cout << "虚数是:" << a << "+" << b << "i" << endl;
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
    //Xushu d = new Xushu(); //使用这种方式是错的，new用于创建一个栈空间
    delete d;

    Xushu e = a - b;
    e.print();

    getchar();
    return 0;
}