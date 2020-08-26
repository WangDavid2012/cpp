#include <iostream>

using namespace std;

/*********************
关于左值和右值的定义：
这个部分先给出lvalue和rvalue的一个简单定义。文章下面将会详细描述。
lvalue（locator value）代表一个在内存中占有确定位置的对象（换句话说就是有一个地址）。
rvalue通过排他性来定义，每个表达式不是lvalue就是rvalue。
因此从上面的lvalue的定义，rvalue是在不在内存中占有确定位置的表达式。

左值与右值这两概念是从 c 中传承而来的，在 c 中，
左值---指的是既能够出现在等号左边也能出现在等号右边的变量(或表达式)，
右值---指的则是只能出现在等号右边的变量(或表达式).
**/
class A
{
public:
    void foo() const {
        std::cout << "A::foo() const\n";
    }
    void foo() {
        std::cout << "A::foo()\n";
    }
};

A bar()
{
    return A();
}
const A cbar()
{
    return A();
}

/*****************************************************
*******************暂时不太理解
在 main 函数的第二个调用实际上调用的是 A 的 foo () const 方法，
因为 cbar 返回的是 const A 类型，这是与 A 不同的。
这正是上个引用中最后一句话的意思。也可以注意到 cbar 返回的是一个右值。
因此这也是一个 cv修饰的右值的例子。
**********************************************/
int lvalue_test0()
{
    bar().foo();  //调用foo
    cbar().foo(); //调用foo const
    return 0;
}

/****************
在 c++ 中，每一个表达式都会产生一个左值，或者右值，
	相应的，该表达式也就被称作“左值表达式"， "右值表达式"。
对于基本数据类型来说(primitive types)，左值右值的概念和 c 没有太多不同，
不同的地方在于自定义的类型，而且这种不同比较容易让人混淆:
1) 对于基础类型，右值是不可被修改的(non-modifiable)，
	也不可被 const, volatile 所修饰(cv-qualitification ignored)
2) 对于自定义的类型(user-defined types)，右值却允许通过它的成员函数进行修改。

*/
class cs
{
public:
    cs(int i) : i_(i) {
        cout << "cs(" << i << ") constructor!" << endl;
    }
    ~cs() {
        cout << "cs destructor,i(" << i_ << ")" << endl;
    }

    cs &operator=(const cs &other) {
        i_ = other.i_;
        cout << "cs operator=()" << endl;
        return *this;
    }

    int get_i() const {
        return i_;
    }
    void change(int i) {
        i_ = i;
    }

private:
    int i_;
};

cs get_cs()
{
    static int i = 0;
    return cs(i++);
}

int lvalue_test1()
{
    // 合法
    (get_cs() = cs(2)).change(323);
    get_cs() = cs(2);// operator=()
    get_cs().change(32);

    return 0;
}