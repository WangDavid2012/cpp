#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//�Ҿ���
class Furniture
{
public:
	int m; //����  
};
//���������̳б����� �������Ὣ�����еĳ�Ա�� ֻ����һ�ݡ�

//����
class Bed: virtual  public Furniture
{
public:
	void sleep()
	{
		cout << "�ڴ���˯��" << endl;
	}
};

//ɳ����
class Sofa :virtual public Furniture
{
public:
	void sit()
	{
		cout << "��ɳ����˯��" << endl;
	}
};

//ɳ����
class SofaBed :public Bed, public Sofa
{
public:
	void sitAndSleep()
	{
		sit();//sofa
		sleep();//bed
	}
};

int main(void)
{
	Bed b;
	b.sleep();

	cout << "  ---- " << endl;

	Sofa s; //m 
	s.m = 100;
	s.sit();
	cout << "------- " << endl;

	SofaBed sb;
	sb.sitAndSleep();

	sb.m; //��̳���� 
	

	return 0;
}
