//std::mutex: ��ռ�Ļ�����, ���ܵݹ�ʹ��.
//std::timed_mutex : ����ʱ�Ķ�ռ������, ���ܵݹ�ʹ��.
//std::recursive_mutex : �ݹ黥����, ������ʱ����.
//std::recursive_timed_mutex : ����ʱ�ĵݹ黥����.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex g_lock;

void func()
{
	//����
	g_lock.lock();
	cout << "in id: " << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::seconds(1));
	cout << "out id: " << this_thread::get_id() << endl;
	//����
	g_lock.unlock();
}

void f()
{
	//lock_guard�ڹ���ʱ���Զ�����������,�����˳���������������ʱ�ͻ��Զ�����.
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