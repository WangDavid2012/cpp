#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>

using namespace std;

//merge�㷨
void print(int v){
	cout << v << " ";
}
void test02(){
	
	vector<int> v1,v2,v3;
	v1.push_back(6);
	v1.push_back(2);
	v1.push_back(8);
	v1.push_back(4);

	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(6);
	v2.push_back(4);

	sort(v1.begin(),v1.end(),greater<int>());
	sort(v2.begin(), v2.end(), greater<int>());

	/*
		
		template<class _InIt1,
		class _InIt2,
		class _OutIt> inline
		_OutIt merge(_InIt1 _First1, _InIt1 _Last1,
		_InIt2 _First2, _InIt2 _Last2,
		_OutIt _Dest)
		{	// copy merging ranges, both using operator<
		return (_STD merge(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
		}
	
	*/

	v3.resize(v1.size()+v2.size());
	for_each(v3.begin(), v3.end(), print);


	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin(), greater<int>());

	for_each(v3.begin(), v3.end(), print);


}

//sort�㷨
void test03(){
	
	vector<int> v;
	v.push_back(6);
	v.push_back(2);
	v.push_back(8);
	v.push_back(4);

	sort(v.begin(),v.end(),greater<int>()); //�Ӵ�С����  Ĭ�ϴ�С����
}

//random_shuffle  ϴ��  �������е�Ԫ�� ˳�����
void test04(){
	
	vector<int> v;
	for (int i = 0; i < 10;i++){
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), print);
	cout << endl;
	random_shuffle(v.begin(),v.end());
	for_each(v.begin(), v.end(), print);
	cout << endl;
	random_shuffle(v.begin(), v.end());
	for_each(v.begin(), v.end(), print);
	cout << endl;

}

//reverse ��ת�����е�Ԫ��
void test05(){

	vector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), print);
	cout << endl;

	reverse(v.begin(),v.end());

	for_each(v.begin(), v.end(), print);
	cout << endl;



}

int main(){


	//test02();
	//test04();
	test05();

	system("pause");
	return EXIT_SUCCESS;
}
