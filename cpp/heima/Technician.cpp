#include "Technician.h"


Technician::Technician()
{

}


Technician::~Technician()
{
}

void Technician::init()
{
	cout << "请输入技术人员的姓名" << endl;
	cin >> this->name;
	perHourMoney = 100; //技术人员每小时赚100
}

//得到员工的薪水的方法
void Technician::getPay()
{
	cout << "请输入员工一个月工作了多少小时" << endl;
	cin >> workHour;

	//计算工资
	this->salary = perHourMoney * workHour;
}

//员工的升级方法
void Technician::uplevel(int addLevel)
{
	this->level += addLevel;

}
