#include <thread>
#include <iostream>

using namespace std;

void    threadRunLambda(void){
    int         a   = 100,
                b   = 200;
    thread*     t   = new thread( [](int ia, int ib){
                        cout << (ia + ib) << endl;
                    },
                    a,
                    b );

    t->join();
    delete  t;
}

int lambda_test01(){
    threadRunLambda();
    return  0;
}

