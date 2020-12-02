//#include <thread>
//#include <atomic>
//#include <iostream>
//
//using namespace std;
//
//#define COUNT   10000000
//
//static  void inc(atomic<int> *p)
//{
//	for (int i = 0; i < COUNT; i++) {
//		(*p)++;
//	}
//}
//
//void threadDataRacing(void)
//{
//	atomic<int> a(0);
//	thread ta(inc, &a);
//	thread tb(inc, &a);
//	ta.join();
//	tb.join();
//	cout << "a=" << a << endl;
//}
//
//int atomic_test()
//{
//	threadDataRacing();
//	return  0;
//}
//
