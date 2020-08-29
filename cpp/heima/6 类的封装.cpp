#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//��������������ص㣬 ��װ���̳У���̬
//C++��struct ���˹��ܵ���ǿ��structʵ���Ͼ���һ��class
//ֻ���� struct������ڲ���Ĭ�ϵķ��ʿ���Ȩ����public
//class ������ڲ���Ĭ�ϵķ��ʿ���Ȩ����private
struct Date
{
	int year;
	int month;
	int day;
};

//��ʼ������ṹ��
void init(struct Date & date)
{
	cout << "year, month, day" << endl;
	cin >> date.year;
	cin >> date.month;
	cin >> date.day;
}

//��ӡ�˽ṹ��
void printDate(struct Date &date)
{
	cout << "������" << date.year << "��" << date.month << "��" << date.day << "��" << endl;
}

//�ж��Ƿ�Ϊ����
bool isLeapYear(struct Date &date)
{
	if (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0)) {
		return true;
	}
	else {
		return false;
	}
}

void test1()
{
	struct  Date date;

	//��ͳ��C���Կ�����������̵ģ� ��һ��һ�������������� C������С��Ԫ��һ������
	init(date);

	printDate(date);

	if (isLeapYear(date) == true) {
		cout << "������" << endl;
	}
	else {
		cout << "��������" << endl;
	}
}


class MyDate
{
	//���{}�е����������Ϊ ��� �ڲ��� ����{}�������ⶼ�� ����ⲿ
public://���ʿ���Ȩ��  //��public��ʶ�����涨��ĳ�Ա�����ͳ�Ա���� ������������ⲿ������ڲ� ����

	int getYear()
	{
		return year;
	}

	void init(){
		cout << "year, month, day" << endl;
		cin >> year;
		cin >> month;
		cin >> day;
	}



	//��Ա����
	bool isLeapYear()
	{
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	void printDate() {
		cout << "������" << year << "��" << month << "��" << day << "��" << endl;
	}

protected://����ǵ����࣬ ��private��һ���ġ� ������ڲ��ܹ����ʣ�������ⲿ���ܹ�����
private://��private ���ʿ��Ʒ� �¶���ĳ�Ա�����ͳ�Ա���� ֻ��������ڲ�����
	int month;
	int day;
	int year;
};


void test2()
{
	MyDate date; //ͨ��MyDate �� ʵ����һ������

	//c++�� �����������п��������з�������װ�����У� ͨ��һ��һ���Ķ�����б�̡�
	date.init();
	if (date.isLeapYear() == true) {
		cout << "������" << endl;
	}
	else {
		cout << "��������" << endl;
	}

	//cout <<"��"<< date.year << endl;
	cout << "��" << date.getYear() << endl;

	/*
	date.year = 2005;//������ⲿ�޸��˳�Ա����
	date.month;
	date.day;
	*/
}

int main(void)
{
	
	//test1();
	test2();

	return 0;
}