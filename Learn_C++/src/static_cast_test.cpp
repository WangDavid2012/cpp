#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void static_cast_test(void)
{
	double PI = 3.14159265;

	//int num = PI;
	int num2 = (int)PI; //C���Ե�ת����ʽ
						//static_cast ���ӿɶ��ԣ�������ͨ���͵�ǿ��ת����
						//static_cast ʵ�������ֱ������ڱ����ʱ����Ѿ���PI���ͳ�num������
	int num3 = static_cast<int>(PI);

	cout << "num2" << num2 << endl;
	cout << "num3" << num3 << endl;
}



class A
{
public:
	virtual void func() {
		cout << "A" << endl;
	}
	int a;
};

class B :public A
{
public:
	virtual void func() {
		cout << "B" << endl;
	}
	int b;
};

//����ĳ�����
class Animal
{
public:
	virtual void cry() = 0;// ���麯��
	virtual void doHome() = 0;// ���麯��
};

class Dog :public Animal {
public:
	virtual void cry() {
		cout << "����~~" << endl;
	}

	void doHome() {
		cout << "����" << endl;
	}
};

class Cat :public Animal {
public:
	virtual void cry() {
		cout << "����~~" << endl;
	}
	void doHome() {
		cout << "ץ����" << endl;
	}
};



void dynamic_cast_test(void)
{
	Animal *animal = NULL;
	animal = new Dog;
	animal->cry();

	Dog *dog = new Dog;
	cout << " ----- " << endl;

	dog = dynamic_cast<Dog*> (animal);
	if (dog != NULL) {
		cout << "ת���ɹ�" << endl;
		dog->cry();
		dog->doHome();
	}
	else {
		cout << "ת��ʧ��" << endl;
	}
	//dynamic _cast �ǽ�����ת�������ࡣ�����ӱ�ɶ��ӡ�
	//������ָ��ִ�и���Ķ���

	Cat *cat = dynamic_cast<Cat*>(animal);
	//׼����ͼ��һֻ�����һֻè
	if (cat != NULL) {
		cout << "ת���ɹ�" << endl;
		cat->cry();
		cat->doHome();
	}
	else {
		cout << "ת��ʧ��" << endl;
	}

	A *ap = new A;
	B *bp = dynamic_cast<B*>(ap);
	if (bp != NULL) {
		bp->func();
	}
}