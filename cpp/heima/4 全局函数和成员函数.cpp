#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test()
	{
		this->a = 0;
		this->b = 0;
	}

	Test(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	void printT()
	{
		cout << "a = " << a << ", b = " << b << endl;
	}

	int getA()
	{
		return this->a;
	}

	int getB()
	{
		return this->b;
	}

	//��Ա����
	Test TestAdd01(Test &t1, Test &t2)
	{
		Test temp(t1.getA() + t2.getA(), t1.getB() + t2.getB());
		return temp;
	}

	Test TestAdd02(Test &another)
	{
		//Test temp(this->a + another.getA(), this->b + another.getB());
		Test temp(this->a + another.a, this->b + another.b);

		return temp;
	}


	void TestAdd03(Test &another)
	{
		this->a += another.a;
		this->b += another.b;
	}


	Test & TestAdd04(Test &another)
	{
		this->a += another.a;
		this->b += another.b;

		//�����Լ�
		return *this;
	}//temp���� = *this 

private:
	int a;
	int b;
};

//�ṩһ��������ʵ������Test�������
//ȫ�ֺ���
Test TestAdd(Test &t1, Test &t2)
{
	Test temp(t1.getA() + t2.getA(), t1.getB() + t2.getB());

	return temp;
}//��ʱ������temp

int main(void)
{
	Test t1(10, 20);
	Test t2(100, 200);
	 
	Test t3 = TestAdd(t1, t2); //������һ��ȫ�ֺ��� 

	t3.printT();
	
	Test t4 = t1.TestAdd01(t1, t2);
	t4.printT();

	Test t5 = t1.TestAdd02(t2); //������ʱ�Ŀ���

	t5.printT();

	t1.TestAdd03(t2);
	t1.printT();

	(t1.TestAdd04(t2)).printT(); //t1�ı���

	return 0;
}