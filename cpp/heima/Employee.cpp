#include "Employee.h"


//ʼ����̬��Ա
int Employee::startnum = 1000; //��̬�ı�ż���

//���м̳��� ������� �����ڹ����ʱ�򣬶�����ø���Ĺ��캯��
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
	cout << "����" << this->name << endl;
	cout << "����" << this->level << endl;
	cout << "���" << this->id << endl;
	cout << "���µ�нˮ" << this->salary << endl;
}