#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;


int main(){


	//��һ�ַ�ʽ ����һ��pair
	pair<int, string> mypair(10,"aaa");
	cout << mypair.first << endl;
	cout << mypair.second << endl;

	//�ڶ��� ����pair
	pair<string,string> mypair2 =  make_pair("aaa","bbb");
	//auto mypair2 = make_pair("aaa", "bbb");
	cout << mypair2.first << " " << mypair2.second << endl;

	//������ 
	pair<int, string> mypair3 = mypair; //��������


	system("pause");
	return EXIT_SUCCESS;
}
