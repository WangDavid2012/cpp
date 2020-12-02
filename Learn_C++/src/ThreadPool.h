#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
/********************************************************
F&& f 这是一个万能引用

******************************************************/



class ThreadPool
{
public:

	// 构造函数，传入线程数
	ThreadPool(size_t threads);
	
	// 入队任务(传入函数和函数的参数)
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;
	// 一个最简单的函数包装模板可以这样写(C++11)适用于任何函数(变参、成员都可以)
	// template<class F, class... Args>
	// auto enqueue(F&& f, Args&&... args) -> decltype(declval<F>()(declval<Args>()...))
	// {    return f(args...); }
	// C++14更简单
	// template<class F, class... Args>
	// auto enqueue(F&& f, Args&&... args)
	// {    return f(args...); }


    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};



// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0; i < threads; ++i)
        workers.emplace_back(
        [this] {
        for(;;)
        {
            std::function<void()> task;

            {
				//当前线程被阻塞, 直到condition.notify_one()调用,
				//如果lambda返回false,wait会解锁互斥元lock并置阻塞或等待状态,如果条件满足互斥元仍被锁定
				//而这里锁用的是std::unique_lock而不是std::lock_guard,是因为std::lock_guard不能在wait等待中解锁,并在之后重新锁定
				//如果互斥元在线程休眠期间始终被锁定,enqueue就无法锁定互斥元往下执行,则造成死锁
				
				std::unique_lock<std::mutex> lock(this->queue_mutex);
                this->condition.wait(lock,
                [this] { return this->stop || !this->tasks.empty(); });
                if(this->stop && this->tasks.empty())
                    return;
                task = std::move(this->tasks.front());
                this->tasks.pop();
            }

            task();
        }
    }
    );
}

//函数后跟throw()代表不抛出任何异常,跟thorw(...)代表可以抛出任何异常
// add new work item to the pool
template<class F, class... Args>										//... Args这个代表不限类型,不限数量
auto ThreadPool::enqueue(F &&f, Args &&... args)						//&&代表右值引用(可以用常量做参数)                   
-> std::future<typename std::result_of<F(Args...)>::type>				//<F(Args...)>代表这个是个返回类型为F,参数不确定多的函数;放入类型(如int)会报错
{
    using return_type = typename std::result_of<F(Args...)>::type;		//std::result_of::type 获得函数返回类型,直接用decltype会报错

    auto task = std::make_shared< std::packaged_task<return_type()> >(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]() {
            (*task)();
        });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker : workers)
        worker.join();
}

#endif
