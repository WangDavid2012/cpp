#include <thread>
#include <iostream>
#include <chrono>
#include <csignal>
#include <pthread.h>

using namespace std;
static  int     counter;

static  void    on_signal_term(int  sig){
    cout << "on SIGTERM:" << this_thread::get_id() << endl;
    pthread_exit(NULL);
}
void    threadPosixKill(void){
    signal(SIGTERM, on_signal_term);
    thread*     t   = new thread( [](){
                        while(true){
                            ++counter;
                        }
                    });
    pthread_t   tid = t->native_handle();
    cout << "tid=" << tid << endl;
    //  确保子线程已经在运行。
    this_thread::sleep_for( chrono::seconds(1) );
    pthread_kill(tid, SIGTERM);
    t->join();
    
    delete  t;
    cout << "thread destroyed." << endl;
}

int main(){
    threadPosixKill();
    return  0;
}

