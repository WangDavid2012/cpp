<<<<<<< HEAD
#include <iostream>

using namespace std;

extern int string_test();
extern int string_test3();
extern int transform_test();
extern int operator_test();
extern int shareptr_test();

extern void linklist_test();
extern void HandleTest();

int main()
{
	cout << "C++ learn !" << endl;
	linklist_test();
	HandleTest();

	shareptr_test();
	operator_test();
	transform_test();
	string_test();
	string_test3();
	system("pause");
	return 0;
}
=======
﻿#include <iostream>
#include <windows.h>
#include <direct.h>
#include "queue.h"
#include "min_heap.h"

using namespace std;

extern int string_test();
extern int string_test3();
extern int transform_test();
extern int operator_test();
extern int shareptr_test();
extern void linklist_test();
extern void HandleTest();
extern void thread_test0();
extern void thread_test1();
extern void multimap_test();
extern void  ofstream_test();
extern void filefunction_test();
extern void time_test1();
extern void time_test2();
extern void multithread_time_test();
extern void lambda_test0();
extern int promise_test0();
extern int promise_test1();
extern int queue_test();
extern int offset_test();
extern int threadpool_test();
extern  int args_test();
extern int result_of_test1();
extern int result_of_test2();

string AbsolutelyPath(const string &s) {
	char *cur = _getcwd(NULL, 0);
	int loc = 0;
	loc = s.rfind("\\");				//在字符串中查找第一个 \ 的位置
	string path = s.substr(0, loc);		//path = ../src
	_chdir(path.c_str());				//转到 ../src 目录下·
	string cfgAbsPath = _getcwd(NULL, 0);
	cfgAbsPath.append("\\").append(s.substr(loc + 1));
	_chdir(cur);
	free(cur);
	return cfgAbsPath;
}




int minheap_test() {
	int arr[] = { 7, 8, 2, 3, 4, 5, 1, 6, 9 };
	MinHeap<int> minheap(arr, 9);
	minheap.insert(13);
	minheap.display();
	return 0;
}


int main()
{
	cout << "******** Test ! *************" << endl;
	result_of_test1();
	result_of_test2();
	threadpool_test();
	minheap_test();
	queue_test();
	promise_test0();
	time_test1();
	time_test2();
	lambda_test0();
	multithread_time_test();
	ofstream_test();
	multimap_test();
	filefunction_test();
	linklist_test();
	HandleTest();
	string mypath = AbsolutelyPath("..\\src\\debug.h");
	shareptr_test();
	operator_test();
	transform_test();
	string_test();
	string_test3();
	system("pause");
	return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
