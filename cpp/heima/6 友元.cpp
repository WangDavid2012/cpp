#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cmath>

using namespace std;


class Point;

class PointManager
{
public:
	//������ѭ��ǰ�����������⣬Ӧ�ý������������ͺ����Ķ���ֿ�д��
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

	//Point����Ϊ ȫ�ֺ��������ⲿ�ĺ�����PointDistance ���ҵ�һ�����ǡ��������
	//����ʹ���ҵ�˽�г�Ա
	//����һ��ȫ�ֺ���Ϊ�Լ�����Ԫ
	friend double PointDistance(Point & p1, Point &p2);

	//����һ�� ������ĳ�Ա����Ϊ�Լ�����Ԫ
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




//1 ͨ��ȫ�ַ�ʽдһ������֮��ľ���
//���������һ����ʽ ��ȫ�ֵĲ������Լ��ĳ�Ա����
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

	cout << "����֮��ľ����� " << PointDistance(p1, p2) << endl;


	PointManager pm;
	cout << "����֮��ľ����� " << pm.PointDistance(p1, p2) << endl;


	
	return 0;
}