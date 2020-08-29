#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//抽象类
class Programmer
{
public:
	virtual void printMoney() = 0;
};

class  Junior_programmer :public Programmer
{
public:
	Junior_programmer(double salary) {
		this->salary = salary;
	}
	virtual void printMoney()  {
		cout << "初级成员的工资是 " << salary << endl;
	}

private:
	double salary; //工资
};

class Mid_programmer :public Programmer
{
public:
	Mid_programmer(double salary)
	{
		this->salary = salary;
	}
	virtual void printMoney() {
		cout << "中级成员的工资是 " << salary << endl;
	}
private:
	double salary;
};

class Adv_programmer :public Programmer
{
public:
	Adv_programmer(double salary)
	{
		this->salary = salary;
	}
	virtual void printMoney() {
		cout << "高级级成员的工资是 " << salary << endl;
	}
private:
	double salary;
};

//针对抽象类封装的一个架构函数
void printSalary(Programmer *p)
{
	p->printMoney();
}

int main(void)
{
	Programmer *p = new Junior_programmer(8000);

	printSalary(p);
	delete p;

	p = new Mid_programmer(18000);
	printSalary(p);
	delete p;


	p = new Adv_programmer(20000);
	printSalary(p);
	delete p;



	
	return 0;
}