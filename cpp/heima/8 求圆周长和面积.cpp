#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


//面向过程
//求圆面积的函数
double getCircleArea(double r)
{
	return 3.14 * r * r;
}

//求圆周长的函数
double getCircleGirth(double r)
{
	return 2 * 3.14 * r;
}

void test1()
{
	double r = 0;

	cout << "请输入圆的半径: " << endl;
	cin >> r;

	cout << "圆的周长是" << getCircleGirth(r) << endl;
	cout << "原点面积是" << getCircleArea(r) << endl;

}


//面向对象
class Circle
{
public:

	//一般修改一个私有成员的方法 叫 getter  和setter方法

	//写一个m_r的setter方法
	void setR(double r) {
		m_r = r;
	}

	//写一个m_r的getter方法
	double getR() {
		return m_r;
	}

	//得到周长的方法(成员函数)
	double getGirth() {
		return m_r * 3.14 * 2;
	}

	//得到面积的方法
	double getArea() {
		return 3.14 * m_r*m_r;
	}
private://在private下定义的成员变量 称为私有成员
	double m_r; //半径
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
	double area ; //面积
	double girth; //周长
};

int main(void)
{
	Circle c1;

	//c.m_r = 10.0;
	c1.setR(10.0);

	cout << "c1 的半径是  " << c1.getR() << "  c1 的周长是" << c1.getGirth() << "  c1的面积是" << c1.getArea() << endl;

	Circle c2;
	c2.setR(20.0);

	cout << "c2 的半径是  " << c2.getR() << "  c2的周长是" << c2.getGirth() << "  c2的面积是" << c2.getArea() << endl;

	Circle2 c3;

	c3.setR(30.0);
	cout << "c3 的半径是  " << c3.getR() << "  c3的周长是" << c3.getGirth() << "  c3的面积是" << c3.getArea() << endl;


	return 0;
}