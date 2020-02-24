#include "sort.h"

//不自己实现一遍，理解的不是那么深入
void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}



//注意：第一次起泡，将队列中的最大值找到，并放到末尾
// 理解错误的地方是------ 原来一直理解成，一次起泡，将最小值取出，然后放到最左侧--错误
// time:2019/02/20 
// david
void BubbleSort(int array[],int lenth)
{
    for (int i = 0; i < lenth; i++)
    {
        for (int j = 0; j+1<lenth-i; j++)
        {
            if (array[j] > array[j+1])
            {
                swap(&array[j],&array[j+1]);
            }
        }
    }
}

void selectionSort(int * array, int len)
{
}

void insertionSort(int * array, int len)
{
}

void shellSort(int * array, int len)
{
}

void quickSort(int s[], int l, int r)
{
}

void mergeSort(int a[], int first, int last, int temp[])
{
}
