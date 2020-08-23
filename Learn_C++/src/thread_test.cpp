#include <thread>
#include <string>
#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <mutex>
#include <chrono>

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using namespace std;

void myprint()
{
    std::cout << "hello" << endl;
}

void thread_test0()
{
    std::thread thread0(myprint);  //构造函数的参数是一个 函数指针
    //实质是阻塞主线上，让主线程在此处等待，当子线程完成后，然后与子线程会和，然后一起向下运行
    //实质是阻塞主线程，然后等待子线程执行完毕
    thread0.join();    //如果子线程没有执行完毕，但是主线程执行完毕，会出现问题。
    //detach() 之后，与主线程关联的子线程，会与主线程分离，此时主线程关闭，不会影响正在运行的子线程
    //当主进程执行完毕后，detach()的线程会转到后台进行，直到执行完毕
    //一旦调用detach()之后，子线程关联的主进程会和这个线程失去关联，这个子线程就会被C++运行时库接管
    //此时，这个子线程会驻留在后台运行，当这个子线程执行完毕后，由C++运行时库负责清理该线程相关的资源（守护线程）
}

void thread_test1()
{
}

vector<thread> g_list;
vector<std::shared_ptr<thread>> g_list2;




using namespace std;

mutex g_lock;          // 独占互斥量
void func()
{
    g_lock.lock();   // 锁
    cout << "Enter thread " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Leaving thread " << std::this_thread::get_id() << endl;
    g_lock.unlock();
}


void CreateThread()
{
    thread t(func);
    g_list.push_back(std::move(t));    // 将线程对象保存到容器中
    g_list2.push_back(std::make_shared<thread>(func));
}

//可以将线程对象保存到一个容器中，以保证线程对象的生命周期
int thread_test2()
{
    CreateThread();
    for (auto &thread : g_list) {
        thread.join();
    }
    for (auto &thread : g_list2) {
        thread->join();
    }

    return 0;
}
//线程不支持复制，但是可以将线程移动
int thread_test3()
{
    thread t(func);
    thread t1(std::move(t));   // 移动语义
    return 0;
}
int thread_test4()
{
    thread t1(func);
    thread t2(func);
    thread t3(func);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
