#include <thread>
#include <iostream>

using namespace std;

class   MyThread : public thread{
public:
    MyThread() noexcept : thread(){};
    template<typename Callable, typename... Args>
        explicit
        MyThread(Callable&& func, Args&&... args) : 
            thread( std::forward<Callable>(func), 
                    std::forward<Args>(args)...){
        }
    ~MyThread() {  }
    //  disable copy constructors
    MyThread( MyThread& )       = delete;
    MyThread( const MyThread& ) = delete;

    MyThread& operator=(const MyThread&)    = delete;
};

void    threadInherit(void){
    int         a   = 100,
                b   = 200;
    MyThread*   t   = new MyThread( [](int ia, int ib){
                        cout << (ia + ib) << endl;
                    },
                    a,
                    b );

    t->join();
    delete  t;
}

int inherit_test(){
    threadInherit();
    return  0;
}

