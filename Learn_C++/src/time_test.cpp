#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void timefun()
{
	long i;
	for (i = 0; i < 100000000; i++)
	{
		long a = 0;
		a = a + 1;
	}
}

//单位是秒，此种方法测试不够准确
void time_test1()
{
	time_t start, stop;
	start = time(NULL);
	timefun();
	stop = time(NULL);
	printf("Use Time:%ld\n", (stop - start));
}
void time_test2()
{
	double dur;
	clock_t start, end;
	start = clock();
	timefun();
	end = clock();
	dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));
}

//执行函数采用这种方式
