#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;


int main(){


	string email = "zhaosi@itcast.cn";

	int pos1 = email.find("@");
	int pos2 = email.find(".");

	if (pos1 == -1 || pos2 == -1){
		cout << "�����в�����@����.!" << endl;
		system("pause");
		return 0;
	}
	
	if (pos1 > pos2){
		cout << "��������䲻�Ϸ���" << endl;
	}

	string username = email.substr(0, pos1);

	string::iterator pStart = username.begin();
	string::iterator pEnd = username.end();

	while (pStart != pEnd){
		if (*pStart < 97 || *pStart > 122){
			cout << "������ַ�������Сд�ַ�!" << endl;
			system("pause");
			return 0;
		}
		pStart++;
	}
	cout << endl;


	string rightEmail = "zhaosi@itcast.cn";
	int ret = email.compare(rightEmail);
	if (ret != 0){
		cout << "�����ַ������!" << endl;
		system("pause");
		return 0;
	}

	cout << "�����ַ��ȷ!" << endl;


	system("pause");
	return EXIT_SUCCESS;
}
