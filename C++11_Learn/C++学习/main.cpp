#include <iostream>
#include "debug.h"
using namespace std;

extern int test1();
extern int test2();
extern int test3();
extern int test4();
extern int test5();
extern int test6();
int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	getchar();
	return 0;
}