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
		cout << "������=�Ų�����" << endl;
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


//�������캯���ĵ�һ������
void test1()
{
	Test t1(1, 2);
	Test t2(t1);
	//ͨ��t1 ��t2 ���и�ֵ

	t2.printT();
}

//�������캯���ĵڶ�����
void test2()
{
	Test t1(1, 2);
	Test t2;
	t2 = t1; //���õĲ��ǿ������캯�������õ��� =�Ų�������Ҳ�ܹ���ɽ�t1��ֵ��t2 �����ǵ���t2�Ŀ������캯����
}


void func(Test t) //Test t = test1::t1; //����þֲ�����t�Ŀ������캯��
{
	cout << "func begin..." << endl;
	t.printT();
	cout << "func end..." << endl;

}

//������
void test3()
{
	cout << "test3 begin ..." << endl;
	Test t1(10, 20); //������һ��t1�Ķ���ͨ��t1���в����Ĺ��캯��
	func(t1);

	cout << "test3 end..." << endl;
}


int func(void)
{
	int a = 10;
	return a;
}
//������
Test func2()
{
	cout << "func2 begin..." << endl;
	Test temp(10, 20); //����temp�Ĵ��������캯��  
	cout << "func2 end.." << endl;
	return temp; // ��һ����ʱ���������� = temp ����temp�����ݸ�������ʱ����������,  ,����������ʱ����
						//����Ŀ������캯���� ��temp����ȥ��
}

void test4() 
{
	cout << "test4 begin " << endl;
	func2();

	//���������ڴ˱������ˣ� ���һ����ʱ����������û���κα���ȥ����������������Ϊ�����ʱ��������û���ô���
	//���������������������ʱ����������
	cout << "test4 end" << endl;
}

void test5()
{
	cout << "test5 begin ..." << endl;
	Test t1 = func2();//�����һ������ȥ���������ʱ���������� ��������Ϊ�����������ת���ˣ��Ͳ������̸������١�
							//t1 = ��������ʱ���� Ϊʲô���ᷢ����������
							//	��ʱ��t1 ȥ���������������ʱ������ ���´���һ��t1 ���Ǹ������������������־ͽ�t1
							//һ������������������Լ������֣��������Ͳ������̸�����������������ˣ�
							//�͵���ͨ�ֲ�����������

	cout << "test5 end..." << endl;

	//�ڴ�ʱ������t1
}

void test6()
{
	cout << "test6 begin..." << endl;
	Test t1; //����t1���޲������캯��
	t1 = func2(); //���õ�=�Ų����� ,,t1 = �������� ������t1��=�Ų�������
						//��ʱ����û�б�ת��������û���Լ������֣� ������������ڴ�û���Լ��ı����� �������ͻ��������١�
	cout << "test6 end..." << endl;
}


int main(void)
{
	
	//test3();
	//test4();

	//func();

	//test5();
	test6();


	return 0;
}