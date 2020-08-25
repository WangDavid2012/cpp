#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cmath>

using namespace std;


class Point;

class PointManager
{
public:
	//如果解决循环前置声明的问题，应该将函数的声明和函数的定义分开写。
	double PointDistance(Point & p1, Point &p2);
};

class Point
{
public:
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void printPoint()
	{
		cout << "x = " << x << ", y = " << y << endl;
	}

	int getX()
	{
		return this->x;
	}

	int getY()
	{
		return this->y;
	}

	//Point类认为 全局函数（类外部的函数）PointDistance 是我的一个哥们。这个函数
	//可以使用我的私有成员
	//声明一个全局函数为自己的友元
	friend double PointDistance(Point & p1, Point &p2);

	//声明一个 其他类的成员函数为自己的友元
	friend double PointManager::PointDistance(Point & p1, Point &p2); 

private:

	int x;
	int y;

};


double PointManager::PointDistance(Point & p1, Point &p2)
{
	//int dd_x = p1.getX() - p2.getX();
	int dd_x = p1.x - p2.x;
	//int dd_y = p1.getY() - p2.getY();
	int dd_y = p1.y - p2.y;

	return sqrt(dd_x*dd_x + dd_y*dd_y);
}




//1 通过全局方式写一个亮点之间的距离
//如果发现有一个方式 是全局的不是类自己的成员函数
double PointDistance(Point & p1, Point &p2)
{
	//int dd_x = p1.getX() - p2.getX();
	int dd_x = p1.x - p2.x;
	//int dd_y = p1.getY() - p2.getY();
	int dd_y = p1.y - p2.y;

	return sqrt(dd_x*dd_x + dd_y*dd_y);
}

int main(void)
{
	Point p1(1, 2);
	Point p2(0, 0);

	cout << "两点之间的距离是 " << PointDistance(p1, p2) << endl;


	PointManager pm;
	cout << "两点之间的距离是 " << pm.PointDistance(p1, p2) << endl;


	
	return 0;
}