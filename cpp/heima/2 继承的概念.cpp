#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
	Student(int id, char *name)
	{
		this->name = name;
		this->id = id;
	}

	void printS()
	{
		cout << "id =  " << id << " name  =" << name << endl;
	}

private:
	string name;
	int id;
};

//用C语言的方式
class Student2
{
public:
	Student2(int id, string name, int score)
	{
		this->id = id;
		this->name = name;
		this->score = score;
	}

	void printS()
	{
		cout << "id =  " << id << " name  =" << name << endl;
		cout << "score = " << score << endl;
	}

private:

	string name;
	int id;
	//添加一个成员变量
	int score;
};

//用C++的继承的方式
class Student3 : public Student
{
public:
	Student3(int id, char * name, int score) : Student(id, name)//子类继承过来的成员变量 通过父类的构造器来构造
	{
		this->score = score;
		//this->id = id;
	}

	void printS()
	{
		Student::printS();// 先调用父类中的方法
		cout << "score = " << this->score << endl;
	}
private:
	int score;//添加的一个成员变量
};

int main(void)
{
	Student3 s(1, "zhang3", 88);

	s.printS();
	
	return 0;
}