#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
cin.get() //һ��ֻ�ܶ�ȡһ���ַ�
cin.get(һ������) //��һ���ַ�
cin.get(��������) //���Զ��ַ���
cin.getline()
cin.ignore()
cin.putback()
*/

//cin��operator>>������ //���ݻس���ˢ�»�����  ���ݿո�������ÿ������������
void test1()
{
	int myInt;
	long myLong;

	char buf[128] = { 0 };

	cin >> myInt;
	cin >> myLong;
	cin >> buf;

	cout << "myInt: " << myInt << endl;
	cout << "myLong: " << myLong << endl;
	cout << "buf: " << buf << endl;
}


//cin.get()����
void test2()
{
	char ch;

	//cin.get()��������Ĳ���EOF��ʶ������ô����Զ�������ȴ�
	//�Ӽ�������ctrl+z ����EOF��ʶ��
	while ((ch = cin.get() )!= EOF) {
		cout << ch << endl;
	}
}

void test3()
{
	char a, b, c;

	char buf[10] = { 0 };

	cout << "�����뻺����ȥ��ȡ���ݣ������������û�����ݣ�������" << endl;
	//cin.get(a); //�����뻺����ȥ��ȡ���ݣ�����о͸�a
	//cin.get(b);
	//cin.get(c);
	//cin.get(a).get(b).get(c);


	//cout << "a  =" << a << endl;
	//cout << "b  =" << b<< endl;
	//cout << "c  =" << c<< endl;

	cin.get(buf, 10, ' ');

	cout << buf << endl;
}

//cin.getline()
void test4()
{
	char buf[128] = { 0 };
	cout << "������һ���ַ��� aa bb cc dd" << endl;
	cin.getline(buf, 128); //�����뻺�����ж����ݵ�buf�У�����128 ��֪������\nΪֹ

	cout << "buf:" <<buf << endl;
}


//cin.ignore()
void test5()
{
	char buf1[128];
	char buf2[128];

	cout << "������һ���ַ��� aa  bb cc dd" << endl;
	cin >> buf1; //aa
	cin.ignore(2);
	cin.getline(buf2, 128);// bb cc dd

	cout << "buf1:" << buf1 << endl;
	cout << "buf2:" << buf2 << endl;

}

//cin.putback()
void test6()
{
	cout << "������һ�����ֻ����ַ���" << endl;
	char ch;
	ch = cin.get(); //�����뻺����ȥ��һ���ַ�
	if ((ch >= '0') && ch <= '9') {
		cout << "�������һ������" << endl;
		int num;
		//��ʱ���ֵ�һ���ַ��Ѿ��������ˡ� ��Ҫ��ch�Żص����뻺����
		cin.putback(ch); //��ch�ԻỺ������ λ�þͻ�������ͷ����
		cin >> num;

		cout << "num =" << num << endl;
	}
	else {
		cout << "�������һ���ַ���" << endl;
		char buf[128] = { 0 };
		//cin.putback(ch);
		cin.getline(buf, 128);

		cout << "buf:" << buf << endl;
	}
}

int main(void)
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
	
	return 0;
}