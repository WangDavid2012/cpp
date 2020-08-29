#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//如果你写的函数对象接受一个参数，那么就叫 一元函数对象
//如果你写的函数对象接受两个参数，那么叫 二元函数对象

//如果你写的函数对象或者普通函数接受一个参数，并且返回值是Bool，叫一元谓词
//如果你写的函数对象或者普通函数接受二个参数，并且返回值是Bool，叫二元谓词



//一元函数对象 应用举例 : for_each
class print{
public:
	void operator()(int v){
		cout << v << " ";
	}
};

void print2(int v){
	cout << v << " ";
}
void test01(){
	
	vector<int> v;
	for (int i = 0; i < 10;i++){
		v.push_back(i);
	}

	//print p;
	//for_each(v.begin(), v.end(), print());  //函数对象
	for_each(v.begin(), v.end(), print2); //普通函数
	cout << endl;
}


//一元谓词 应用举例：find_if
class mycompare{
public:
	bool operator()(int v){
		if (v > 7){
			return true;
		}
		else{
			return false;
		}
	}
};
void test02(){
	
	vector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
	}


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

	vector<int>::iterator pos = find_if(v.begin(), v.end(), mycompare()); //匿名函数对象
	if(pos == v.end()){
		cout << "没找到" << endl;
	}
	else{
		cout << "找到:" << *pos << endl;
	}

}

//二元函数对象 应用举例 : transform
class myplus{
public:
	int operator()(int v1,int v2){
		return v1 + v2;
	}

};
void test03(){
	
	vector<int> v1,v2,v3;
	for (int i = 0; i < 10; i++){
		v1.push_back(i);
		v2.push_back(i + 1);
	}


	/*
		
		template<class _InIt1,
		class _InIt2,
		class _OutIt,
		class _Fn2> inline
		_OutIt transform(_InIt1 _First1, _InIt1 _Last1,
		_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
		{	// transform [_First1, _Last1) and [_First2, ...) with _Func
		_DEBUG_RANGE(_First1, _Last1);
		_DEBUG_POINTER(_Dest);
		_DEBUG_POINTER(_Func);
		if (_First1 != _Last1)
		return (_Transform2(_Unchecked(_First1), _Unchecked(_Last1),
		_First2, _Dest, _Func,
		_Is_checked(_Dest)));
		return (_Dest);
		}


		template<class _InIt1,
		class _InIt2,
		class _OutIt,
		class _Fn2> inline
		_OutIt _Transform(_InIt1 _First1, _InIt1 _Last1,
		_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
		{	// transform [_First1, _Last1) and [_First2, ...) with _Func
		for (; _First1 != _Last1; ++_First1, ++_First2, ++_Dest)
		*_Dest = _Func(*_First1, *_First2);
		return (_Dest);
		}
	
	*/

	v3.resize(v1.size());

	for_each(v1.begin(), v1.end(), print2); //普通函数
	cout << endl;
	for_each(v2.begin(), v2.end(), print2); //普通函数
	cout << endl;
	for_each(v3.begin(), v3.end(), print2); //普通函数
	cout << endl;

	
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), myplus()); //匿名函数对象

	cout << "------------------------------" << endl;

	for_each(v1.begin(), v1.end(), print2); //普通函数
	cout << endl;
	for_each(v2.begin(), v2.end(), print2); //普通函数
	cout << endl;
	for_each(v3.begin(), v3.end(), print2); //普通函数
	cout << endl;

}
//二元谓词 应用举例 : sort

class mycompare04{
public:
	bool operator()(int v1,int v2){
		return v1 > v2; //从大到小
	}
};
void test04(){

	vector<int> v;
	v.push_back(5);
	v.push_back(2);
	v.push_back(7);
	v.push_back(9);


	/*
	
	template<class _RanIt,
	class _Pr> inline
	void sort(_RanIt _First, _RanIt _Last, _Pr _Pred)
	{	// order [_First, _Last), using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_Sort(_Unchecked(_First), _Unchecked(_Last), _Last - _First, _Pred);
	}


	*/
	for_each(v.begin(), v.end(), print2); //普通函数
	cout << endl;
	sort(v.begin(), v.end(), mycompare04());
	for_each(v.begin(), v.end(), print2); //普通函数
	cout << endl;
	
}


int main(){


	//test01();
	//test02();
	//test03();
	test04();

	system("pause");
	return EXIT_SUCCESS;
}
