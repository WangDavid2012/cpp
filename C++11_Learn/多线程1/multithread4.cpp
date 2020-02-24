#include <windows.h>
#include <process.h>
#include <stdio.h>

//stack:
struct Node
{
	struct Node *next;
	int data;
};
struct Stack
{
	struct Node *head;
#ifdef _DEBUG
	CRITICAL_SECTION critical_sec;
#endif

	Stack()
	{
		head = NULL;
#ifdef _DEBUG
		InitializeCriticalSection(&critical_sec);
#endif
	}
	~Stack()
	{
		if (head != NULL)
		{
			if (NULL == head->next)
			{
				delete head;
				head = NULL;
			}
			else
			{
				Node *p = head;
				Node *q = head->next;

				while (q != NULL)
				{
					delete p;
					p = q;
					q = q->next;
				};
				delete p;
				p = NULL;
			}
		}
#ifdef _DEBUG
		DeleteCriticalSection(&critical_sec);
#endif
	}
	void Push(int num)
	{
		//enter critical section, add a new node and then     
#ifdef _DEBUG
		EnterCriticalSection(&critical_sec);
#endif
		Node * node = new Node();
		node->next = head;
		node->data = num;
		head = node;
		printf("Stack:%d\n", num);
		//leave critical section 
#ifdef _DEBUG
		LeaveCriticalSection(&critical_sec);
#endif
	}
	int Pop()
	{
#ifdef _DEBUG
		EnterCriticalSection(&critical_sec);
#endif
		int result = 0;
		if (head != NULL)
		{
			result = head->data;
			if (head->next != NULL)
			{
				Node *temp = head->next;
				delete head;
				head = temp;
			}
			else
				head = NULL;
		}
#ifdef _DEBUG
		LeaveCriticalSection(&critical_sec);
#endif
		return result;
	}
};


//test:
unsigned  __stdcall Thread1(void * pVoid)
{
	Stack *stack = ((Stack*)pVoid);
	for (int i = 200; i < 220; ++i)
	{
		stack->Push(i);
	}
	return 1;
}
unsigned __stdcall Thread2(void *pVoid)
{
	Stack *stack = ((Stack*)pVoid);
	for (int i = 0; i < 20; ++i)
	{
		stack->Push(i);
	}
	return 1;
}


int main()
{
	Stack stack;
	stack.Push(1000);
	stack.Push(1000);

	HANDLE   hth1;
	unsigned  uiThread1ID;

	hth1 = (HANDLE)_beginthreadex(NULL,         // security
		0,										// stack size
		Thread1,
		(void*)&stack,							// arg list
		CREATE_SUSPENDED,						// so we can later call ResumeThread()
		&uiThread1ID);

	if (hth1 == 0)
		printf("Failed to create thread 1\n");

	DWORD   dwExitCode;

	GetExitCodeThread(hth1, &dwExitCode); // should be STILL_ACTIVE = 0x00000103 = 259
	printf("initial thread 1 exit code = %u\n", dwExitCode);



	HANDLE   hth2;
	unsigned  uiThread2ID;

	hth2 = (HANDLE)_beginthreadex(NULL,         // security
		0,										// stack size
		Thread2,
		(void*)&stack,							 // arg list
		CREATE_SUSPENDED,					// so we can later call ResumeThread()
		&uiThread2ID);

	if (hth2 == 0)
		printf("Failed to create thread 2\n");

	GetExitCodeThread(hth2, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
	printf("initial thread 2 exit code = %u\n", dwExitCode);

	ResumeThread(hth1);
	ResumeThread(hth2);

	WaitForSingleObject(hth1, INFINITE);
	WaitForSingleObject(hth2, INFINITE);

	// 刺探 指定线程(通过线程的HANDLE) 是否己经结束, 
	//exitCode1中存储线程状态,若正在运行,值为STILL_ACTIVE 
	//若己经结束,值为 线程的返回值(即 return 后的值)
	// #define STATUS_PENDING                   ((DWORD   )0x00000103L) 
	GetExitCodeThread(hth1, &dwExitCode);
	printf("thread 1 exited with code %u\n", dwExitCode);

	GetExitCodeThread(hth2, &dwExitCode);
	printf("thread 2 exited with code %u\n", dwExitCode);

	CloseHandle(hth1);
	CloseHandle(hth2);
	getchar();
	printf("Primary thread terminating.\n");
}

#if 0

BOOL   GetExitCodeThread(

	HANDLE        hThread,               // in,线程handle,也就是CreateThread()的返回值
	LPDWORD      lpExitCode               //out,存储线程结束代码,也就是线程的返回值
	);

// 说明: 此函数调用成功返回TRUE, 失败返回FALSE, 只表示这个函数是否调用成功而己.
// 	不能根据返回值来判断一个线程是否结束, 而要根据 lpExitCode的值来确定,
// 	lpExitCode  值STILL_ACTIVE 表示线程正在运行.
// 	若线程己经结束, 则lpExitCode中存储指定线程的返回值.
// 	例:

	/*
	* ExitCode.c
	*
	* Sample code for "Multithreading Applications in Win32"
	* This is from Chapter 2, Listing 2-2
	*
	* Start two threads and try to exit
	* when the user presses a key.
	*/

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

	DWORD WINAPI ThreadFunc(LPVOID);

	int main()
	{
		HANDLE hThrd1;
		HANDLE hThrd2;
		DWORD exitCode1 = 0;
		DWORD exitCode2 = 0;
		DWORD threadId;

		//创建成功,返回一个HANDLE,对于此线程的操作函数,几乎都使用此HANDLE
		hThrd1 = CreateThread(NULL,
			0,                                            //堆栈大小,0取默认值1MB
			ThreadFunc,                          //线程函数地址
			(LPVOID)1,                           //线程的传入参数
			0,                                   //0 表示线程一旦创建 立即执行
			&threadId);                          //线程ID,一般为 向线程发送消息时用,
		if (hThrd1)
			printf("Thread 1 launched/n");

		//
		hThrd2 = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)2,
			0,
			&threadId);
		if (hThrd2)
			printf("Thread 2 launched/n");


		// Keep waiting until both calls to
		// GetExitCodeThread succeed AND
		// neither of them returns STILL_ACTIVE.
		// This method is not optimal - we'll
		// see the correct way in Chapter 3.
		for (;;)
		{
			printf("Press any key to exit../n");
			getch();                     // 按任意键继续
			 // 刺探 指定线程(通过线程的HANDLE) 是否己经结束, 
			//exitCode1中存储线程状态,若正在运行,值为STILL_ACTIVE 
			//若己经结束,值为 线程的返回值(即 return 后的值)
			GetExitCodeThread(hThrd1, &exitCode1);
			GetExitCodeThread(hThrd2, &exitCode2);
			if (exitCode1 == STILL_ACTIVE)
				puts("Thread 1 is still running!");
			if (exitCode2 == STILL_ACTIVE)
				puts("Thread 2 is still running!");
			if (exitCode1 != STILL_ACTIVE
				&& exitCode2 != STILL_ACTIVE)
				break;
		}

		CloseHandle(hThrd1);                //线程核心对象的引用计数 减1
		CloseHandle(hThrd2);

		printf("Thread 1 returned %d/n", exitCode1);
		printf("Thread 2 returned %d/n", exitCode2);

		return EXIT_SUCCESS;
	}


	/*
	* Take the startup value, do some simple math on it,
	* and return the calculated value.
	*/
	DWORD WINAPI ThreadFunc(LPVOID n)
	{
		Sleep((DWORD)n * 1000 * 2);
		return (DWORD)n * 10;
	}


#endif