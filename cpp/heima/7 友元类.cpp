#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class B;

class A
{
public:
	A(int a)
	{
		this->m_a = a;
	}

	void printA()
	{
		cout << m_a << endl;
	}

	int getA()
	{
		B bb(10);
		cout << bb.m_b << endl;
		return m_a;
	}

	//�������B�з��� A��������˽�г�Ա
	friend class B; //����B�����ҵ���Ԫ�ࡣ  ��Ԫ��Ϳ��Է����ҵ����г�Ա

private:
	int m_a;
};


class B
{
public:
	B(int b)
	{
		this->m_b = b;
		A aa(10);
		aa.m_a = 10;
	}
	
	void Test()
	{
		A aa(10);
		cout << aa.m_a << endl;
	}
	friend class A;
private:
	int m_b;
};

int main(void)
{
	B b(200);

	b.Test();
	
	return 0;
}