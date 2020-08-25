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
		this->name = (char*)malloc(len + 1); //��name�ڶ��Ͽ���һ���ռ�
		strcpy(this->name, name);
	}

	//��ֹǳ�����ṩһ����ʾ�Ŀ���
	Student(const Student & another_s)
	{
		this->id = another_s.id;

		int len = strlen(another_s.name);
		this->name = (char*)malloc(len + 1);
		strcpy(this->name, another_s.name);
	}

	//��д�ȺŲ�����
	Student & operator=(const Student & another_s)
	{
		if (this->name != NULL)
		{
			//ԭ�������� ��Ҫ�ͷ�
			delete[] this->name;
			this->name = NULL;
			this->id = 0;
		}
		//����λ�ã�֮ǰ�������ͷ����
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
	char *name; //׼���ڶ��Ͽ��ٿռ�
};

int main(void)
{
	
	Student s1(1, "����");
	Student s2(s1); //������ÿ��������ʱ��һ���ǳ�ʼ����

	Student s3(2, "����");

	s3 = s1; //���ǵ��ÿ������� //Ҳ�������ṩһ��Ĭ�ϵ�=��������


	s1.printS();
	s3.printS();

	return 0;
}