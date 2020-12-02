#include <thread>
#include <iostream>

using namespace std;

#define COUNT   10000000
static  void
inc(int *p ){
    for(int i = 0; i < COUNT; i++){
        (*p)++;
    }
}

void    threadDataRacing(void){
    int         a = 0;
    thread      ta( inc, &a);
    thread      tb( inc, &a);
    ta.join();
    tb.join();
    cout << "a=" << a << endl;
}

int race_test(){
    threadDataRacing();
    return  0;
}

