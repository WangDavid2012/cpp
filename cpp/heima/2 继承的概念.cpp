#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
	Student(int id, char *name)
	{
		this->name = name;
		this->id = id;
	}

	void printS()
	{
		cout << "id =  " << id << " name  =" << name << endl;
	}

private:
	string name;
	int id;
};

//��C���Եķ�ʽ
class Student2
{
public:
	Student2(int id, string name, int score)
	{
		this->id = id;
		this->name = name;
		this->score = score;
	}

	void printS()
	{
		cout << "id =  " << id << " name  =" << name << endl;
		cout << "score = " << score << endl;
	}

private:

	string name;
	int id;
	//���һ����Ա����
	int score;
};

//��C++�ļ̳еķ�ʽ
class Student3 : public Student
{
public:
	Student3(int id, char * name, int score) : Student(id, name)//����̳й����ĳ�Ա���� ͨ������Ĺ�����������
	{
		this->score = score;
		//this->id = id;
	}

	void printS()
	{
		Student::printS();// �ȵ��ø����еķ���
		cout << "score = " << this->score << endl;
	}
private:
	int score;//��ӵ�һ����Ա����
};

int main(void)
{
	Student3 s(1, "zhang3", 88);

	s.printS();
	
	return 0;
}