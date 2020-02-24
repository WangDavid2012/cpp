#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;

DWORD WINAPI Fun1Pro(LPVOID lpParameter);
DWORD WINAPI Fun2Pro(LPVOID lpParameter);

int tickets = 100;
HANDLE hMutex = NULL;


/*
	linux版本
	#include <pthread.h>
	pthread_create (thread, attr, start_routine, arg)

*/




int funcReturnInt(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	return 0xabcd;
}
void threadRunFunction(void) {
	//thread* t = new thread(funcReturnInt, "%d%s\n", 100, "\%");
	//t->join();
	//delete t;
}





void foo() {
	std::cout << "Hello C++11" << std::endl;
}

int test1() {
	std::thread thread(foo);  // 启动线程foo
	thread.join();            // 等待线程执行完成

	return 0;
}

void test21()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);//这句话要放在线程初始化之前初始化，因为如果  
											//放在之后注释的位置初始化可能导致线程线程已经开始执行了，并且执行到
											//WaitForSingleObject(hMutex, INFINITE);这段话，结果发现hMutex没有初始化
											//这样就会出现无法预料的问题。
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1 = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Pro, NULL, 0, NULL);
	threadRunFunction();
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	//hMutex = CreateMutex(NULL, FALSE, NULL);
	Sleep(1000);
	getchar();
}

DWORD WINAPI Fun1Pro(LPVOID lpParameter)
{
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(4);
			cout << "thread1 sell ticket : " << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}

DWORD WINAPI Fun2Pro(LPVOID lpParameter)
{
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(4);
			cout << "thread2 sell ticket : " << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;

}




//namespace std {
//	struct thread {
//		// native_handle_type 是连接 thread 类和操作系统 SDK API 之间的桥梁。
//		typedef implementation - dependent native_handle_type;
//		native_handle_type native_handle();
//		//
//		struct id {
//			id() noexcept;
//			// 可以由==, < 两个运算衍生出其它大小关系运算。
//			bool operator==(thread::id x, thread::id y) noexcept;
//			bool operator<(thread::id x, thread::id y) noexcept;
//			template<class charT, class traits>
//			basic_ostream<charT, traits>&
//				operator<<(basic_ostream<charT, traits>&out, thread::id id);
//			// 哈希函数
//			template <class T> struct hash;
//			template <> struct hash<thread::id>;
//		};
//		id get_id() const noexcept;
//		// 构造与析构
//		thread() noexcept;
//		template<class F, class… Args> explicit thread(F&f, Args&&… args);
//		~thread();
//		thread(const thread&) = delete;
//		thread(thread&&) noexcept;
//		thread& operator=(const thread&) = delete;
//		thread& operator=(thread&&) noexcept;
//		//
//		void swap(thread&) noexcept;
//		bool joinable() const noexcept;
//		void join();
//		void detach();
//		// 获取物理线程数目
//		static unsigned hardware_concurrency() noexcept;
//	}
//	namespace this_thead {
//		thread::id get_id();
//		void yield();
//		template<class Clock, class Duration>
//		void sleep_until(const chrono::time_point<Clock, Duration>& abs_time);
//		template<class Rep, class Period>
//		void sleep_for(const chromo::duration<Rep, Period>& rel_time);
//	}
//}