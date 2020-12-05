#include "common.h"

// 定义个数组
typedef struct Array {
	int length; // 数组长度
	int count;  // 数组当前元素数 count
	int *pBase; // 数组的首字节地址
}*PMyArray, MyArray; //两个别名，PMyArray 类似java中类名，定义的对象不带 * , MyArray类似于OC中的类型，定义的对象带 * 。

					 // 要实现的一些基本方法

					 /** 初始化数组*/
void init_Arr(MyArray *pArr, int len);
/** 追加数组*/
bool append_Arr(MyArray *pArr, int value);
/** 插入数组*/
bool insert_Arr(MyArray *pArr, int index, int value);
/** 删除数组*/
bool delete_Arr(MyArray *pArr, int index, int * pVal);
/** 是否满载*/
bool is_full(MyArray *pArr);
/** 是否为空*/
bool is_empty(MyArray *pArr);
/** 排序数组*/
void sort_Arr(MyArray *pArr);
/** 展示数组*/
void show_Arr(MyArray *pArr);
/** 倒序数组*/
void inversion_Arr(MyArray *pArr);

/** 获取一个默认初始化的数组*/
MyArray * get_Arr(void);
