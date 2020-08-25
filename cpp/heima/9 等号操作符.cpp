#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Student
{
public:
	Student(int id, char *name)  
	{
		this->id = id;

		int len = strlen(name);
		this->name = (char*)malloc(len + 1); //将name在堆上开辟一个空间
		strcpy(this->name, name);
	}

	//防止浅拷贝提供一个显示的拷贝
	Student(const Student & another_s)
	{
		this->id = another_s.id;

		int len = strlen(another_s.name);
		this->name = (char*)malloc(len + 1);
		strcpy(this->name, another_s.name);
	}

	//重写等号操作符
	Student & operator=(const Student & another_s)
	{
		if (this->name != NULL)
		{
			//原来有数据 需要释放
			delete[] this->name;
			this->name = NULL;
			this->id = 0;
		}
		//到这位置，之前的数据释放完毕
		this->id = another_s.id;
		int len = strlen(another_s.name);
		this->name = (char*)malloc(len + 1);
		strcpy(this->name, another_s.name);

		return *this;
	}

	~Student() {
		if (this->name != NULL) {
			delete[] this->name;
			this->name = NULL;
			this->id = 0;
		}
	}

	void printS()
	{
		cout << "id : " << this->id << ",  name = " << this->name << endl;
	}
private:
	int id;
	char *name; //准备在堆上开辟空间
};

int main(void)
{
	
	Student s1(1, "张三");
	Student s2(s1); //当你调用拷贝构造的时候，一定是初始化，

	Student s3(2, "李四");

	s3 = s1; //不是调用拷贝构造 //也给我们提供一个默认的=操作符。


	s1.printS();
	s3.printS();

	return 0;
}