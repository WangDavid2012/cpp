#include <thread>
#include <iostream>

using namespace std;

void    threadMoveTerm(void){
    int         a = 1;
    thread      t( [](int* pa){
                        for(;;){
                            *pa = (*pa * 33) % 0x7fffffff;
                            if ( ( (*pa) >> 30) & 1)    break;
                        }
                    }, &a);
    thread      t2( [](){
                        int i = 0;
                        for(;;)i++;
                    } );
    t2  = move(t);
    cout << "should not reach here" << endl;
    t2.join();
}

int move_term_test(){
    threadMoveTerm();
    return  0;
}

