#include "Manager.h"


Manager::Manager()
{

}


Manager::~Manager()
{
	cout << "~Manager()" << endl;
}

void Manager::init()
{
	cout << "�����뾭�������" << endl;
	cin >> name;

	//����Ĺ̶�нˮ��8000
	fixSalary = 8000;
}


//�õ�Ա����нˮ�ķ���
void Manager::getPay()
{
	//���㾭���н�ʷ���
	this->salary = fixSalary;
}

//Ա������������
void Manager::uplevel(int addLevel)
{
	this->level += addLevel;
}
