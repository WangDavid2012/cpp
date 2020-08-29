#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	//��ʾ�ṩһ���������Ĺ��캯��
	A(int a)
	{
		m_a = a;
		cout << "a = " << m_a << "�����˹��캯��" << endl;

	}
	~A()
	{
		cout << "a = " << m_a << "��������" << endl;
	}

	void printA()
	{
		cout << " a = " << m_a << endl;
	}
private:
	int m_a;
};

class B
{
public:
	B(int b) :a1(10), a2(100) //�ڳ�ʼ��B��ʱ��ͨ����ʼ���б���ڲ�����a1 ��a2 �����˳�ʼ��
	{
		m_b = b;
		/*
		a1(10);
		a2(20);
		*/
		cout << "b = " << m_b << "�����˹��캯��" << endl;
	}

	B(int aa1, int aa2, int b) : a1(aa1), a2(aa2), m_b(b) //ͨ����ʼ���б����ܹ���ʼ����Ա���� �����Գ�ʼ����Ա����
	{

	}

	void printB()
	{
		cout << "b = " << m_b << endl;
		a1.printA();
		a2.printA();
	}

	~B()
	{
		cout <<"b = " <<m_b << " ��������������" << endl;
	}

private:
	int m_b;
	A a2;
	A a1;
};

//���ڲ��Ķ����ʼ����˳�򣬸�����Ķ���˳��һ��������ʼ���б��е�˳���޹�
//������˳��͸������˳���෴

class ABC
{
public:
	ABC()
	{

	}
	ABC(int a, int b, int c) :m_a(a), m_b(b), m_c(c) {}


	ABC(const ABC &abc)
	{
		m_a = abc.m_a;
		m_b = abc.m_b;
		m_c = abc.m_c;
	}

	void printABC()
	{
		cout << m_a << "," << m_b << "," << m_c << "," << endl;
	}
private:
	int m_a;
	int m_b;
	int m_c;
};


class ABCD
{
public:
	ABCD(int a, int b, int c, int d, int m) :m_abc(a, b, c), m_m(m)//������Ա�������ܹ���ֵ��ֻ��ͨ����ʼ���б���г�ʼ��
	{
		m_d = d;
	}

	ABCD(int d, ABC abc, int m) :m_abc(abc), m_m(m)
	{
		m_d = d;
	}

	ABCD(int d, int m) :m_m(m)
	{

	}

	void printABCD()
	{
		m_abc.printABC();
		cout << m_d << endl;
	}

private: 
	ABC m_abc; 
	int m_d;
	const int m_m; //����
};

int main(void)
{
	//A a(10);

	//a(10);//��һ��a���󵱳�һ������������

//	B b(1); 
//	b.printB();

	//B b2(10, 20, 30);
	//b2.printB();

	ABCD abcd_obj1(1, 2, 3, 4);
	abcd_obj1.printABCD();

	cout << " -----" << endl;

	ABC abc_obj(1, 2, 3); 
	ABCD abcd_obj2(40, abc_obj);
	abcd_obj2.printABCD();



	
	return 0;
}