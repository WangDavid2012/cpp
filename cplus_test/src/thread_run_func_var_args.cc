#include <thread>
#include <cstdarg>
#include <cstdio>

using namespace std;

int     funcReturnInt(const char* fmt, ...){
    va_list     ap;
    va_start(ap, fmt);
    vprintf( fmt, ap );
    va_end(ap);
    return  0xabcd;
}
void    threadRunFunction(void){
    thread*     t   = new thread(funcReturnInt, "%d%s\n", 100, "\%");
    t->join();
    delete  t;
}

int var_args_test(){
    threadRunFunction();
    return  0;
}

