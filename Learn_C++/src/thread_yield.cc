//#include <sys/time.h>
//#include <chrono>
//#include <thread>
//#include <iostream>
//#include <mutex>
//
//using namespace std;
//
//static  mutex   g_mutex;
//static  void    print_time(struct timeval t1, struct timeval t2, const char* word){
//    lock_guard<mutex>   _(g_mutex);
//    
//    struct timeval  tv;
//    tv.tv_sec   = t2.tv_sec - t1.tv_sec;
//    if (t2.tv_usec >= t1.tv_usec ){
//        tv.tv_usec  = t2.tv_usec - t1.tv_usec;
//    }
//    else{
//        tv.tv_sec--;
//        tv.tv_usec  = 1000000 + t2.tv_usec - t1.tv_usec;
//    }
//    double  elapsed = tv.tv_sec + tv.tv_usec / 1000000.0;
//    cout << word << " elapse " << elapsed << "s" << endl;
//}
//
//static  void    do_nothing(){}
//
//#define COUNT   1000000 * 10
//void    threadYield(void){
//    unsigned int    procs   = thread::hardware_concurrency(),
//                    i       = 0;
//    thread*     ta  = new thread( [](){
//                        struct timeval  t1, t2;
//                        gettimeofday(&t1, NULL);
//                        for(int i = 0, m = 13; i < COUNT; i++, m *= 17){
//                            this_thread::yield();
//                        }
//                        gettimeofday(&t2, NULL);
//                        print_time(t1, t2, "   with yield");
//                    } );
//    thread**    tb = new thread*[ procs ];
//    for( i = 0; i < procs; i++){
//        tb[i] = new thread( [](){
//                        struct timeval  t1, t2;
//                        gettimeofday(&t1, NULL);
//                        for(int i = 0, m = 13; i < COUNT; i++, m *= 17){
//                            do_nothing();
//                        }
//                        gettimeofday(&t2, NULL);
//                        print_time(t1, t2, "without yield");
//                    });
//    }
//    ta->join();
//    delete  ta;
//    for( i = 0; i < procs; i++){
//        tb[i]->join();
//        delete  tb[i];
//    };
//    delete  tb;
//}
//
//int yield_test(){
//    threadYield();
//    return  0;
//}
//
