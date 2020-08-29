#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Teacher
{
public:
	//有参数的构造函数
	Teacher(int id, char *name)
	{
		cout << "调用了Teacher 的构造函数" << endl;
		//是给id 赋值
		m_id = id;

		//给姓名赋值
		int len = strlen(name);
		m_name = (char*)malloc(len + 1);
		strcpy(m_name, name);
	}

	//显示写一个拷贝构造函数
	//通过显示拷贝构造函数提供了深拷贝的动作
	Teacher(const Teacher &another)
	{
		m_id = another.m_id; //给id赋值

		int len = strlen(another.m_name);
		m_name = (char*)malloc(len + 1);

		strcpy(m_name, another.m_name);
	}
	~Teacher() {
		//在构造函数中， 已经开辟了内存 所以为了防止泄露
		//在析构函数中，在对象销毁之前，把m_name的内存释放掉
		if (m_name != NULL) {
			free(m_name);
			m_name = NULL;
			cout << "释放掉了m_name" << endl;
		}
	}
private:
	int m_id;
	char *m_name;
};

int main(void)
{
	Teacher t1(1, "zhang3");

	//如果不提供一个显示的拷贝构造函数， 通过系统自带的默认拷贝构造函数
	Teacher t2(t1); //会调用t2的拷贝构造函数，将t1的值拷贝给t2
	
	return 0;
}