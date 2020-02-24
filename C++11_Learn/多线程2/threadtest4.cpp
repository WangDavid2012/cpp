//std::mutex: 独占的互斥量, 不能递归使用.
//std::timed_mutex : 带超时的独占互斥量, 不能递归使用.
//std::recursive_mutex : 递归互斥量, 不带超时功能.
//std::recursive_timed_mutex : 带超时的递归互斥量.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex g_lock;

void func()
{
	//上锁
	g_lock.lock();
	cout << "in id: " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "out id: " << this_thread::get_id() << endl;
	//解锁
	g_lock.unlock();
}

void f()
{
	//lock_guard在构造时会自动锁定互斥量,而在退出作用域后进行析构时就会自动解锁.
	lock_guard<std::mutex> lock(g_lock);
	cout << "in id: " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "out id: " << this_thread::get_id() << endl;
}

int test4321()
{
	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();

	std::thread t4(f);
	std::thread t5(f);
	std::thread t6(f);

	t4.join();
	t5.join();
	t6.join();
	getchar();
	return 0;
}