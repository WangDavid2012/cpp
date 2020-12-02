#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

static  mutex   g_mutex;
static  void
threadPackagedTask(){
    auto    run = [=](int index){ 
                {
                    lock_guard<mutex>   _(g_mutex);
                    cout << "tasklet " << index << endl;
                }
                this_thread::sleep_for( chrono::seconds(10) );
                return  index * 1000;
    };
    packaged_task<int(int)>   pt1(run);
    packaged_task<int(int)>   pt2(run);

    thread  t1([&](){pt1(2);} );
    thread  t2([&](){pt2(3);} );
    
    int     f1  = pt1.get_future().get();
    int     f2  = pt2.get_future().get();
    cout << "task result=" << f1 << endl;
    cout << "task result=" << f2 << endl;

    t1.join();
    t2.join();
}

int packaged_test(){
    threadPackagedTask();
    return  0;
}

