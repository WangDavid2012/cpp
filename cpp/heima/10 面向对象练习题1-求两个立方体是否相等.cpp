#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

struct A
{
	int a;
	int b;
};


class Cube
{
public:
	//����������ĳ����
	void setABC(int a, int b, int c)
	{
		m_a = a;
		m_b = b;
		m_c = c;
	}

	//�õ����
	int getVolume() {
		return m_a * m_b *m_c;
	}

	int getArea(){
		return 2*( (m_a*m_b) + (m_b *m_c) + (m_c *m_a));
	}

	int getA() {
		return m_a;
	}

	int getB(){
		return m_b;
	}

	int getC(){
		return m_c;
	}

	//�ṩһ���ж������������Ƿ���ȵĳ�Ա����
	bool judge(Cube &another_c)
	{
		if (m_a == another_c.getA() &&
			m_b == another_c.getB() &&
			m_c == another_c.getC()) {
			return true;
		}
		else {
			return false;
		}
	}

private:
	int m_a;
	int m_b;
	int m_c;
};


//�ж������������Ƿ����
bool judge(Cube &c1, Cube &c2)
{
	if (c1.getA() == c2.getA() &&
		c1.getB() == c2.getB() &&
		c1.getC() == c2.getC()) {
		return true;
	}
	else {
		return false;
	}
}

int main(void)
{
	Cube c1;

	c1.setABC(10, 20, 30);

	cout << "�����" << c1.getArea() << endl;
	cout << "����� " << c1.getVolume() << endl;

	Cube c2;

	c2.setABC(10, 20, 30);


	if (judge(c1, c2) == true) {
		cout << "��ͬ" << endl;
	}
	else {
		cout << "��ͬ" << endl;
	}

	//���������жϷ���
	if (c1.judge(c2) == true) {
		cout << "��ͬ" << endl;
	}
	else {
		cout << "��ͬ" << endl;
	}

	return 0;
}