#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "MyString.h"

using namespace std;

int main(void)
{
	MyString str1(10); 

	cout << str1.getLen() << endl;
	
	cout << str1 << endl;

	MyString str2 = "123456789";

	cout << str2 << endl;
	cout << str2.getLen() << endl;

	cout << " --str3---  " << endl;

	MyString str3 = str2;

	cout << str3 << endl;
	cout << str3.getLen() << endl;

	str1 = str3; //str1.operator=(str3);
	
	cout << " --str1---  " << endl;
	cout << str1 << endl;
	cout << str1.getLen() << endl;

	if (str1 == str3) {
		cout << "str1 == str3" << endl;
	}

	MyString str4;

	cin >> str4;

	cout << str4 << endl;

	if (str1 != str4) {
		cout << "str1 != str4" << endl;
	}

	if (str1 > str4) {
		cout << "str1 > str4" << endl;
	}

	if (str1 < str4) {
		cout << "str1 < str4 " << endl;
	}

	return 0;
}