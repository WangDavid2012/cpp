#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
using namespace std;

//ͼ����
//ӵ�д��麯�����࣬ �ͽг�����
class Shape
{
public:
	//��һ������Ľӿڣ�˵��ͼ������һ���õ��������
	virtual  double getArea() = 0;//����һ���ӿڣ�һ����ͼ������Ľӿ�

	//����һ������ӡ����Ľӿ�
	virtual void print() = 0;
};

//Բ��
//��� һ������̳��˳����࣬ ��ôһ��Ҫ��д������麯����
class Circle :public Shape
{
public:
	Circle(double r)
	{
		this->r = r;
	}

	//��д���������Ĵ��麯��
	virtual double getArea() 
	{
		return 3.14 *  r * r;
	}

	
	virtual void print() {
		cout << "Բ�������" << endl;
		cout << this->getArea() << endl;
	}
	
private:
	double r;//�뾶
};


//ʵ��һ��������
class Rect :public Shape
{
public:
	Rect(double a)
	{
		this->a = a;
	}
	//��һ������Ľӿڣ�˵��ͼ������һ���õ��������
	virtual  double getArea()
	{
		return a*a;
	}

	//��һ����ӡ����Ľӿ�
	virtual void print()  {
		cout << "�����ε������" << endl;
		cout << this->getArea() << endl;
	}
private:
	double a;//�߳�
};

//������
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
		cout << "�����ε������" << endl;
		cout << this->getArea() << endl;
	}

private:
	double a;//��
	double h;//��
};


//һ�����ݳ����� ָ��ļܹ�����
void printArea(Shape *p)
{
	p->print();
}

//ҵ���
int main(void)
{
	//Shape p;//�����಻�ܹ�ʵ����

	Shape *sp = new Circle(10.0);

	//�������ָ��Ϳ��Ե��ô��麯���� �ӿ�
	//sp->getArea();//�ڴ˴��ͷ����˶�̬
	//cout << sp->getArea() << endl;
	 
	//delete sp;

	printArea(sp);

	delete sp;

	//����һ�������εĶ����ó�����ָ�루����ָ�룩ָ���������
	sp = new Rect(10.0);

	printArea(sp);
	delete sp;

	//ҵ��� �����Ͳ����� ���������ôʵ�ֵģ� ֻ�ó������ָ��Ϳ��ԡ�
	Shape *sp2 = new Tri(10, 20);
	sp2->print();
	delete sp2;

	cout << " ------   " << endl;

	return 0;
}




