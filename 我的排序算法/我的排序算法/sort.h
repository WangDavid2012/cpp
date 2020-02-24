#pragma once
#include <stdio.h>
#include <stdlib.h>



//主要实现以下几种排序，冒泡排序，插入排序，选择排序，希尔排序

void BubbleSort(int array[], int lenth);

//选择排序(升序排列)
void selectionSort(int *array, int len);

//插入排序算法(降序排列)
void insertionSort(int *array, int len);



//希尔排序
void shellSort(int *array, int len);

//快速排序
void quickSort(int s[], int l, int r);

//归并排序
void mergeSort(int a[], int first, int last, int temp[]);