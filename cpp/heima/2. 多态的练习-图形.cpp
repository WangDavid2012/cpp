#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//ʵ��һ��������
class Shape
{
public:
	//��ʾͼ�εĻ�������
	virtual void show() = 0;

	//��ʾͼ�ε����
	virtual void showArea() = 0;

	//Ϊ���ø���ָ����������������
	virtual ~Shape() {

	}
};


//ʵ�ֲ�
class Circle :public Shape
{
public:
	Circle(double r) {
		this->r = r;
	}
	~Circle() {
		cout << "~Circle()" << endl;
	}
	//��ʾͼ�εĻ�������
	virtual void show()
	{
		cout << "Բ�İ뾶��" << r << endl;
	}

	//��ʾͼ�ε����
	virtual void showArea() {
		cout << "Բ�������" << 3.14*r*r << endl;
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
	//��ʾͼ�εĻ�������
	virtual void show()  {
		cout << "�����εı߳���" << a << endl;
	}

	//��ʾͼ�ε����
	virtual void showArea() {
		cout << "�����ε������" << a * a << endl;
	}
private:
	double a;
};


//ҵ���
int main(void)
{
	Shape *array[2]; //ָ�����飬 ������ÿһ��Ԫ�ض���һ��Shapeָ��

	for (int i = 0; i < 2; i++) {
		//����ͼ��
		if (i == 0) {
			//����һ��Բ
			double r;
			cout << "������Բ�İ뾶:" << endl;
			cin >> r;
			array[i] = new Circle(r);
		}
		else if (i == 1)
		{
			//����һ��������
			double a;
			cout << "�����������εı߳�" << endl;
			cin >> a;
			array[i] = new Square(a);
		}
	}

	for (int i = 0; i < 2; i++) {
		array[i]->show();
		array[i]->showArea();

		delete array[i]; //delete���� Shapeָ����ָ��� ����Ķ���
	}
	
	return 0;
}