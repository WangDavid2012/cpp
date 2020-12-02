#include <thread>
#include <string>
#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <mutex>
#include <chrono>
#include <time.h>

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using namespace std;
typedef std::function<void()> pFunction;


class CalculateTime
{
public:
    CalculateTime() {};
    float runTime(int threadnum, int countnum, pFunction pfunc);
    float runTime(pFunction pfunc);
private:
    vector<std::shared_ptr<thread>> m_pthreads;
};


void testfunc(unsigned char *in, unsigned int lenth, unsigned char *out)
{
    cout << "Thread " << this_thread::get_id() << endl;
    for (unsigned int i = 0; i < lenth; i++) {
        out[i] = in[i];
    }
}

float CalculateTime::runTime(int threadnum, int countnum, pFunction pfunc)
{
    vector<std::shared_ptr<thread>> g_pmthread;
    clock_t start, end;
    start = clock();

    for (int i = 0; i < threadnum; i++) {
        g_pmthread.push_back(std::make_shared<thread>([countnum, pfunc] { for (int j = 0; j < countnum, pfunc; j++); }));
    }
    for (auto &thread : g_pmthread) {
        thread->join();
    }
    end = clock();
    float dur = (float)(end - start);
    return (dur / CLOCKS_PER_SEC);
}

float CalculateTime::runTime(pFunction pfunc)
{
    vector<std::shared_ptr<thread>> g_pmthread;
    clock_t start, end;
    start = clock();

    for (int i = 0; i < 1024; i++) {
        g_pmthread.push_back(std::make_shared<thread>(pfunc));
    }
    for (auto &thread : g_pmthread) {
        thread->join();
    }
    end = clock();
    float dur = (float)(end - start);
    return (dur / CLOCKS_PER_SEC);
}




void multithread_time_test()
{
    unsigned char in[100];
    unsigned char out[100];
    std::function<void()> f1 = std::bind(testfunc, in, 100, out);

    CalculateTime *pCalTime = new CalculateTime();
    //float ftime = pCalTime->runTime(64, 3, f1);
    float ftime = pCalTime->runTime(f1);
    cout << ftime << endl;
}
