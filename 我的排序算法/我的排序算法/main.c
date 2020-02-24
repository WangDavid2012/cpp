#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//����ʱ����������
#include <math.h>
#include <sys/timeb.h>
#include "sort.h"

#define NUMBER 1000

//��ȡϵͳʱ��,��ȷ������
long long getSystemTime()
{
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}

//���������
void randNumber(int* array, int len)
{
    int i;
    //��������
    srand((unsigned)time(NULL));
    for (i = 0; i < len; ++i)
    {
        //����һ��С��len�������
        array[i] = rand() % len;
    }
}




int main()
{

    int i, j;
    int array[6][NUMBER];
    long long t_start, t_end, t_used;

    //��������
    srand((unsigned)time(NULL));
    for (i = 0; i < NUMBER; ++i)
    {
        //����һ��С��len�������
        int number = rand() % NUMBER;
        for (j = 0; j < 6; ++j)
        {
            array[j][i] = number;
        }
    }

    //ð������
    t_start = getSystemTime();
    BubbleSort(array[0], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("ð������� %d �����������򣬺�ʱ: %lld ms\n", NUMBER, t_used);

    //��������
    t_start = getSystemTime();
    insertionSort(array[2], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("��������� %d �����������򣬺�ʱ: %lld ms\n", NUMBER, t_used);

    //ϣ������
    t_start = getSystemTime();
    shellSort(array[3], NUMBER);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("ϣ������� %d �����������򣬺�ʱ: %lld ms\n", NUMBER, t_used);

    //�鲢����
    int temp[NUMBER];
    t_start = getSystemTime();
    mergeSort(array[4], 0, NUMBER - 1, temp);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("�鲢����� %d �����������򣬺�ʱ: %lld ms\n", NUMBER, t_used);

    //��������
    t_start = getSystemTime();
    quickSort(array[5], 0, NUMBER - 1);
    t_end = getSystemTime();
    t_used = t_end - t_start;
    printf("��������� %d �����������򣬺�ʱ: %lld ms\n", NUMBER, t_used);

    system("pause");
    return 0;
}