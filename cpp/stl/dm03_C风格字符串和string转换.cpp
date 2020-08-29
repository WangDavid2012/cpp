#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;


//char* �� stringת��
void test01(){

	//string����ת��Ϊchar*�ַ���
	string s = "abc";
	const char* str = s.c_str();

	//char*�����ַ���ת��Ϊstring�����ַ���
	char* str2 = "acbd";
	string s2(str2);

}

//string��ʼ��
void test02(){
	
	string s; //Ĭ�Ϲ���
	string s2 = "acbd";
	string s3(s2);

	string s4(10, 'c');


	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;

}

//string�����ַ�����ֵ�ʹ�ȡ
void test03(){
	

	//string������ֵ
	string s;
	s = "abcd";

	string s2;
	s2.assign("pppp");


	//string������ȡ
	string s3 = "abcdefg";
	for (int i = 0; i < s3.size();i++){
		cout << s3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s3.size();i++){
		cout << s3.at(i) << " ";
	}
	cout << endl;


	//�������ʷ�ʽ����Խ��ʱ�򣬲������쳣��ֱ�ӹҵ�
	//at���׳��쳣
	try{
		//cout << s3[100] << endl;
		cout << s3.at(100) << endl;
	}
	catch (...){
		cout << "����Խ��!" << endl;
	}


}

//string����ƴ�Ӳ���
void test04(){

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
void test05(){

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
void test06(){
	
	//�Ƚ�
	string s1 = "abc";
	string s2 = "abd";

	int ret = s1.compare(s2);
	if (ret == 1){

		cout << "s1 > s2" << endl;
	}
	else if (ret == -1){

		cout << "s1 < s2" << endl;
	
	}
	else{
		cout << "s1 == s2" << endl;
	}

	//�Ӵ�
	string s3 = "abcdefg";
	string s4 = s3.substr(0,2);
	cout << "s4" << s4 << endl;

	//�����ɾ��
	string s5 = "abcd";
	s5.insert(0, "pppp");
	string s6 = "qqqq";
	s5.insert(s5.size(), s6);

	cout << s5 << endl;

	s5.erase(0,4);
	cout << s5 << endl;

	 
}

int main(){


	//test02();
	//test03();
	//test04();
	//test05();
	test06();

	system("pause");
	return EXIT_SUCCESS;
}
