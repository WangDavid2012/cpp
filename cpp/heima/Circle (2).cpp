#include "Circle.h"

void Circle::setR(double r)
{
	//��������Ȼ�� Circle����ڲ�
	m_r = r;
}

double Circle::getR()
{
	return m_r;
}

//�õ����
double Circle::getArea()
{
	return m_r * m_r *3.14;
}

//�õ��ܳ�
double Circle::getGirth()
{
	return m_r * 3.14 * 2;
}