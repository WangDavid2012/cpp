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
	//设置立方体的长宽高
	void setABC(int a, int b, int c)
	{
		m_a = a;
		m_b = b;
		m_c = c;
	}

	//得到体积
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

	//提供一个判断两个立方体是否相等的成员函数
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


//判断两个立方体是否相等
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

	cout << "面积是" << c1.getArea() << endl;
	cout << "体积是 " << c1.getVolume() << endl;

	Cube c2;

	c2.setABC(10, 20, 30);


	if (judge(c1, c2) == true) {
		cout << "相同" << endl;
	}
	else {
		cout << "不同" << endl;
	}

	//面向对象的判断方法
	if (c1.judge(c2) == true) {
		cout << "相同" << endl;
	}
	else {
		cout << "不同" << endl;
	}

	return 0;
}