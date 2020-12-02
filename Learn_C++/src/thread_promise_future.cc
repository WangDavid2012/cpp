#include <iostream>
#include <thread>
#include <string>
#include <future>

using namespace std;

promise<string> val;
static  void
threadPromiseFuture(){
    thread  ta([](){
                future<string>  fu  = val.get_future();
                cout << "waiting promise->future" << endl;
                cout << fu.get() << endl;
            });
    thread  tb([](){
                this_thread::sleep_for( chrono::milliseconds(100) );
                val.set_value("promise is set");
            });
    ta.join();
    tb.join();
}

int future_test(){
    threadPromiseFuture();
    return  0;
}

