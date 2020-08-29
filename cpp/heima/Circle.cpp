#include "Circle.h"


void Circle::setXY(int x, int y)
{
	m_x = x;
	m_y = y;
}
void Circle::setR(int r)
{
	m_r = r;
}

//�жϵ�ʮ�����ҵ��ڲ�
bool Circle::judgePoint(Point &p)
{
	int dd = (p.getX() - m_x) * (p.getX() - m_x) + (p.getY() - m_y) *(p.getY() - m_y);

	if (dd > m_r * m_r) {
		return false;
	}
	else {
		return true;
	}
}