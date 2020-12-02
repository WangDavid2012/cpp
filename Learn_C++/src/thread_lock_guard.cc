#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

#define COUNT   100000

static  mutex   g_mutex;

static  void
inc(int *p ){
    for(int i = 0; i < COUNT; i++){
        //lock_guard<mutex>   _(g_mutex);
        unique_lock<mutex>   _(g_mutex);
        (*p)++;
    }
}

void    threadLockGuard(void){
    int         a = 0;
    thread      ta( inc, &a);
    thread      tb( inc, &a);
    ta.join();
    tb.join();
    cout << "a=" << a << endl;
}

int lockgard_test(){
    threadLockGuard();
    return  0;
}

