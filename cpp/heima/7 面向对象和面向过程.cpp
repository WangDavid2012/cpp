#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Dog
{
public:
	void eat(char *food)
	{
		cout << name << "����" << food << endl;
	}
	char name[64];
};

//���������дһ�����̣�
void eat(Dog &dog, char *food)
{
	cout << dog.name << "����" << food << endl;
}

int main(void)
{
	//������������
	Dog dog;

	strcpy(dog.name, "��");
	//ͨ��������Ϊ������
	dog.eat("��");

	//������������
	eat(dog, "��");
	
	return 0;
}