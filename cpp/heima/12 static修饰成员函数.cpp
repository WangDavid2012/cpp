#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;


class Student
{
public:
	Student(int num, double score) {
		m_num = num;
		m_score = score;

		count++;
		sum_score += score;
	}

	static double getAvg()
	{
		return sum_score / count;
	}

private:
	int m_num; //ѧ��
	double m_score; //�ɼ�

	//����һ����¼ѧ�������ľ�̬����
	static int count; //��¼ĿǰStudent���Ѿ������˶��ٸ�ѧ������
	static double sum_score;// �����Ѿ�����ѧ���������score�͡�
};

//��ʼ����̬��Ա����
int Student::count = 0;
double Student::sum_score = 0.0;

int main(void)
{
	Student s1(1, 80);
	Student s2(2, 90);
	Student s3(3, 80);

	//Student::sum_score / Student::count;
	//ʹ��һ����̬�ĳ�Ա����
	double avg = Student::getAvg(); //���Ը�������һ�� ���ȫ�ֺ���

	//s1.getAvg();

	cout << "Ŀǰ��ѧ����ƽ��������" << avg << endl;
	
	return 0;
}