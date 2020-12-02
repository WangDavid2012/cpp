#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <functional>
#include <queue>

using namespace std;

namespace _nmsp1 {
    //�ɱ��ģ�壺��Variadic Templates)������ģ���к���0�� �� ����� ģ����������﷨��Ҳ�ʹ�ͳģ�岻̫һ��������һ��...

    //һ���ɱ�κ���ģ��
    //��1.1���򵥷���
    //ֵ��ע������ݣ�
    //a)����һ������args��Ϊһ�� ����һ�� ������������Щ���������Ϳ��Ը�����ͬ��
    //�������T�������͵�ʱ�򣬲��ܰ�������һ�����ͣ���Ҫ����0�������ͬ�����ͣ�����Ȼ����Ӧ�Ĳ���argsҲӦ���Ƕ����ͬ���͵Ĳ�����
    //b)�� һ�������п�������0�����ģ�������������Щģ���������Ϊ��������ͣ�
    //c)���ע���������˳һ�£�
    //T��ߴ���...,���ԣ����ǳƺ�T���ɱ�����ͣ� ���������������һ����������ʵ������߰�������0�������ͬ�����ͣ�һ�����ͣ���
    //args���ɱ��βΣ���ȻT�������һ�����ͣ�����Ȼargs����ľ�һ���βΣ�
    //d)�ھ��庯���β��У�&��λ�ã����������������ĺ�ߡ�

    //��1.2����������չ��:չ����·�ȽϹ̶���һ�㶼���õݹ麯���ķ�ʽ��չ��������
    //Ҫ�������ڴ����д�У���һ��������չ����������һ��ͬ���ĵݹ���ֹ���������Ǿ���ͨ�������������Ѳ�����չ���ģ�

    template <typename... T>
    void myfunct1(T... args)  				//T��һ������   ��args��һ���β�
    {
        cout << sizeof...(args) << endl;    //sizeof...�ɱ������
        cout << sizeof...(T) << endl;
    }

    //----------------------------
    //�ݹ���ֹ ����
    void myfunct2()
    {
        cout << "������չ��ʱִ���˵ݹ���ֹ����myfunc2()..." << endl;
    }

    template <typename T, typename...U>
    void myfunct2(const T &firstarg, const U &... otherargs)   //һ��������һ�����������ֿɱ�κ���ģ��д�����ʺϲ�������չ��
    {
        //cout << sizeof...(otherargs) << endl;
        cout << "�յ��Ĳ���ֵΪ:" << firstarg << endl;
        myfunct2(otherargs...); //�ݹ���ã�ע��д��...
    }

    void func()
    {
        myfunct1();
        myfunct1(10, 20);
        myfunct1(10, 25.8, "abc", 68);

        myfunct2(10); //0
        myfunct2(10, "abc", 12.7);


        myfunct2(10, "abc", 12.7);
        myfunct2("abc", 12.7);
        myfunct2( 12.7);
        myfunct2();


    }
}
namespace _nmsp2 {
    //�����ɱ����ģ�壺����ģ�嶨���к���0�������ģ�������
    //��2.1��ͨ���ݹ�̳з�ʽչ��������
    template<typename...Args> class myclasst {}; //��ģ��

    template<> class myclasst<>   //0��ģ��������ػ��汾
    {
    public:
        myclasst()
        {
            printf("myclasst<>::myclasst()ִ����,this = %p\n", this);
        }
    };

    template <typename First, typename... Others>
    class myclasst<First, Others...> : private myclasst<Others...>   //ƫ�ػ�
    {
    public:
        myclasst() : m_i(0)
        {
            printf("myclasst::myclasst()ִ����,this = %p\n", this);
        }
        myclasst(First parf, Others...paro) : m_i(parf), myclasst<Others...>(paro...)
        {
            cout << "-------------------begin----------------" << endl;
            printf("myclasst::myclasst(parf,paro)ִ����,this = %p\n", this);
            cout << "m_i=" << m_i << endl;
            cout << "-------------------end------------------" << endl;
        }
        First m_i;
    };

    void func()
    {
        //myclasst<int, float, double> myc;
        myclasst<int, float, double> myc(12, 13.5f, 23);
        //����ȡ�ģ���׼���е�tuple��Ԫ�飩
    }
}

int args_test()
{
    _nmsp1::func();
    _nmsp2::func();
    return 1;
}