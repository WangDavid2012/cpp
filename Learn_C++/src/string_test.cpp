#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int string_test()
{
	string str1 = "hello";
	int length = str1.length();

	char data[8] = { 0x68,0x04, 0x43,0x00,0x00,0x00 };
	cout << hex << (unsigned int)(unsigned char)data << endl;

	//������5��������\0�ַ�
	printf("����str.length()������ȡ�ַ������ȣ�%d\n\n", length);
	return 0;
}
int string_test1()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string str4 = str1 + str2;
	string str5 = str3 + str2;
	cout << "�ַ���str1+str2���ӽ����" << str4 << endl;
	cout << endl;
	cout << "�ַ���str3+str2���ӽ����" << str5 << endl;
	return 0;
}

void string_test2()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string::const_iterator it = str1.begin();
	cout << *it << endl;


	//end��ָ�����һ���ַ������Ԫ�أ����Ҳ������,����cout << *it << endl;��������ᱨ��
	it = str1.end();
	it--;
	cout << *it << endl;

}

int string_test3()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	//string ת����unsigned char
	string str = "csdn";
	unsigned char dst[128] = "";
	strcpy((char*)dst, str.c_str());

	cout << "dst:" << hex << dst[0] << endl;

	char *d = new char[20];   //��Ϊ��һ�����ﲻ��ֱ�Ӹ�ֵ������ָ�����Ϳ��Բ���const char *
	strcpy(d, str3.c_str());  //c_str ȡ��C����const char* �ַ���
	cout << "d:" << d << endl;

	return 0;
}





//char* �� stringת��
void test01() {

	//string����ת��Ϊchar*�ַ���
	string s = "abc";
	const char* str = s.c_str();

	//char*�����ַ���ת��Ϊstring�����ַ���
	char* str2 = "acbd";
	string s2(str2);

}

//string��ʼ��
void test02() {

	string s; //Ĭ�Ϲ���
	string s2 = "acbd";
	string s3(s2);

	string s4(10, 'c');


	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;

}

//string�����ַ�����ֵ�ʹ�ȡ
void test03() {


	//string������ֵ
	string s;
	s = "abcd";

	string s2;
	s2.assign("pppp");


	//string������ȡ
	string s3 = "abcdefg";
	for (int i = 0; i < s3.size(); i++) {
		cout << s3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s3.size(); i++) {
		cout << s3.at(i) << " ";
	}
	cout << endl;


	//�������ʷ�ʽ����Խ��ʱ�򣬲������쳣��ֱ�ӹҵ�
	//at���׳��쳣
	try {
		//cout << s3[100] << endl;
		cout << s3.at(100) << endl;
	}
	catch (...) {
		cout << "����Խ��!" << endl;
	}


}

//string����ƴ�Ӳ���
void test04() {

	string s1 = "aaa";
	string s2 = "bbb";

	//string s3 = s1 + s2;
	//cout << s3 << endl;

	//s1 += s2;
	//cout << s1 << endl;

	//��Ա������ʽ append
	s1.append(s2);
	cout << s1 << endl;
}

//string���Һ��滻 �Ƚ�
void test05() {

	string s = " acbdefg";
	//����
	string target = "bd";
	int pos = s.find(target);
	char* target2 = "ef";
	int pos2 = s.find(target2);

	cout << "pos:" << pos << endl;
	cout << "pos2:" << pos2 << endl;

	int pos3 = s.rfind(target);
	cout << "pos3:" << pos3 << endl;

	//�ַ����滻
	string s1 = "acbd";
	s.replace(0, 2, s1);
	cout << s << endl;


}

//string �Ƚ� �Ӵ� �����ɾ��
void test06() {

	//�Ƚ�
	string s1 = "abc";
	string s2 = "abd";

	int ret = s1.compare(s2);
	if (ret == 1) {

		cout << "s1 > s2" << endl;
	}
	else if (ret == -1) {

		cout << "s1 < s2" << endl;

	}
	else {
		cout << "s1 == s2" << endl;
	}

	//�Ӵ�
	string s3 = "abcdefg";
	string s4 = s3.substr(0, 2);
	cout << "s4" << s4 << endl;

	//�����ɾ��
	string s5 = "abcd";
	s5.insert(0, "pppp");
	string s6 = "qqqq";
	s5.insert(s5.size(), s6);

	cout << s5 << endl;

	s5.erase(0, 4);
	cout << s5 << endl;


}











