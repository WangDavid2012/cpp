#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// ��Ҫ�ڹ��캯����ȥ���ó�Ա������

class Parent
{
public:
	Parent(int a)
	{
		cout << "Parent(int a)...." << endl;
		this->a = a;
		print(); //���print��ӡ���� Parent ���� Child�ģ�
	}

	//�麯��
	virtual void print()
	{
		cout << "Parent::print():  " << a << endl;
	}
private:
	int a;
};

class Child : public Parent
{
public:
	Child(int a, int b) :Parent(a)
	{
		//vptrָ���ִ�е�������麯����
		print(); //ִ�е�child �� ���� parent?

		//�ٴ˴�֮ǰ�� �ǹ��츸����ڴ�ռ�  ��ʱchild����û������ϣ�vptrָ���ʱָ����Ǹ�����麯����
		cout << "Child() ..." << endl;
		this->b = b;

	}

	//��д�˸�����麯��
	virtual void print()
	{
		cout << "Child::print()  "<< " , " <<b << endl;
	}

private:
	int b;
};

int main(void)
{
	
	Parent *p = new Child(10, 20);//�ڴ˵���Child �Ĺ��캯��
	p->print(); //��ʱ�����˶�̬

	delete p;
	
	return 0;
}