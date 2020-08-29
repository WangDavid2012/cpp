#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


class Student
{
public:
	Student(int num, double score) {
		m_num = num;
		m_score = score;

		count++;
		sum_score += score;
	}

	static double getAvg()
	{
		return sum_score / count;
	}

private:
	int m_num; //学号
	double m_score; //成绩

	//定义一个记录学生个数的静态变量
	static int count; //记录目前Student类已经创建了多少个学生对象。
	static double sum_score;// 所有已经定义学生对象的总score和。
};

//初始化静态成员变量
int Student::count = 0;
double Student::sum_score = 0.0;

int main(void)
{
	Student s1(1, 80);
	Student s2(2, 90);
	Student s3(3, 80);

	//Student::sum_score / Student::count;
	//使用一个静态的成员函数
	double avg = Student::getAvg(); //可以给他当成一个 类的全局函数

	//s1.getAvg();

	cout << "目前的学生的平均分数是" << avg << endl;
	
	return 0;
}