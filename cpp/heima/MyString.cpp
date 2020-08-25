#include "MyString.h"


MyString::MyString()
{
	this->len = 0;
	this->str = NULL;
}


MyString::~MyString()
{
	if (this->str != NULL) {
		cout <<this->str << "ִ������������" << endl;
		delete[] this->str;
		this->str = NULL;
		this->len = 0;
	}
}

MyString::MyString(int len)
{
	if (len == 0)
	{
		this->len = 0;
		this->str = new char[len + 1];
		strcpy(this->str, "");
	}
	else {
		this->len = len; //���ַ����ĳ�������Ϊ0

		this->str = new char[len + 1]; //���ٳ�����len�Ŀռ�
		memset(this->str, 0, len + 1); //���˿ռ�ȫ������
	}
}

//�������캯��
//MyString str1 = str2;  MyString str1(str1);
MyString::MyString(const MyString &another)
{
	//ֱ�����
	int len = strlen(another.str);
	this->str = new char[len + 1];
	strcpy(this->str, another.str);

	this->len = len;
}

//MyString str1 = "1321321"
//MyString str1("1231231");
MyString::MyString(const char *str)
{
	if (str == NULL) {
		this->len = 0;
		this->str = new char[len + 1];
		strcpy(this->str, "");
	}
	else {
		//��Ҫ���
		int len = strlen(str);
		this->len = len;

		this->str = new char[len + 1]; //�Ѿ��ڶ��Ͽ������ڴ棬ʵ�������
		strcpy(this->str, str); //��str�����ݿ����� this->str�ѿռ���
	}
}

MyString & MyString::operator=(const MyString &another)
{
	//���ͷ�ԭ�е��ڴ�ռ�
	if (this->str != NULL) {
		delete[] this->str;
		this->str = NULL;
		this->len = 0;
	}

	//ִ�����
	int len = strlen(another.str);
	this->str = new char[len + 1];
	strcpy(this->str, another.str);

	this->len = another.len;

	return *this;
}


char & MyString::operator[](int index)
{
	return this->str[index];
}

bool MyString::operator ==(const MyString &another)
{
	if (strcmp(this->str, another.str) == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool MyString::operator !=(const MyString &another)
{
	return !(*this == another);
}

bool MyString::operator>(const MyString &myString)
{
	int ret = strcmp(this->str, myString.str);
	if (ret > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool MyString::operator<(const MyString &myString)
{
	int ret = strcmp(this->str, myString.str);
	if (ret < 0) {
		return true;
	}
	else {
		return false;
	}
}

int MyString::getLen()
{
	return this->len;
}

//ʵ��<<����
ostream &  operator <<(ostream &os, MyString &s)
{
	os << s.str;

	return os;
}

istream & operator>>(istream &is, MyString &s)
{
	char buf[1024] = { 0 };
	char *temp = buf;
	cout << "������һ���ַ���str:" << endl;
	cin >> temp;

	//���˲��� buf���Ѿ������ ����д��������

	//���
	int len = strlen(buf);
	s.str = new char[len + 1];
	strcpy(s.str, buf);
	s.len = len;

	return is;
}