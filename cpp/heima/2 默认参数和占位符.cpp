#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


// c++�� �����һ���β� Ĭ������Ϊһ��ֵ, ���ⲿ���ú�����ʱ����������ݲ����ģ���ôx����100
//����ⲿ����ʵ�Σ���ôx��ֵ����ʵ�ε�ֵ
int func1(int x , int = 0)
{
	cout << "func1: x = " << x << endl;

	return 0;
}


//��һ�� ����������
//Ĭ�ϲ����������Ǵ����������ã� ֻ����һ�������Ǵ���Ĭ�ϲ��� �ģ���ô���ұߵ����в�����������Ĭ��ֵ��
int volume(int len , int width, int high= 30)
{
	return len *width * high;
}

int main(void)
{
	int x = 10;
	int v = 0;

	func1(x);

	int len = 10;
	int w = 20;
	int h = 30;

	//v = volume(len, w, h);
	v = volume(len, w,h);

	cout << "v = " << v << endl;
	
	return 0;
}