#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cmath>

using namespace std;

//同类之间无私处。
class Point
{
public:
	//设置point的两个坐标
	void setXY(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	int getX()
	{
		return m_x;
	}

	//根据另一个点，返回两个点之间的距离
	double pointDistance(Point &p)
	{
		int d_x = p.m_x - m_x; 
		int d_y = p.m_y - m_y;

		double dis = sqrt(d_x*d_x + d_y*d_y);

		return dis;
	}

private:
	int m_x;
	int m_y;
};


class Circle
{
public:
	//设置圆的半径
	void setR(int r)
	{
		m_r = r;
	}
	//设置圆的坐标
	void setXY(int x, int  y)
	{
		p0.setXY(x, y);
	}

	//判断另一个圆是否跟自己相交
	bool isIntersection(Circle & another_c)
	{
		int rr = m_r + another_c.m_r; //两个圆的半径之和
		double dis = p0.pointDistance(another_c.p0);

		if (dis <= rr) {
			//相交
			return true;
		}
		else {
			//不相交
			return false;
		}
	}
private:
	int m_r; //半径
	Point p0;// p0 就是圆的圆心点
};

int main(void)
{
	Circle c1, c2;


	int x, y, r;

	cout << "请输入第一个圆的半径" << endl;
	cin >> r;
	c1.setR(r);
	cout << "请输入第一个圆的x" << endl;
	cin >> x;
	cout << "请输入第一个院的y" << endl;
	cin >> y;
	c1.setXY(x, y);


	cout << "请输入第2个圆的半径" << endl;
	cin >> r;
	c2.setR(r);
	cout << "请输入第2个圆的x" << endl;
	cin >> x;
	cout << "请输入第2个院的y" << endl;
	cin >> y;
	c2.setXY(x, y);


	if (c1.isIntersection(c2) == true) {
		cout << "两个圆相交" << endl;
	}
	else {
		cout << "两个圆不想交" << endl;
	}
	
	return 0;
}