#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class AA
{
public:
	AA(int a, int b)
	{
		m_a = a;
		m_b = b;
	}

	int getC()
	{
		cout << "c = " << m_c << endl;
		m_c++;
		return m_c;
	}

	static int m_c;//��̬�ĳ�Ա����  //1 ������ڲ������������ ��static
						//��̬�ĳ�Ա�����ǶԱ����������б����еĶ��� ���ǹ���һ���ڴ�����
private:
	int m_a;
	int m_b;
};


//2 ��̬��Ա�����ĳ�ʼ���� ������ⲿȥд
int AA::m_c = 0;

int main(void)
{
	AA aa1(10, 20), aa2(100,200), aa3(1000,2000);

	aa1.getC();
	aa2.getC();
	aa3.getC();

	//��ôȥ�޸�һ����̬�ĳ�Ա����
	AA::m_c = 200;

	aa1.getC();
	aa2.getC();
	aa3.getC();



	
	return 0;
}