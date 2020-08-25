#include "Circle.h"

void Circle::setR(double r)
{
	//这里面依然是 Circle类的内部
	m_r = r;
}

double Circle::getR()
{
	return m_r;
}

//得到面积
double Circle::getArea()
{
	return m_r * m_r *3.14;
}

//得到周长
double Circle::getGirth()
{
	return m_r * 3.14 * 2;
}