#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//�Զ����MyException Ҳ�����׼���쳣��
class MyException :public exception
{
public:
	MyException(char *str) {
		this->m_s = str;
	}
	virtual const char *what() const{
		cout << "MyException ���쳣" << endl;
		return this->m_s;
	}
private:
	char *m_s;
};

class Teacher
{
public:
	Teacher(string name, int id)
	{
		this->name = name;
		if (id > 100) {
			string str = "id ������Χ";
			throw out_of_range(str);
		}
		this->id = id;
	}
private:
	int id;
	string name;
};

int main(void)
{
	try
	{
		Teacher t1("zhangsan", 10001);
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	

	try {
		throw MyException("aaaa");

	}
	catch (exception &e){
		cout << e.what() << endl;
	}
	
	return 0;
}