//#include <thread>
//#include <iostream>
//#include <mutex>
//
//using namespace std;
//
//#define COUNT   100000
//
//static  mutex g_mutex1, g_mutex2;
//static  void inc1(int *p)
//{
//	for (int i = 0; i < COUNT; i++) {
//		g_mutex1.lock();
//		(*p)++;
//		g_mutex1.unlock();
//		g_mutex2.lock();
//		//  do something.
//		g_mutex2.unlock();
//	}
//}
//static  void inc2(int *p)
//{
//	for (int i = 0; i < COUNT; i++) {
//		g_mutex2.lock();
//		//  do other thing.
//		g_mutex2.unlock();
//		g_mutex1.lock();
//		(*p)++;
//		g_mutex1.unlock();
//	}
//}
//
//void threadMutex(void)
//{
//	int a = 0;
//	std::thread  ta(inc1, &a);
//	std::thread  tb(inc2, &a);
//	ta.join();
//	tb.join();
//	cout << "a=" << a << endl;
//}
//
//int deadlock_test()
//{
//	threadMutex();
//	return  0;
//}
//
