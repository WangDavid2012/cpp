#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;



//�����ڽ��г�ʼ����Ա������ʱ�� ����˳�Ա�����Ǽ̳й����ģ� ��ô��Ҫ���ø���Ĺ���������ʼ����

class Parent
{
public:
	Parent(int a) {
		this->a = a;
		cout << "Parent(int a) ..." << endl;
	}
	~Parent()
	{
		cout << "~Parent()..." << endl;
	}

	void printA()
	{
		cout << "a = " << a << endl;
	}
private:
	int a;
};

class Son :public Parent
{
public:
	//����̳��ڸ��࣬ �����еĳ�Ա���� Ӧ���� ����Ĺ��캯������ʼ��
	Son(int a, int b) : Parent(a)
	{
		this->b = b;
		cout << "Son(int a, int b) ..." << endl;
	}
	~Son()
	{
		//Parent p = Parent(b);//��һ���µ�parent����
		cout << "~Son() ..." << endl;
	}

	void printB()
	{
		cout << "b = " << b << endl;
	}

	void pirntAB()
	{
		Parent::printA();
		this->printB();
	}
private:
	int b;
	char *name;
};

void test1()
{
	Parent p(30);

	Son s(20, 20); // p + s����


	s.pirntAB();
}

int main(void)
{

	test1();
	return 0;
}