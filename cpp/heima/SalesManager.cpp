#include "SalesManager.h"


SalesManager::SalesManager()
{

}


SalesManager::~SalesManager()
{
}

void SalesManager::init()
{
	cout << "���������۾��������" << endl;
	cin >> name;

	fixSalary = 5000;
	salePersent = 0.05;
}

//�õ�Ա����нˮ�ķ���
void SalesManager::getPay()
{
	cout << "���������۾���ǰ�µ����۶�" << endl;
	cin >> this->saleAmount;

	//��������
	this->salary = this->fixSalary + this->saleAmount*this->salePersent;
}

//Ա������������
void SalesManager::uplevel(int addLevel)
{
	this->level += addLevel;
}