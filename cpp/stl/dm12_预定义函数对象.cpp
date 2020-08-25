#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<functional>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/*
	
	template<class T> T plus<T>//�ӷ��º���
	template<class T> T minute<T>//�����º���
	template<class T> T multiplies<T>//�˷��º���
	template<class T> T divides<T>//�����º���
	template<class T> T modulus<T>//ȡģ�º���
	template<class T> T negate<T>//ȡ���º���
*/


void  test01(){


	
	plus<int> myplus;
	int ret = myplus(10, 20);
	cout << ret << endl;
	plus<string> myplus2;


	string s1 = "aaa";
	string s2 = "bbb";
	string ret2 = myplus2(s1, s2);

	cout << ret2 << endl;

	cout << plus<int>()(10, 20) << endl;

}

//transform
void print(int v){
	cout << v << " ";
}
void test02(){
	
	vector<int> v1, v2, v3;

	for (int i = 0; i < 10;i++){
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	v3.resize(v1.size());
	//plus<int> myplus;
	for_each(v3.begin(), v3.end(), print);
	cout << endl;

	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<int>());

	for_each(v3.begin(), v3.end(), print);
	cout << endl;



}

int main(){


	//test01();
	test02();


	system("pause");
	return EXIT_SUCCESS;
}
