#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//����ĳ�����
class Animal
{
public:
	virtual void cry() = 0;// ���麯��
	virtual void doHome() = 0;// ���麯��
};

class Dog :public Animal {
public:
	Dog(int a){
		this->a = a;
	}
	virtual void cry()  {
		cout << "����~~" << endl;
	}

	void doHome() {
		cout << "����" << endl;
	}
	int a;
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


class Tree
{
public:
	Tree(){
		age = 10;
	}
	virtual void printT() {
		cout << "���Ǵ���" << endl;
	}
	int age1;
	int age; //������ڴ��ڲ�
};

int main(void)
{
	Animal *animal = new Dog(10);
   animal->cry();


	Tree* tree = reinterpret_cast<Tree*>(animal); //C++�� ������ǿ��ת��
	if (tree != NULL) {
		cout << "ת���ɹ�" << endl;
		cout << tree->age << endl;
		tree->printT(); //vptr
	}
	else {
		cout << "ת��ʧ��" << endl;
	}
	
	return 0;
}