#include <thread>
#include <iostream>

using namespace std;

void    threadMove(void){
    int         a = 1;
    thread      t( [](int* pa){
                        for(;;){
                            *pa = (*pa * 33) % 0x7fffffff;
                            if ( ( (*pa) >> 30) & 1)    break;
                        }
                    }, &a);
    thread    t2  = move(t);
    t2.join();
    cout << "a=" << a << endl;
}

int move_test01(){
    threadMove();
    return  0;
}

