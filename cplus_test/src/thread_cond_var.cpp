#include <thread>
#include <iostream>
#include <condition_variable>

using namespace std;

mutex               m;
condition_variable  cv;
void    threadCondVar(void){
#   define  THREAD_COUNT    10
    thread**            t   = new thread*[THREAD_COUNT];
    int                 i;
    for(i = 0; i < THREAD_COUNT; i++){
        t[i]    = new thread( [](int index){
                        unique_lock<mutex>  lck(m);
                        cv.wait_for(lck, chrono::hours(1000));
                        cout << index << endl;
                    }, i );
        this_thread::sleep_for( chrono::milliseconds(50));
    }
    for(i = 0; i < THREAD_COUNT; i++){
        lock_guard<mutex>   _(m);
        cv.notify_one();
    }
    for(i = 0; i < THREAD_COUNT; i++){
        t[i]->join();
        delete  t[i];
    }
    delete  t;
}

int main(){
    threadCondVar();
    return  0;
}

