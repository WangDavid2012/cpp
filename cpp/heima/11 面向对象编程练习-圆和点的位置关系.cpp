#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//����
class Point
{
public:
	//����һ���������
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

//Բ ��
class Circle
{
public:
	//��������
	void setXY(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	//���ð뾶
	void setR(int r)
	{
		m_r = r;
	}

	//���true �������Բ���ڲ�
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
		cout << "����Բ���ڲ�" << endl;
	}
	else {
		cout << "����Բ���ⲿ" << endl;
	}
	
	return 0;
}