#include <thread>
#include <iostream>

using namespace std;

void    threadSwap(void){
    int         a = 1;
    thread      t( [](int* pa){
                        for(;;){
                            *pa = (*pa * 33) % 0x7fffffff;
                            if ( ( (*pa) >> 30) & 1)    break;
                        }
                    }, &a);
    thread    t2;
    cout << "before swap: t=" << t.get_id() 
         << ", t2=" << t2.get_id() << endl;
    swap(t, t2);
    cout << "after swap : t=" << t.get_id() 
         << ", t2=" << t2.get_id() << endl;
    t2.join();
    cout << "a=" << a << endl;
}

int swap_test(){
    threadSwap();
    return  0;
}

