#include "Animal.h"


Animal::Animal()
{
	cout << "Animal()..." << endl;
}


Animal::~Animal()
{
	cout << "~Animal() ..." << endl;
}


void AnimalVoice(Animal *ap)
{
	cout << "���￪ʼ�ҽ���" << endl;
	ap->voice();
	cout << "�����ҽ� ������" << endl;
}

