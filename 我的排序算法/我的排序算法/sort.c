#include "sort.h"

//���Լ�ʵ��һ�飬���Ĳ�����ô����
void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}



//ע�⣺��һ�����ݣ��������е����ֵ�ҵ������ŵ�ĩβ
// ������ĵط���------ ԭ��һֱ���ɣ�һ�����ݣ�����Сֵȡ����Ȼ��ŵ������--����
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
