#include <thread>
#include <iostream>

using namespace std;

struct  God{
    void    create(const char* anything){
        cout << "create " << anything << endl;
    }
};

void    threadRunMemberFunction(void){
    God         god;
    thread*     t   = new thread( &God::create, god, "the world" );
    t->join();
    delete  t;
}

int run_number_func_test(){
    threadRunMemberFunction();
    return  0;
}

