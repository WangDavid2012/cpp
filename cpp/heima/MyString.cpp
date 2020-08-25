#include "MyString.h"


MyString::MyString()
{
	this->len = 0;
	this->str = NULL;
}


MyString::~MyString()
{
	if (this->str != NULL) {
		cout <<this->str << "执行了析构函数" << endl;
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
		this->len = len; //将字符串的长度设置为0

		this->str = new char[len + 1]; //开辟长度是len的空间
		memset(this->str, 0, len + 1); //将此空间全部清零
	}
}

//拷贝构造函数
//MyString str1 = str2;  MyString str1(str1);
MyString::MyString(const MyString &another)
{
	//直接深拷贝
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
		//需要深拷贝
		int len = strlen(str);
		this->len = len;

		this->str = new char[len + 1]; //已经在堆上开辟了内存，实现了深拷贝
		strcpy(this->str, str); //将str的内容拷贝到 this->str堆空间中
	}
}

MyString & MyString::operator=(const MyString &another)
{
	//先释放原有的内存空间
	if (this->str != NULL) {
		delete[] this->str;
		this->str = NULL;
		this->len = 0;
	}

	//执行深拷贝
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

//实现<<运算
ostream &  operator <<(ostream &os, MyString &s)
{
	os << s.str;

	return os;
}

istream & operator>>(istream &is, MyString &s)
{
	char buf[1024] = { 0 };
	char *temp = buf;
	cout << "请输入一个字符串str:" << endl;
	cin >> temp;

	//到此步， buf中已经存放了 键盘写进的内容

	//深拷贝
	int len = strlen(buf);
	s.str = new char[len + 1];
	strcpy(s.str, buf);
	s.len = len;

	return is;
}