#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//����һ����
struct  Hero
{
public:
	int sex;
	char name[64];

};

//����һ����Ĺؼ���
class AdvHero //����һ������
{
public: //���ʿ��Ʒ�  ����Ȩ��
	int sex;
	char name[64]; //��Ա����


	//��Ա����
	void printHero()
	{
		cout << "�Ա�:" << sex << endl;
		cout << "����" << name << endl;
	}
};

//����һ��animal��
class Animal{
public:
	char color[64];
	char kind[64];

	//ӵ��д�ֵĳ�Ա����
	void write()
	{
		cout << kind << "��ʼд����" << endl;
	}

	//ӵ���ܲ��ķ���
	void run()
	{
		cout << kind << "�ܲ���" << endl;
	}
};

int main(void)
{
	struct Hero chunBro;

	chunBro.sex = 1;
	strcpy(chunBro.name, "chunBro");


	AdvHero gailun; //ͨ��AdvHero�� ����һ������
	gailun.sex = 1;
	strcpy(gailun.name, "����");


	/*
	cout << "�Ա�" << gailun.sex << endl;
	cout << "����:" << gailun.name << endl;
	*/

	gailun.printHero();//ͨ������ ֱ�ӵ��ó�Ա����


	Animal dog;
	Animal sheep;

	strcpy(dog.kind, "��");
	strcpy(dog.color, "��ɫ");

	dog.run();
	dog.write();

	strcpy(sheep.kind, "��");
	strcpy(sheep.color, "��");

	sheep.run();
	sheep.write();



	return 0;
}