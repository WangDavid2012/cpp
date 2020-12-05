#include "common.h"

// ���������
typedef struct Array {
	int length; // ���鳤��
	int count;  // ���鵱ǰԪ���� count
	int *pBase; // ��������ֽڵ�ַ
}*PMyArray, MyArray; //����������PMyArray ����java������������Ķ��󲻴� * , MyArray������OC�е����ͣ�����Ķ���� * ��

					 // Ҫʵ�ֵ�һЩ��������

					 /** ��ʼ������*/
void init_Arr(MyArray *pArr, int len);
/** ׷������*/
bool append_Arr(MyArray *pArr, int value);
/** ��������*/
bool insert_Arr(MyArray *pArr, int index, int value);
/** ɾ������*/
bool delete_Arr(MyArray *pArr, int index, int * pVal);
/** �Ƿ�����*/
bool is_full(MyArray *pArr);
/** �Ƿ�Ϊ��*/
bool is_empty(MyArray *pArr);
/** ��������*/
void sort_Arr(MyArray *pArr);
/** չʾ����*/
void show_Arr(MyArray *pArr);
/** ��������*/
void inversion_Arr(MyArray *pArr);

/** ��ȡһ��Ĭ�ϳ�ʼ��������*/
MyArray * get_Arr(void);
