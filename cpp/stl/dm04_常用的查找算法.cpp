#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>
using namespace std;


//find算法
void test01(){
	
	vector<int> v;
	v.push_back(8);
	v.push_back(2);
	v.push_back(5);
	v.push_back(6);

	/*
		
		template<class _InIt,
		class _Ty> inline
		_InIt find(_InIt _First, _InIt _Last, const _Ty& _Val)
		{	// find first matching _Val
		_DEBUG_RANGE(_First, _Last);
		return (_Rechecked(_First,
		_Find(_Unchecked(_First), _Unchecked(_Last), _Val)));
		}
	
	*/
	vector<int>::iterator pos =  find(v.begin(),v.end(),5);
	if (pos == v.end()){
		cout << "没有找到！" << endl;
	}
	else{
		cout << "找到了：" << *pos << endl;
	}
}

class student{
public:
	student(int id, int age) :id(id), age(age){}
	int id;
	int age;

	bool operator==(const student& s){
		if (this->id == s.id && this->age == s.age){
			return true;
		}
		else
		{
			return false;
		}
		//return  this->id == s.id && this->age == s.age;
	}
};

//查找对象
void test02(){

	vector<student> v;
	student s1(1, 2), s2(3, 4), s3(5, 6);

	v.push_back(s1);
	v.push_back(s2);
	v.push_back(s3);

	vector<student>::iterator pos = find(v.begin(), v.end(), s1);
	if (pos != v.end()){
		cout << "找到:" << pos->id << " " << pos->age << endl;
	}
	else{
		cout << "没有找到!" << endl;
	}

}

//find_if

class mycompare03{
public:
	bool operator()(int v){
		if (v > 6){
			return true;
		}
		else{
			return false;
		}
	}
};
void test03(){
	
	vector<int> v;
	v.push_back(8);
	v.push_back(2);
	v.push_back(5);
	v.push_back(6);

	/*
		template<class _InIt,
	class _Pr> inline
	_InIt find_if(_InIt _First, _InIt _Last, _Pr _Pred)
	{	// find first satisfying _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Find_if(_Unchecked(_First), _Unchecked(_Last), _Pred)));
	}

	template<class _InIt,
	class _Pr> inline
	_InIt _Find_if(_InIt _First, _InIt _Last, _Pr _Pred)
	{	// find first satisfying _Pred
	for (; _First != _Last; ++_First)
	if (_Pred(*_First))
	break;
	return (_First);
	}


	*/

	vector<int>::iterator pos = find_if(v.begin(), v.end(), mycompare03());
	if (pos == v.end()){
		cout << "没有找到!" << endl;
	}
	else{
		cout << "找到了:" << *pos << endl;
	}

}

//adjacent_find 查找相邻重复元素 并返回第一个重复的元素出现的位置
void test04(){
	
	vector<int> v;
	v.push_back(8);
	v.push_back(2);
	v.push_back(2);
	v.push_back(5);
	v.push_back(6);

	/*
		template<class _FwdIt> inline
	_FwdIt adjacent_find(_FwdIt _First, _FwdIt _Last)
	{	// find first matching successor
	return (_STD adjacent_find(_First, _Last, equal_to<>()));
	}
	
	*/

	vector<int>::iterator pos =  adjacent_find(v.begin(),v.end());
	if (pos == v.end()){
		cout << "么有找到!" << endl;
	}
	else{
		cout << "找到:" << *pos << endl;
	}
}

//binary_search 二分查找法
void test05(){
	
	//binary_search需要对有序的元素进行查找

	vector<int> v;
	v.push_back(8);
	v.push_back(2);
	v.push_back(2);
	v.push_back(5);
	v.push_back(6);

	greater<int> mygreater;
	sort(v.begin(), v.end(), mygreater);  //排序

	/*
		template<class _FwdIt,
	class _Ty> inline
	bool binary_search(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
	{	// test if _Val equivalent to some element, using operator<
	return (_STD binary_search(_First, _Last, _Val, less<>()));
	}
	*/

	bool flag = binary_search(v.begin(), v.end(), 5, mygreater);
	if (flag){
		cout << "查找到！" << endl;
	}
	else{
		cout << "没有查找到！" << endl;
	}

}

//count count_if
class mycompare06{
public:
	bool operator()(int v){
		return v > 2;
	}
};
void test06(){
	
	vector<int> v;
	v.push_back(8);
	v.push_back(2);
	v.push_back(2);
	v.push_back(5);
	v.push_back(6);

	//count算法
	int n = count(v.begin(),v.end(),2);
	cout << "n:" << n << endl;
	//count_if
	/*
		
		template<class _InIt,
		class _Pr> inline
		typename iterator_traits<_InIt>::difference_type
		count_if(_InIt _First, _InIt _Last, _Pr _Pred)
		{	// count elements satisfying _Pred
		_DEBUG_RANGE(_First, _Last);
		_DEBUG_POINTER(_Pred);
		return (_Count_if(_Unchecked(_First), _Unchecked(_Last), _Pred));
		}
	
	*/
	n = count_if(v.begin(), v.end(), mycompare06());
	cout << "n:" << n << endl;

}



int main(){


	//test01();
	//test02();
	//test03();
	//test04();
	test05();
	//test06();



	system("pause");
	return EXIT_SUCCESS;
}
