#include "SaleMan.h"


SaleMan::SaleMan()
{

}


SaleMan::~SaleMan()
{
	cout << "~SaleMan()" << endl;
}

void SaleMan::init()
{
	cout << "������ ������Ա������" << endl;
	cin >> name;

	this->salePersent = 0.04; //��4%  ���
}

//�õ�Ա����нˮ�ķ���
void SaleMan::getPay()
{
	cout << "�������Ա�����µ����۶�" << endl;
	cin >> saleAmount;

	//����нˮ
	this->salary = this->saleAmount * this->salePersent;
}

//Ա������������
void SaleMan::uplevel(int addLevel)
{
	this->level += addLevel;
}
