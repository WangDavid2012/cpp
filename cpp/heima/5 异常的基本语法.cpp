#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//��һ���ܹ��׳��쳣�ĺ���
void divide(int x, int y)
{
	if (y == 0) {
		//�����������ķǷ�
		cout << "����y == 0" << endl;
		throw 0; //throw divide���˳��ˣ� return
	}

	cout << "x/y = " << x / y << endl;
}

void use_divide(int x, int y)
{
	try {
		divide(x, y);
	}
	catch (...) {
		cout << "use_divide ����δ֪�쳣��������" << endl;
		throw ; //�м�㺯���������쳣���������մ���ֱ��������
	}
}
//1 �쳣�Ĳ������ϸ�������ƥ��
//2 �쳣���Բ������� ���������ף��м����Բ���Ҫ������һ��ͳһ�����쳣�ĺ���ͳһ����
//3 ���˵�쳣һֱ�����ף� û�к������� ���ղ���ϵͳ�Ὣ����������

int main(void)
{
	try {
		use_divide(10, 0);
	}
	catch (int e)
	{
		cout << "�������쳣 e = " << e << endl;
	}
	catch (char e)
	{
		cout << "�������쳣 e = " << e << endl;
		throw e;
	}
	catch (...)//�ܹ������������͵��쳣
	{
		cout << "����δ֪�쳣" << endl;
	}
	
	return 0;
}