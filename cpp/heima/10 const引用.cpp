#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//const����һ�������β��ϣ�������  �����õı������ܱ��޸ģ�
void printX(const int & re )
{
	cout << "re " << re << endl;
}

int main(void)
{
	const int a = 10; // a�����ʼ��
	//int & b = a;
	const int &b = a;

	//�����һ��const ������ ������const ������������
	int x = 3.14;
	const int &re1 = x;


	cout << "re1 " << re1 << endl;
	x = 20;
	cout << "re1 " << re1 << ", x: " << x << endl;


	const int &re2 = 10;// ��const ���� ����һ��������
									// ����һ��const ����  ȥ����һ����������ʱ�� ����������û�е�ַ��
									//�������޷� ��������ȡ��ַ�ģ� ��ʱ����һ�� int temp�� 10 --->temp
									//const int &re2 = temp;
									//��re2 ���Ǵ��� temp��re2��const�����ã����޷�ȥ�ı�temp��ֵ
	//int &re2 = 10;         //�ǳ������� ��������ֵ�� ��ֵ���ǿ��Է���=��ߵı��ʽ����ֵ�ǿ��Ը�ֵ�������ڴ�ռ��
									//������һ�������������õĻ���ֻ���� const ������

	cout << "re2 = " << re2 << endl;

	cout << "sizeof(re2)" << sizeof(re2) << endl;

	return 0;
}