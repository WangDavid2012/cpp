#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//利用时间生成种子
#include <math.h>
#include <sys/timeb.h>
#include "sort.h"

#define NUMBER 1000

//获取系统时间,精确到毫秒
long long getSystemTime()
{
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}

//生成随机数
void randNumber(int* array, int len)
{
    int i;
    //生成种子
    srand((unsigned)time(NULL));
    for (i = 0; i < len; ++i)
    {
        //生成一个小于len的随机数
        array[i] = rand() % len;
    }
}




int main()
{

    int i, j;
    int array[6][NUMBER];
    long long t_start, t_end, t_used;

    //生成种子
    srand((unsigned)time(NULL));
    for (i = 0; i < NUMBER; ++i)
    {
        //生成一个小于len的随机数
        int number = rand() % NUMBER;
        for (j = 0; j < 6; ++j)
        {
            array[j][i] = number;
        }
    }

    //冒泡排序
    t_start = getSystemTime();
    BubbleSort(array[0], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("冒泡排序对 %d 个数进行排序，耗时: %lld ms\n", NUMBER, t_used);

    //插入排序
    t_start = getSystemTime();
    insertionSort(array[2], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("插入排序对 %d 个数进行排序，耗时: %lld ms\n", NUMBER, t_used);

    //希尔排序
    t_start = getSystemTime();
    shellSort(array[3], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("希尔排序对 %d 个数进行排序，耗时: %lld ms\n", NUMBER, t_used);

    //归并排序
    int temp[NUMBER];
    t_start = getSystemTime();
    mergeSort(array[4], 0, NUMBER - 1, temp);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("归并排序对 %d 个数进行排序，耗时: %lld ms\n", NUMBER, t_used);

    //快速排序
    t_start = getSystemTime();
    quickSort(array[5], 0, NUMBER - 1);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("快速排序对 %d 个数进行排序，耗时: %lld ms\n", NUMBER, t_used);

    system("pause");
    return 0;
}