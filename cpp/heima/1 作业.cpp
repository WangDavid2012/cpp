#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cmath>

using namespace std;

//ͬ��֮����˽����
class Point
{
public:
	//����point����������
	void setXY(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	int getX()
	{
		return m_x;
	}

	//������һ���㣬����������֮��ľ���
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
	//����Բ�İ뾶
	void setR(int r)
	{
		m_r = r;
	}
	//����Բ������
	void setXY(int x, int  y)
	{
		p0.setXY(x, y);
	}

	//�ж���һ��Բ�Ƿ���Լ��ཻ
	bool isIntersection(Circle & another_c)
	{
		int rr = m_r + another_c.m_r; //����Բ�İ뾶֮��
		double dis = p0.pointDistance(another_c.p0);

		if (dis <= rr) {
			//�ཻ
			return true;
		}
		else {
			//���ཻ
			return false;
		}
	}
private:
	int m_r; //�뾶
	Point p0;// p0 ����Բ��Բ�ĵ�
};

int main(void)
{
	Circle c1, c2;


	int x, y, r;

	cout << "�������һ��Բ�İ뾶" << endl;
	cin >> r;
	c1.setR(r);
	cout << "�������һ��Բ��x" << endl;
	cin >> x;
	cout << "�������һ��Ժ��y" << endl;
	cin >> y;
	c1.setXY(x, y);


	cout << "�������2��Բ�İ뾶" << endl;
	cin >> r;
	c2.setR(r);
	cout << "�������2��Բ��x" << endl;
	cin >> x;
	cout << "�������2��Ժ��y" << endl;
	cin >> y;
	c2.setXY(x, y);


	if (c1.isIntersection(c2) == true) {
		cout << "����Բ�ཻ" << endl;
	}
	else {
		cout << "����Բ���뽻" << endl;
	}
	
	return 0;
}