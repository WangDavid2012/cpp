#pragma once
#include <stdio.h>
#include <stdlib.h>



//��Ҫʵ�����¼�������ð�����򣬲�������ѡ������ϣ������

void BubbleSort(int array[], int lenth);

//ѡ������(��������)
void selectionSort(int *array, int len);

//���������㷨(��������)
void insertionSort(int *array, int len);



//ϣ������
void shellSort(int *array, int len);

//��������
void quickSort(int s[], int l, int r);

//�鲢����
void mergeSort(int a[], int first, int last, int temp[]);