#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//点类
class Point
{
public:
	//设置一个点的坐标
	void setXY(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	int getX()
	{
		return m_x;
	}

	int getY()
	{
		return m_y;
	}

private:
	int m_x;
	int m_y;
};

//圆 类
class Circle
{
public:
	//设置坐标
	void setXY(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	//设置半径
	void setR(int r)
	{
		m_r = r;
	}

	//如果true 代表点在圆的内部
	bool judgePoint(Point &p)
	{
		int dd = (p.getX() - m_x) * (p.getX() - m_x) + (p.getY() - m_y) *(p.getY() - m_y);

		if (dd > m_r * m_r) {
			return false;
		}
		else {
			return true;
		}
	}

private:
	int m_x;
	int m_y;
	int m_r;
};

int main(void)
{
	Circle c;
	Point p;

	c.setXY(2, 2);
	c.setR(4);
	p.setXY(6, 8);



	if (c.judgePoint(p) == true) {
		cout << "点在圆的内部" << endl;
	}
	else {
		cout << "点在圆的外部" << endl;
	}
	
	return 0;
}