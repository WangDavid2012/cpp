#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	//���캯��(������)�� ��Ϊ�˸������ṩ��ʼ�������ֵġ�
	//�������ָ�������һ���ģ�û�з���ֵ�����ҿ�������

	//�޲����Ĺ��캯��
	Test()
	{
		m_x = 0;
		m_y = 0;
		p = (char*)malloc(100);
		strcpy(p, "123");
	}

	//�������Ĺ��캯��
	Test(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	//һ�������Ĺ��캯��
	Test(int x)
	{
		m_x = x;
		m_y = 0;
	}


	//�������� : ~+����  û���κεĲ���
	~Test()
	{
		cout << "Test ����������~Test() ��������" << endl;
		if (p != NULL) {
			cout << "p�Ķѿռ䱻�ͷ���" << endl;
			free(p);
			p = NULL;
		}
	}


	void printT()
	{
		cout << "x : " << m_x << ", y: " << m_y << endl;
	}

	void init(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
private:
	int m_x;
	int m_y;
	char *p;
};

void test1()
{
	Test t1; //�����޲����Ĺ��캯��
		//t1 ��һ���ֲ������� ����������test1����һ���ģ� ��test1��������ִ�������Ҫ ������t1����
	//t1��������֮ǰ��ϵͳ�ͻ�Ĭ�ϵĵ���t1����������
	t1.printT();


	return;
}

int main(void)
{
	//Test t1; //t1 �ڿ����ڴ�֮��t1�е�m_x  m_y �����ֵ
	//
	//t1.init(10, 20); //ÿ�ζ���Ҫ��ʾ�ĵ���һ����ʼ���ĺ�����

	//�ܲ����ṩһ�� �ڴ���һ�������ʱ��͸�����ʼ���أ�

	test1();

	//Test t1;  //����һ������ ��������ֱ�ӵ����޲����Ĺ��캯����

	//Test t2(10, 20); //�ڴ����������֮�� ���Ѿ��������һЩ��Ա������ʼ����

	//Test t3(10);
	
	return 0;
}