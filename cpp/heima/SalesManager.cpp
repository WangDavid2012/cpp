#include "SalesManager.h"


SalesManager::SalesManager()
{

}


SalesManager::~SalesManager()
{
}

void SalesManager::init()
{
	cout << "请输入销售经理的姓名" << endl;
	cin >> name;

	fixSalary = 5000;
	salePersent = 0.05;
}

//得到员工的薪水的方法
void SalesManager::getPay()
{
	cout << "请输入销售经理当前月的销售额" << endl;
	cin >> this->saleAmount;

	//计算心事
	this->salary = this->fixSalary + this->saleAmount*this->salePersent;
}

//员工的升级方法
void SalesManager::uplevel(int addLevel)
{
	this->level += addLevel;
}