<<<<<<< HEAD
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
=======
﻿#include <iostream>

using namespace std;

// 关于显式调用的学习
// explicit函数的介绍!!!
// explicit函数的作用：explicit构造函数是用来防止隐式转换的
class Test1 {
public:
	Test1(int n) {  // 普通隐式的构造函数
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(显式)构造函数
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // 隐式调用其构造函数,成功
	//Test2 t2 = 12;  // 编译错误,不能隐式调用其构造函数
	Test2 t3(12);   // 显式调用成功
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
//接受一个参数的构造函数允许使用赋值语句隐式调用来初始化对象;
//而explicit构造函数只能被显式调用!所以，输出的是short！
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
