#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Sqr
{
public:
	Sqr(int a)
	{
		this->a = a;
	}

	//���s���� �����һ�� ����һ�������ĺ����� ���ƽ�� ����
	//�˺������ܾ��� ��a��ƽ��
	int operator()(int a)
	{
		return a*a;
	}
private:
	int a;
};

//STL C++�ı�׼ģ���


//a ��ͨint  
//fp  --> int (*)(int)
void func(int a, int(*fp)(int))
{
	cout << a << "��ƽ�������" << endl;
	cout << fp(a) << endl;
}

int sqr(int a)
{
	return a * a;
}

class Print
{
public:
	void operator()(int value)
	{
		cout << value << endl;
	}
};

void print(int value)
{
	cout << value << endl;
}


int main(void)
{
	Sqr s(10);

	int a = 10;

	//s���� ����һ��������ʹ��
	//����д���� ���Ƿº����� ��s������һ��������ʹ�ã���������Ϊs��һ��������
	int aa = s(a);//s.operator()(a);    //α����


	//��һ������ ����һ���ص���������ȥ ���Ƿº���������

	cout << aa << endl;


	int b = 20;

	func(b, sqr); //ͨ��func ����һ��sqr�ص�����
	//func(b, s);

	cout << "  ------  " << endl;

	vector<int> v1; //���� ���10��Ԫ��

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i + 10);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << v1[i] << endl;
	}


	cout << " -----  " << endl;

	Print pObj;
	 
	for_each(v1.begin(), v1.end(), pObj); //pObjd(value)


	
	return 0;
}
