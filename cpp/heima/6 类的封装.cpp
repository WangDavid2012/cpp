#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//面向对象有三大特点， 封装，继承，多态
//C++将struct 做了功能的增强，struct实际上就是一个class
//只不过 struct的类的内部，默认的访问控制权限是public
//class 的类的内部，默认的访问控制权限是private
struct Date
{
	int year;
	int month;
	int day;
};

//初始化这个结构体
void init(struct Date & date)
{
	cout << "year, month, day" << endl;
	cin >> date.year;
	cin >> date.month;
	cin >> date.day;
}

//打印此结构体
void printDate(struct Date &date)
{
	cout << "日期是" << date.year << "年" << date.month << "月" << date.day << "日" << endl;
}

//判断是否为闰年
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

	//传统的C语言开发，面向过程的， 是一个一个函数来操作， C语种最小单元是一个函数
	init(date);

	printDate(date);

	if (isLeapYear(date) == true) {
		cout << "是闰年" << endl;
	}
	else {
		cout << "不是闰年" << endl;
	}
}


class MyDate
{
	//类的{}中的所有区域称为 类的 内部， 除了{}区域以外都是 类的外部
public://访问控制权限  //在public标识符下面定义的成员变量和成员函数 均可以在类的外部和类的内部 访问

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



	//成员函数
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
		cout << "日期是" << year << "年" << month << "月" << day << "日" << endl;
	}

protected://如果是单个类， 跟private是一样的。 在类的内部能够访问，在类的外部不能够访问
private://在private 访问控制符 下定义的成员变量和成员函数 只能在类的内部访问
	int month;
	int day;
	int year;
};


void test2()
{
	MyDate date; //通过MyDate 类 实例化一个对象

	//c++中 是面向对象进行开发，所有方法都封装在类中， 通过一个一个的对象进行编程。
	date.init();
	if (date.isLeapYear() == true) {
		cout << "是闰年" << endl;
	}
	else {
		cout << "不是闰年" << endl;
	}

	//cout <<"年"<< date.year << endl;
	cout << "年" << date.getYear() << endl;

	/*
	date.year = 2005;//在类的外部修改了成员变量
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