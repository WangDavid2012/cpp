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
	cout << "请输入 销售人员的姓名" << endl;
	cin >> name;

	this->salePersent = 0.04; //按4%  提成
}

//得到员工的薪水的方法
void SaleMan::getPay()
{
	cout << "请输入该员工本月的销售额" << endl;
	cin >> saleAmount;

	//计算薪水
	this->salary = this->saleAmount * this->salePersent;
}

//员工的升级方法
void SaleMan::uplevel(int addLevel)
{
	this->level += addLevel;
}
