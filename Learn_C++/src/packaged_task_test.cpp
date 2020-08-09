#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>
#include <future>
#include <functional>
/********************************************************
packaged_task类模板也是定义于future头文件中，
它包装任何可调用 (Callable) 目标，
包括函数、 lambda 表达式、 bind 表达式或其他函数对象，使得能异步调用它，
其返回值或所抛异常被存储于能通过 std::future 对象访问的共享状态中。
简言之，将一个普通的可调用函数对象转换为异步执行的任务。模板声明如下：
template< class R, class ...Args >
class packaged_task< fn(Args...)>;
其中：

fn 是可以调用目标
Args 函数入参

通过packaged_task包装后，可以通过thread启动或者仿函数形式启动，
其执行结果返回值或所抛异常被存储于能通过 std::future 对象访问的共享状态中。



其实std::packaged_task和std::promise非常相似，
简单来说std::packaged_task<F>是对
std::promise<T= std::function<F>>中
T= std::function<F>这一可调对象(如函数、lambda表达式等)进行了包装，简化了使用方法。
并将这一可调对象的返回结果传递给关联的std::future对象。

注意：使用std::packaged_task关联的std::future对象保存的数据类型是可调对象的返回结果类型，
如示例函数的返回结果类型是int，那么声明为std::future<int>，
而不是std::future<int(int)>
**********************************************************/



using namespace std;
//普通函数
int Add(int x, int y)
{
	return x + y;
}


void task_lambda()
{
	//包装可调用目标时lambda
	packaged_task<int(int, int)> task([](int a, int b) { return a + b; });

	//仿函数形式，启动任务
	task(2, 10);

	//获取共享状态中的值,直到ready才能返回结果或者异常
	future<int> result = task.get_future();
	cout << "task_lambda :" << result.get() << "\n";
}

void task_thread()
{
	//包装普通函数
	std::packaged_task<int(int, int)> task(Add);
	future<int> result = task.get_future();
	//启动任务，非异步
	task(4, 8);
	cout << "task_thread :" << result.get() << "\n";

	//重置共享状态
	task.reset();
	result = task.get_future();

	//通过线程启动任务，异步启动
	thread td(move(task), 2, 10);
	td.join();
	//获取执行结果
	cout << "task_thread :" << result.get() << "\n";
}

int packaged_task_test0()
{
	task_lambda();
	task_thread();

	return 0;
}



int Test_Fun(int a, int b, int &c)
{
	//a=1,b=2,c=0

	//突出效果，休眠5s
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//c=233
	c = a + b + 230;

	return c;
}


//参见promise用法相比较既可以理解用法
int packaged_task_test1()
{
	//声明一个std::packaged_task对象pt1，包装函数Test_Fun
	std::packaged_task<int(int, int, int&)> pt1(Test_Fun);
	//声明一个std::future对象fu1，包装Test_Fun的返回结果类型，并与pt1关联
	std::future<int> fu1 = pt1.get_future();

	//声明一个变量
	int c = 0;

	//创建一个线程t1，将pt1及对应的参数放到线程里面执行
	std::thread t1(std::move(pt1), 1, 2, std::ref(c));

	//阻塞至线程t1结束(函数Test_Fun返回结果)
	int iResult = fu1.get();

	std::cout << "执行结果：" << iResult << std::endl;	//执行结果：233
	std::cout << "c：" << c << std::endl;				//c：233

	return 1;
}