#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class A
{
public:
	A(){
		cout << "A() ...." << endl;
	}
	~A()
	{
		cout << "~A()...." << endl;
	}
	void func()
	{
		cout << "a --> func()...." << endl;
	}
};


class MyAutoPtr //����һ��ָ��A�������ָ��
{
public:
	//�в����Ĺ��캯����  ��A�Ķ���ĵ�ַ  ���չ�����
	MyAutoPtr(A* ptr) //ptr = new A;
	{
		this->m_p = ptr;
	}

	~MyAutoPtr()
	{
		if (this->m_p != NULL) {
			delete m_p;
		}
	}

	A* operator->()
	{
		return m_p;
	}

	A &  operator*()
	{
		return *m_p; //A temp = *m_p; 
	}

private:
	A* m_p;//ָ��A����ĵ�ַ��
};


void test1()
{
	//ֻ��ָ�벻��Ҫ�����ֶ� delete����ռ�
	auto_ptr<A>   auto_p(new A);    //����ָ�롣
	auto_p->func();
}

void test2()
{
	MyAutoPtr auto_p(new A); // A  auto_p  &A,  *auto_p  A

	//auto_p =  &A;
	//auto_p->     func(); // A* m_p = &A;  m_p->func();
	//(*auto_p)      .func()//  *m_p    .func()
	// m_p->      func();
	/*
	A* m_p = new A;
	m_p->func();
	(*m_p).func();
	delete m_p;


	*/

	auto_p->func();  //m_p->func(); 

	(*auto_p).func();   //(*m_p).func();

	//����auto_p   �ͻ����auto_p ��������
}


class Teacher
{
public:
	Teacher(int id, string name)
	{
		this->id = id;
		this->name = name;
	}

	void printT()
	{
		cout << "id = " << id << " name = " << name << endl;
	}
private:
	int id;
	string name;
};


int main(void)
{
	
	test2();

	string str1 = "12312321";
	string str2 = str1;
	string str3;

	str3 = str1 + str2;

	cout << str1 << endl;


	return 0;
}