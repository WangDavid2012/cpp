#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


//�������
//��Բ����ĺ���
double getCircleArea(double r)
{
	return 3.14 * r * r;
}

//��Բ�ܳ��ĺ���
double getCircleGirth(double r)
{
	return 2 * 3.14 * r;
}

void test1()
{
	double r = 0;

	cout << "������Բ�İ뾶: " << endl;
	cin >> r;

	cout << "Բ���ܳ���" << getCircleGirth(r) << endl;
	cout << "ԭ�������" << getCircleArea(r) << endl;

}


//�������
class Circle
{
public:

	//һ���޸�һ��˽�г�Ա�ķ��� �� getter  ��setter����

	//дһ��m_r��setter����
	void setR(double r) {
		m_r = r;
	}

	//дһ��m_r��getter����
	double getR() {
		return m_r;
	}

	//�õ��ܳ��ķ���(��Ա����)
	double getGirth() {
		return m_r * 3.14 * 2;
	}

	//�õ�����ķ���
	double getArea() {
		return 3.14 * m_r*m_r;
	}
private://��private�¶���ĳ�Ա���� ��Ϊ˽�г�Ա
	double m_r; //�뾶
};


class Circle2
{
public:
	void setR(double r)
	{
		m_r = r;
	}
	double getR(){
		return m_r;
	}

	double getArea()
	{
		area = m_r *m_r *3.14;
		return area;
	}

	double getGirth()
	{
		girth = 3.14 * 2 * m_r;
		return girth;
	}

private:
	double m_r;
	double area ; //���
	double girth; //�ܳ�
};

int main(void)
{
	Circle c1;

	//c.m_r = 10.0;
	c1.setR(10.0);

	cout << "c1 �İ뾶��  " << c1.getR() << "  c1 ���ܳ���" << c1.getGirth() << "  c1�������" << c1.getArea() << endl;

	Circle c2;
	c2.setR(20.0);

	cout << "c2 �İ뾶��  " << c2.getR() << "  c2���ܳ���" << c2.getGirth() << "  c2�������" << c2.getArea() << endl;

	Circle2 c3;

	c3.setR(30.0);
	cout << "c3 �İ뾶��  " << c3.getR() << "  c3���ܳ���" << c3.getGirth() << "  c3�������" << c3.getArea() << endl;


	return 0;
}