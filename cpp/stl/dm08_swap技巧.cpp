#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
using namespace std;


void print(vector<int>& v){
	for (vector<int>::iterator it = v.begin(); it != v.end();it++){
		cout << *it << " ";
	}
	cout << endl;
}

int main(){

	
	vector<int> v1,v2;
	for (int i = 0; i < 5;i++){
		v1.push_back(i);
	}

	for (int i = 6; i < 10;i++){
		v2.push_back(i);
	}

	print(v1);
	print(v2);
	v1.swap(v2);
	cout << "v1 ��v2����֮��:" << endl;
	print(v1);
	print(v2);


	//swapС����
	vector<int> v;
	v.resize(100);

	cout << "������" << v.capacity() << endl;
	cout << "��С:" << v.size() << endl;

	v.clear();
	v.push_back(2);
	v.push_back(3);

	cout << "������" << v.capacity() << endl;
	cout << "��С:" << v.size() << endl;

	vector<int>(v).swap(v);

	cout << "������" << v.capacity() << endl;
	cout << "��С:" << v.size() << endl;
	

	system("pause");
	return EXIT_SUCCESS;


}
