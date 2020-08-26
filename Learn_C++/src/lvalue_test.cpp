#include <iostream>

using namespace std;

/*********************
������ֵ����ֵ�Ķ��壺
��������ȸ���lvalue��rvalue��һ���򵥶��塣�������潫����ϸ������
lvalue��locator value������һ�����ڴ���ռ��ȷ��λ�õĶ��󣨻��仰˵������һ����ַ����
rvalueͨ�������������壬ÿ�����ʽ����lvalue����rvalue��
��˴������lvalue�Ķ��壬rvalue���ڲ����ڴ���ռ��ȷ��λ�õı��ʽ��

��ֵ����ֵ���������Ǵ� c �д��ж����ģ��� c �У�
��ֵ---ָ���Ǽ��ܹ������ڵȺ����Ҳ�ܳ����ڵȺ��ұߵı���(����ʽ)��
��ֵ---ָ������ֻ�ܳ����ڵȺ��ұߵı���(����ʽ).
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
*******************��ʱ��̫���
�� main �����ĵڶ�������ʵ���ϵ��õ��� A �� foo () const ������
��Ϊ cbar ���ص��� const A ���ͣ������� A ��ͬ�ġ�
�������ϸ����������һ�仰����˼��Ҳ����ע�⵽ cbar ���ص���һ����ֵ��
�����Ҳ��һ�� cv���ε���ֵ�����ӡ�
**********************************************/
int lvalue_test0()
{
    bar().foo();  //����foo
    cbar().foo(); //����foo const
    return 0;
}

/****************
�� c++ �У�ÿһ�����ʽ�������һ����ֵ��������ֵ��
	��Ӧ�ģ��ñ��ʽҲ�ͱ���������ֵ���ʽ"�� "��ֵ���ʽ"��
���ڻ�������������˵(primitive types)����ֵ��ֵ�ĸ���� c û��̫�಻ͬ��
��ͬ�ĵط������Զ�������ͣ��������ֲ�ͬ�Ƚ��������˻���:
1) ���ڻ������ͣ���ֵ�ǲ��ɱ��޸ĵ�(non-modifiable)��
	Ҳ���ɱ� const, volatile ������(cv-qualitification ignored)
2) �����Զ��������(user-defined types)����ֵȴ����ͨ�����ĳ�Ա���������޸ġ�

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
    // �Ϸ�
    (get_cs() = cs(2)).change(323);
    get_cs() = cs(2);// operator=()
    get_cs().change(32);

    return 0;
}