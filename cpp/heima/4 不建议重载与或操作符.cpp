#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test(int value)
	{
		this->value = value;
	}

	int getValue()
	{
		cout << "value = " << this->value << endl;
		return this->value;
	}

	Test operator+(Test &another)
	{
		cout << "ִ����+���ز�����" << endl;
		Test temp(this->value + another.value);
		return temp;
	}

	//����&&������  
	bool operator&&(Test &another)
	{
		cout << "ִ����&&���ز�����" << endl;
		if (this->value && another.value) {
			return true;
		}
		else{
			return false;
		}
	}
	//����||������  
	bool operator||(Test &another)
	{
		cout << "ִ����||���ز�����" << endl;
		if (this->value || another.value) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int value;
};

int main(void)
{
	int a = 10;
	int b = 20;

	a = 0;

	//��ͨ��&& ��||���ж�·������
	if (a && (a = 20)) //&& ����������߼� ֱ���˳�
	{
		
	}

	cout << "a = " << a << endl;

	a = 10;
	if (a || (a = 20)) //&& ��������� �߼� ֱ���˳�
	{

	}
	cout << "a = " << a << endl;


	cout << " --------   " << endl;


	Test t1(10);
	Test t2(20);

	if (t1.getValue() && (t1 + t2).getValue() ) //��ͨ&& ���·����
	{
		cout << "if ����ɹ�" << endl;
	}


	cout << " --------   " << endl;

	if (t1 && (t1 + t2))// t1.operator&&(    t1.operator+(t2)   ) //�������ص�&&���ᷢ����·����
	{
		cout << "if ����ɹ�" << endl;
	}


	cout << " --------   " << endl;


	if (t1 || (t1 + t2)) //t1.operator|| (  t1.operator+(t2)    ) 
	{
		cout << "if ����ɹ�" << endl;

	}



	
	return 0;
}