#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//��ζ�һ��һ������ָ��

//����һ
//����һ����������
typedef int(ARRAY_INT_10_TYPE)[10];

//������
//ֱ�Ӷ���һ������ָ��
typedef int(*ARRAY_INT_10_TYPE_POINTER)[10];

int main(void)
{
	int array[10];
	ARRAY_INT_10_TYPE array2;
	ARRAY_INT_10_TYPE * array_p = NULL; //ָ���������͵�ָ��
	ARRAY_INT_10_TYPE_POINTER array_p3 = NULL;

	*array; // �����һ��Ԫ��  int �� array����������֣���Ԫ�صĵ�ַ
			  //��һ�� ���int����ĵ�һ��Ԫ�ء�
	*array_p;//��һ��������飨int[10]��������ĵ�һ��Ԫ�ء�

	for (int i = 0; i < 10; i++) {
		(*array_p)[i] = 10;
	}

	for (int i = 0; i < 10; i++) {
		array[i] = 10;
		array2[i] = 10;
	}
	
	return 0;
}