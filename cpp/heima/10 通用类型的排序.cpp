#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

template<class T>
int array_sort(T *array, int num)
{

	T temp; //��ʱ��Ԫ��

	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (array[j] >array[i]) {
				temp = array[j];
				array[j] = array[i];
				array[i] = temp;
			}
		}
	}

	return 0;
}

//��ӡ����ķ���
template <typename T>
void print_array(T *array, int num)
{
	for (int i = 0; i < num; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}


int main(void)
{
	// �����ַ���
	char str[] = "dsajdksadcndsofjdidjisaodja";
	int len = strlen(str);
	array_sort<char>(str, len);
	print_array<char>(str, len);


	cout << " -------  " << endl;


	// ����һ��int����
	int array[] = { 3, 4, 7, 1, 6, 13, 84, 31 };
	len = sizeof(array) / sizeof(array[0]);
	array_sort<int>(array, len);
	print_array<int>(array, len);
	
	return 0;
}