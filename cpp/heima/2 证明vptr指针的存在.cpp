#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	void func(int a, int b)
	{
		cout << "Parent func " << endl;
	}
private:
	int a;
};

class Parent2
{
public:
	virtual void func(int a, int b)
	{
		cout << "Parent2 func " << endl;
	}
private:
	int a;
};

int main(void)
{
	Parent p1;
	Parent2 p2;

	cout << "sizeof(p1)" << sizeof(p1) << endl;
	cout << "sizeof(p2)" << sizeof(p2) << endl; //p2�������4���ֽھ��Ǵ��vptrָ��Ŀռ��С
																		//vptrָ�����Ƿ��ʲ��ˣ�vptrָ��ָ�����Parent2����麯����
																		//�˱���Ŀǰ��һ�� �麯�� func(inta, intb)����ڵ�ַ��


	
	return 0;
}