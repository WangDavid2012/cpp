#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
using namespace std;


int main(){


	int count = 0;
	int* p = NULL;
	vector<int> v;
	v.reserve(100000);
	
	for (int i = 0; i < 100000; i++){
		v.push_back(i);
		if (p != &v[0]){
			count++;
			p = &v[0];
		}
	}

	cout << "count:" << count << endl;

	cout << "ÈÝÁ¿£º" << v.capacity() << endl;
	cout << "´óÐ¡:" << v.size() << endl;




	vector<int> v2;
	for (int i = 0; i < 5;i++){
		v2.push_back(i);
	}


	for (vector<int>::iterator it = v2.begin(); it != v2.end();it++){
		cout << *it << " ";
	}
	cout << endl;

	v2.resize(3);

	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++){
		cout << *it << " ";
	}
	cout << endl;


	v2.resize(6);

	for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	system("pause");
	return EXIT_SUCCESS;
}
