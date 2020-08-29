#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
using namespace std;

//for_each�㷨
class print{
public:
	print() :count(0){}
	void operator()(int v){
		count++;
		cout << v << " ";
	}

	int count;
};
void test01(){

	vector<int> v;
	for (int i = 0; i < 10;i++){
		v.push_back(i);
	}

	/*
		template<class _InIt,
		class _Fn1> inline
		_Fn1 for_each(_InIt _First, _InIt _Last, _Fn1 _Func)
		{	// perform function for each element
		_DEBUG_RANGE(_First, _Last);
		_DEBUG_POINTER(_Func);
		_For_each(_Unchecked(_First), _Unchecked(_Last), _Func);

		return (_STD move(_Func));
	}

	*/
	print p1;
	print p2 =  for_each(v.begin(), v.end(), p1);
	cout << endl;
	cout << "count:" << p1.count << endl;
	cout << "count" << p2.count << endl;

}

//transform�㷨
class myplus100{
public:
	int operator()(int v){
		return v + 100;
	}
};

class myminute{
public:
	int operator()(int v1,int v2){
		return v2 - v1;
	}
};
void test02(){
	


	//��һ�����  һ�������е�Ԫ�ؾ������� �ѽ���Ž�Ŀ��������(v2)
	/*

	vector<int> v1,v2;
	for (int i = 0; i < 10; i++){
	v1.push_back(i);
	}


	v2.resize(v1.size());

	for_each(v2.begin(), v2.end(), print());
	cout << endl;
	transform(v1.begin(), v1.end(), v2.begin(), myplus100());

	for_each(v2.begin(), v2.end(), print());
	cout << endl;
	*/


	//�ڶ��ַ�ʽ
	vector<int> v1, v2,v3;
	for (int i = 0; i < 10; i++){
		v1.push_back(i);
		v2.push_back(i + 1);
	}

	v3.resize(v1.size());
	for_each(v3.begin(), v3.end(), print());
	cout << endl;
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), myminute());
	for_each(v3.begin(), v3.end(), print());
	cout << endl;

}


int main(){


	//test01();
	test02();


	system("pause");
	return EXIT_SUCCESS;
}
