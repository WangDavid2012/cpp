#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;


int main(){


	//第一种方式 创建一个pair
	pair<int, string> mypair(10,"aaa");
	cout << mypair.first << endl;
	cout << mypair.second << endl;

	//第二种 创建pair
	pair<string,string> mypair2 =  make_pair("aaa","bbb");
	//auto mypair2 = make_pair("aaa", "bbb");
	cout << mypair2.first << " " << mypair2.second << endl;

	//第三种 
	pair<int, string> mypair3 = mypair; //拷贝构造


	system("pause");
	return EXIT_SUCCESS;
}
