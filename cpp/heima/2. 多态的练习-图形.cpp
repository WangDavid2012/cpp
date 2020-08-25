#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//实现一个抽象类
class Shape
{
public:
	//显示图形的基本属性
	virtual void show() = 0;

	//显示图形的面积
	virtual void showArea() = 0;

	//为了让父类指针可以析构子类对象
	virtual ~Shape() {

	}
};


//实现层
class Circle :public Shape
{
public:
	Circle(double r) {
		this->r = r;
	}
	~Circle() {
		cout << "~Circle()" << endl;
	}
	//显示图形的基本属性
	virtual void show()
	{
		cout << "圆的半径是" << r << endl;
	}

	//显示图形的面积
	virtual void showArea() {
		cout << "圆的面积是" << 3.14*r*r << endl;
	}

private:
	double r;
};


class Square :public Shape
{
public:
	Square(double a){
		this->a = a;
	}
	~Square() {
		cout << "~Square()" << endl;
	}
	//显示图形的基本属性
	virtual void show()  {
		cout << "正方形的边长是" << a << endl;
	}

	//显示图形的面积
	virtual void showArea() {
		cout << "正方形的面积是" << a * a << endl;
	}
private:
	double a;
};


//业务层
int main(void)
{
	Shape *array[2]; //指针数组， 数组中每一个元素都是一个Shape指针

	for (int i = 0; i < 2; i++) {
		//生成图形
		if (i == 0) {
			//生成一个圆
			double r;
			cout << "请输入圆的半径:" << endl;
			cin >> r;
			array[i] = new Circle(r);
		}
		else if (i == 1)
		{
			//生成一个正方形
			double a;
			cout << "请输入正方形的边长" << endl;
			cin >> a;
			array[i] = new Square(a);
		}
	}

	for (int i = 0; i < 2; i++) {
		array[i]->show();
		array[i]->showArea();

		delete array[i]; //delete的是 Shape指针所指向的 具体的对象
	}
	
	return 0;
}