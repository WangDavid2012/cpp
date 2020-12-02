#include <iostream>
#include <future>
#include <chrono>
#include <functional>



/**
	std::promise��C++11��������г��õ�һ���࣬�����std::futureʹ�á�
	����������һ���߳�t1�б���һ������typename T��ֵ��
	�ɹ���󶨵�std::future��������һ�߳�t2�л�ȡ
*/

void Thread_Fun1(std::promise<int> &p)
{
    //Ϊ��ͻ��Ч��������ʹ�߳�����5s
    std::this_thread::sleep_for(std::chrono::seconds(5));

    int iVal = 233;
    std::cout << "��������(int)��" << iVal << std::endl;

    //��������iVal
    p.set_value(iVal);
}

void Thread_Fun2(std::future<int> &f)
{
    //����������ֱ���յ��������std::promise�����������
    auto iVal = f.get();		//iVal = 233

    std::cout << "�յ�����(int)��" << iVal << std::endl;
}

int promise_test0()
{
    //����һ��std::promise����pr1���䱣���ֵ����Ϊint
    std::promise<int> pr1;
    //����һ��std::future����fu1����ͨ��std::promise��get_future()������pr1��
    std::future<int> fu1 = pr1.get_future();

    //����һ���߳�t1��������Thread_Fun1������pr1�����߳�����ִ��
    std::thread t1(Thread_Fun1, std::ref(pr1));
    //����һ���߳�t2��������Thread_Fun2������fu1�����߳�����ִ��
    std::thread t2(Thread_Fun2, std::ref(fu1));

    //�������߳̽���
    t1.join();
    t2.join();

    return 1;
}




//����һ���ɵ�����T
//��ͬ��typedef std::function<int(int)> T;
using T = std::function<int(int)>;

int Test_Fun(int iVal)
{
    std::cout << "Value is:" << iVal << std::endl;
    return iVal + 232;
}
// T ��һ������ָ��
void Thread_Fun3(std::promise<T> &p)
{
    //Ϊ��ͻ��Ч��������ʹ�߳�����5s
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "���뺯��Test_Fun" << std::endl;

    //���뺯��Test_Fun
    p.set_value(std::bind(&Test_Fun, std::placeholders::_1));
}

void Thread_Fun4(std::future<T> &f)
{
    //����������ֱ���յ��������std::promise�����������
    auto fun = f.get();		//iVal = 233

    int iVal = fun(1);

    std::cout << "�յ����������У������" << iVal << std::endl;
}

int promise_test1()
{
    //����һ��std::promise����pr1���䱣���ֵ����Ϊint
    std::promise<T> pr1;
    //����һ��std::future����fu1����ͨ��std::promise��get_future()������pr1��
    std::future<T> fu1 = pr1.get_future();

    //����һ���߳�t1��������Thread_Fun1������pr1�����߳�����ִ��
    std::thread t1(Thread_Fun3, std::ref(pr1));
    //����һ���߳�t2��������Thread_Fun2������fu1�����߳�����ִ��
    std::thread t2(Thread_Fun4, std::ref(fu1));

    //�������߳̽���
    t1.join();
    t2.join();

    return 1;
}