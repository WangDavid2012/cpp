#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<set>
using namespace std;


int main(){


	multiset<int> muset;
	muset.insert(10);
	muset.insert(20);
	muset.insert(5);
	muset.insert(35);
	muset.insert(5);


	for (multiset<int>::iterator it = muset.begin(); it != muset.end();it ++){
		cout << *it << " ";
	}
	cout << endl;	
	

	system("pause");
	return EXIT_SUCCESS;
}
