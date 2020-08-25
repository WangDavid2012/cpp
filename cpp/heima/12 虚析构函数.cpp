#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class A
{
public:
	A() {
		cout << "A() ..." << endl;
		this->p = new char[64]; //��p������һ���ռ�
		memset(p, 0, 64);
		strcpy(p, "A string ");
	}

	virtual void print()
	{
		cout << p << endl;
	}

	virtual ~A()
	{
		cout << "~A()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p; 
};

class B : public A
{
public:
	B() {
		cout << "B()..." << endl;
		this->p = new char[64];
		memset(p, 0, 64);
		strcpy(p, "B string");
	}

	//��д
	virtual void print()
	{
		cout << p << endl;
	}

	virtual  ~B()
	{
		cout << "~B()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p;
};

class C : public B
{
public:
	C() {
		cout << "C()..." << endl;
		this->p = new char[64];
		memset(p, 0, 64);
		strcpy(p, "C string");
	}


	virtual void print()
	{
		cout << p << endl;
	}

	virtual  ~C()
	{
		cout << "~C()...." << endl;
		if (p != NULL) {
			delete[] p;
			p = NULL;
		}
	}
private:
	char *p;
};


void func(A *p)//p = cp;  p = &c //�ø���ָ��ָ���������
{ 
	p->print(); //�ڴ˴�������̬��

	//delete p; //delete һ������ָ��   �����delete p���ǽ�p��������ָ����delete ���ǵ�������
	//�������������������� virtual delete �ͻᷢ����̬�� delelte p �����C�����������
}

void myDelete(A*p) //p->cp   ����ָ��ָ���������
{
	delete p; //p->~()  //���~���� ����virtual�ؼ� ���ᷢ����̬��
					//ϣ��delete p�� p->~() ����C���~����
					// ����� ���е����������������virtual�ؼ���  �ͻᷢ����̬��
}




void test()
{
	C c;
}
int main(void)
{
	/*
	C *cp = new C;

	cp->print();//cp�ĺ���

	delete cp;
	*/

	cout << " -----  " << endl;
	C * cp1 = new C; //����3�˹��� A() B���� C()

	//test();
	func(cp1);
	myDelete(cp1); 
	
	return 0;
}