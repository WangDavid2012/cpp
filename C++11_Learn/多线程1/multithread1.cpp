#if 0

#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

#define THREAD_NUM 10

DWORD WINAPI PrintThreads(LPVOID);

int main()
{
	HANDLE hThread[THREAD_NUM];
	DWORD dwThreadID[THREAD_NUM];

	for (int i = 0; i < THREAD_NUM; ++i)
	{
		int isStartImmediate = 0;
		if (3 == i)
			isStartImmediate = CREATE_SUSPENDED;
		hThread[i] = CreateThread(NULL,                // security attributes that should be applied to the new thread, 
													   // this is for NT. Use NULL to get the default security attributes. Use NULL for win95 
			0,                                         // default size of 1MB can be passed by passing zero. 
			PrintThreads,                              // function name:address of the function where the new thread starts.
			(LPVOID)i,                         // parameter(void pointer): pointer to the 32 bit parameter that will be passed into the thread
			isStartImmediate,             // flags to control the creation of the thread. Passing zero starts the thread immediately. 
										  // Passing CREATE_SUSPENDED suspends the thread until the ResumeThread( ) function is called.
			&dwThreadID[i]                // pointer to a 32-bit variable that receives the thread identifier.
		);
		if (hThread[i])
		{
			printf("Thread launched successfully\n");
		}
	}
	printf("Start sleep 100, and let other thread excute\n");
	Sleep(100);

	printf("Start sleep 100, and thread 3 excute\n");
	ResumeThread(hThread[3]);

	Sleep(100);

	for (int i = 0; i < THREAD_NUM; ++i)
	{
		if (hThread[i])
		{
			CloseHandle(hThread[i]);    // You need to use this to release kernel objects when you are done using them. 
										// If a process exits without closing the thread handle, 
										// the operating system drops the reference counts for those objects. 
										// But if a process frequently creates threads without closing the handles, 
										// there could be hundreds of thread kernel objects lying around and these resource leaks can have a big hit on performance.
		}
	}

	getchar();
	return (0);
}

//function PrintThreads 
DWORD WINAPI PrintThreads(LPVOID num)
{
	for (int i = 0; i < 10; i++)
		printf("Thread Number is %d%d%d\n", num, num, num);
	return 0;
}

/*
线程相关的API接口函数用法
CreateThread() 调用成功返回句柄和一个id。
CloseHandle()  关闭一个打开的对象句柄，该对象句柄可以是线程句柄，也可以是进程、
				信号量等其他内核对象的句柄.

SuspendThread(HANDLE) 允许开发人员将HANDLE指定的线程挂起，如果要挂起的线程占有共享资源，
							则可能导致死锁。
ResumeThread(HANDLE)  恢复指定的线程。

TerminateThread() 立即终止线程的工作，不做任何清理工作。
ExitThread() 线程函数返回时回调用次函数，所以一般我们不去显示的调用。

ExitThread是推荐使用的结束一个线程的方法，当调用该函数时，
当前线程的栈被释放，然后线程终止，相对于TerminateThread函数来说，
这样做能够更好地完成附加在该线程上的DLL的清除工作.
但是ExitThread()会导致线程在清处构造器 / 自动变量之前就终止，
所以我们最好不要显示的调用ExitThread()。
*/



#endif