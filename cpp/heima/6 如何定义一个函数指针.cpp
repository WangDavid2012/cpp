#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//����һ������
int func(int a, int b) {
	cout << "func 111 " << endl;

	return 0;
}


//����һ������ָ��
// C������ ����һ����������
// ����ֵ �����б�

typedef int(FUNC)(int, int); //����һ����������

typedef int(*FUNC_POINTER)(int, int); //����һ������ָ������


//��ν�һ������ָ�뵱��һ�����������أ�
void my_function(FUNC *fp)
{
	fp(10, 20);
}

void my_function2(FUNC_POINTER fp)
{
	fp(10, 20);
}

//����һ���ܹ������� 
void my_function3(int(*fp)(int, int))
{
	cout << "1999 ��д�ļܹ�" << endl;
	cout << "�̶�ҵ��1" << endl;
	fp(10, 20);
	cout << "�̶�ҵ��2" << endl;
}


//2015 ʵ��һ���Ӻ���
int my_new_function(int a, int b)
{
	cout << a << b << endl;
	cout << "2015��ʵ�ֵ���ҵ��" << endl;

	return 0;
}

int main(void)
{
	FUNC * p = func;
	FUNC_POINTER p2 = func;
	int(*fp)(int, int) = func;

	p(10, 20);
	(*p)(10, 20); //��������д���ȼ�

	p2(10, 20);
	(*p2)(20, 20);

	fp(10, 20);

	cout << " --------  " << endl;

	//2015   ʵ��һ���Ӻ������ٵ���1999�ļܹ�
	my_function3(my_new_function);
	
	return 0;
}