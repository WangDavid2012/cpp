#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

#define COUNT   100000

static  mutex   g_mutex;
static  void
inc(int *p ){
    thread_local int    i;
    for(; i < COUNT; i++){
        g_mutex.lock();
        (*p)++;
        g_mutex.unlock();
    }
}

void    threadMutex(void){
    int         a = 0;
    thread      ta( inc, &a);
    thread      tb( inc, &a);
    ta.join();
    tb.join();
    cout << "a=" << a << endl;
}

int mutxt_test(){
    threadMutex();
    return  0;
}

