#include <iostream>

using namespace std;


// ������ʽ���õ�ѧϰ
// explicit�����Ľ���!!!
// explicit���������ã�explicit���캯����������ֹ��ʽת����
class Test1 {
public:
	Test1(int n) {  // ��ͨ��ʽ�Ĺ��캯��
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(��ʽ)���캯��
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // ��ʽ�����乹�캯��,�ɹ�
	//Test2 t2 = 12;  // �������,������ʽ�����乹�캯��
	Test2 t3(12);   // ��ʽ���óɹ�
	return 0;
}
class Test {
public:
	Test() :a(0) {
		cout << "void\n";
	}
	explicit Test(int i) :a(i) {
		cout << "int\n";
	}
	Test(short s) :a(s) {
		cout << "short\n";
	}
	Test & operator=(int n) {
		a = n;
		cout << "operator = ";
	}
private:
	int a;
};
//����һ�������Ĺ��캯������ʹ�ø�ֵ�����ʽ��������ʼ������; 
//��explicit���캯��ֻ�ܱ���ʽ����!���ԣ��������short��
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
