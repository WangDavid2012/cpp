#include "Employee.h"


//始化静态成员
int Employee::startnum = 1000; //静态的编号计数

//所有继承于 抽象类的 子类在构造的时候，都会调用父类的构造函数
Employee::Employee()
{
	level = 1;
	salary = 0.0;
	id = startnum++;
}


Employee::~Employee()
{
	cout << "~Employee()" << endl;
}

void Employee::displayStatus()
{
	cout << "姓名" << this->name << endl;
	cout << "级别" << this->level << endl;
	cout << "编号" << this->id << endl;
	cout << "当月的薪水" << this->salary << endl;
}