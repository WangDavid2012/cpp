#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

struct teacher
{
	int id;
	char name[64];
};

//2 ��ȫ�ֱ����ļ��������ǿ�� һ���������������������Ƕ��壬ֻ�ܳ���һ��
int g_val ; //ȫ�ֱ���
//int g_val = 10;// ��һ��ȫ�ֱ���

//1 ʵ���Ե���ǿ�� ���ڱ����Ķ����λ�ã��������⣬û��Ҫ��
int test1(void)
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{

	}

	for (int i = 0; i < 10; i++) {
	}
	
	return 0;
}

//2 
void test2()
{
	//teacher t1; //C++�� ��ʹ��struct ʱ����Ҫ�ٽ� struct д����
}

//3 

void f(int i)
{
	cout << "i = " << i << endl;
}

//4 bool����
void test3()
{
	bool flag = true; //�ʹ����߼���
	flag = false;       //�ʹ����߼���

	cout << "bool:sizeof() : " << sizeof(flag) << endl; //boolռһ���ֽڡ�

	flag = true; // Ϊ�� 
	cout << "flag = " << flag << endl; //��bool����Ϊtrue ������ֵ��1

	flag = false; //Ϊ��
	cout << "flag = " << flag << endl;//��bool����Ϊfalse ������ֵ��0

	//flag = 10;
	cout << "flag = " << flag << endl;

	//flag = 100;
	cout << "flag = " << flag << endl;

	//flag = -100;
	cout << "flag = " << flag << endl; //���ܸ�bool��ֵʲô���ķ�0��ֵ�����Ƕ���true 1 


	//flag = 0;
	cout << "flag = " << flag << endl; 

	//bool���͵�ȡֵ��ֻ��0 ��1 


	if (flag == true) { //Ĭ���ж�flag �Ƿ�Ϊtrue

	}

}


void test5()
{
	int a = 10;
	int b = 20;

	(a < b ? a : b) = 30; //������a�����ı��� 
	//a
	cout << "a = " << a << endl;
	(a < b ? 10 : b); //��ľ����� �����Ϊ��ֵ�� ��ô ���صĽ�������г���
}

//c++��const�ļ�ǿ
void test6() {
	const int a = 10; //c++��const ȷʵ��a���˱��������ã�����ͨ��ָ��ļ�Ӹ�ֵ����a��ֵ
							//
	//int const b; //const int , int const �ǵȼ۵�

	int *p = (int*)&a; //��c++������ ���� ��һ��const�ĳ�������ȡ��ַ��
	*p = 20;//C�����п���ͨ��ָ��ļ�Ӹ�ֵ�ı�const���� 
				//*p �Ǹı����ʱ�ı��� ������ ����a����

	printf("a = %d\n", a);
}

#define A (3)
#define B (4)

void test7()
{
	const int a = 3;
	const int b = 4;  //��ʱ˵�� c++�е�const ����һ�������� ��Զ���ᱻ�ı�
								//c++���Զ�const ����ǿ����const ������������˳���

	int array[a + b] = { 0 };

	int array_2[A + B] = { 0 };  // define ��const ���� �ڱ���Ľ׶β�һ���� define��Ԥ������ const �Ǳ�����

//#define ff (10)
	const int ff = 10; //const �Ǳ������� ��ȫ���ϱ��������߼��жϺʹ˷�����
}

void test8()
{
	//cout << "ff = " << ff << endl; //û������Ļ���
}

enum season {
	SPR ,
	SUM ,
	AUT  ,
	WIN
};

void test9()
{
	enum season s = SPR;

	s = SUM; //Ϊ������ö�ٵĿɶ��ԣ� 
	s = AUT;
	s = WIN;

}

struct student
{
	int id;
	char name[64];
};

void change_stu(struct student *s)
{
	s ->id = 10;
}

void change_stu2(const struct student *s)
{
	//s->id = 10; //��ʱs��ָ���������һ������ ���ܹ����޸�
	struct student s2;
	s = &s2;
}

void change_stu3(struct student *const s)
{
	s->id = 10;
	//struct student s2;
	//s = &s2;  //s��һ������ָ��
}

void change_stu4(const struct student *const s)
{
	//s->id = 10;
	//struct student s2;
	//s = &s2;  //s��һ������ָ��
}

int g(int a, int b, int c)
{
	return 100;
}
//����һ��Ҫ�з���ֵ�� �������û�з���ֵ��ҲҪ��void




int main(void)
{
	//f(1, 2, 3); //error ���ں������εļ���������ӵ��ϸ�
	//g(1, 2, 3); //C_++������ �Ժ����βδ���  ��������ֵ �����ϸ�ļ��
	//test3();
	//test5();
	//test6();
	test7();
	test8();
	return 0;
}