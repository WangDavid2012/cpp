#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	//Ĭ�Ϲ��캯���� ����һ���޲����Ĺ��캯����
	//�������ʾ�ṩ���캯����ϵͳ���ǵ���Ĭ�ϵĹ��캯��
	/*
	Test() {} Ĭ�ϵĹ��캯�����Ѿ��ֶ��ṩ��Ĭ�Ͼͱ�����
	*/

	//��������ṩ��һ����ʾ�Ĺ��캯������ôĬ�ϵĹ��캯���ͱ����ص��ˡ�
	//���캯��һ���ֶ��ṩ�� Ĭ�Ͻ��������ڡ�
	Test(int x, int y)
	{
		
		m_x = x;
		m_y = y;
		cout << "�������в����Ĺ��캯��" << endl;
	}

	//�޲����Ĺ��캯��
	Test(){
		m_x = 0;
		m_y = 0;
		cout << "�������޲����Ĺ��캯��" << endl;
	}


	//�������캯�� ����ͨ����һ��Test���� another ����������п���
	Test(const Test & another)
	{
		m_x = another.m_x;
		m_y = another.m_y;
		cout << "�����˿������캯��" << endl;
	}

	//�ȺŲ�����
	void operator = (const Test &t)
	{
		m_x = t.m_x;
		m_y = t.m_y;
	}

	void printT()
	{
		cout << "x : " << m_x << ", y : " << m_y << endl;
	}

	//�ṩһ����������
	~Test()
	{
		cout << "~Test��������������ִ����" << endl;
		cout << "(" << m_x << ", " << m_y << ")" << "��������" << endl;
	}
	
private:
	int m_x;
	int m_y;
};

int main(void)
{
	Test t1; //�����޲εĹ��캯��
	Test t2(10, 20);
	//Test t3(10, 20, 30);
	t2.printT();
	Test t3(t2); //����t3�Ŀ������캯��  //���ÿ������캯���ķ�ʽ
	t3.printT();
	//Test t4 = t2; // ��Ȼ�ǵ���t4�Ŀ������캯����

	Test t4(100, 200); //����t4 �����������Ĺ��캯��

	Test t5; //�ȵ����޲ҹ��졣
	t5 = t2; //������ÿ������캯�� //����=�����ز�����  ��ֵ������


	//���������ĵ���˳�� ������Ĺ���˳���෴�� ˭�ȹ��죬˭���һ����������
	
	return 0;
}