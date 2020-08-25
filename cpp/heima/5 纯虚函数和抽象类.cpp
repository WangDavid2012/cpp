#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
using namespace std;

//图形类
//拥有纯虚函数的类， 就叫抽象类
class Shape
{
public:
	//是一个抽象的接口，说明图形是有一个得到面积方法
	virtual  double getArea() = 0;//代表一个接口，一个求图形面积的接口

	//定义一个个打印面积的接口
	virtual void print() = 0;
};

//圆类
//如果 一个子类继承了抽象类， 那么一定要重写这个纯虚函数。
class Circle :public Shape
{
public:
	Circle(double r)
	{
		this->r = r;
	}

	//重写父类抽象类的纯虚函数
	virtual double getArea() 
	{
		return 3.14 *  r * r;
	}

	
	virtual void print() {
		cout << "圆的面积是" << endl;
		cout << this->getArea() << endl;
	}
	
private:
	double r;//半径
};


//实现一个正方形
class Rect :public Shape
{
public:
	Rect(double a)
	{
		this->a = a;
	}
	//是一个抽象的接口，说明图形是有一个得到面积方法
	virtual  double getArea()
	{
		return a*a;
	}

	//顶一个打印面积的接口
	virtual void print()  {
		cout << "正方形的面积是" << endl;
		cout << this->getArea() << endl;
	}
private:
	double a;//边长
};

//三角形
class Tri :public Shape
{
public:
	Tri(double a, double h)
	{
		this->a = a;
		this->h = h;
	}
	virtual  double getArea()  {
		return 0.5 * h * a;
	}

	virtual void print()  {
		cout << "三角形的面积是" << endl;
		cout << this->getArea() << endl;
	}

private:
	double a;//底
	double h;//高
};


//一个传递抽象类 指针的架构函数
void printArea(Shape *p)
{
	p->print();
}

//业务层
int main(void)
{
	//Shape p;//抽象类不能够实例化

	Shape *sp = new Circle(10.0);

	//抽象类的指针就可以调用纯虚函数， 接口
	//sp->getArea();//在此处就发生了多态
	//cout << sp->getArea() << endl;
	 
	//delete sp;

	printArea(sp);

	delete sp;

	//创建一个正方形的对象。用抽象类指针（父类指针）指向子类对象
	sp = new Rect(10.0);

	printArea(sp);
	delete sp;

	//业务层 根本就不关心 具体对象怎么实现的， 只用抽象类的指针就可以。
	Shape *sp2 = new Tri(10, 20);
	sp2->print();
	delete sp2;

	cout << " ------   " << endl;

	return 0;
}




