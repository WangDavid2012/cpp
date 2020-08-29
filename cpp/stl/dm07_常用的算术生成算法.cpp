#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<numeric>
#include<vector>
#include<algorithm>
using namespace std;


//accumulate lei ji !!
void test01(){
	
	vector<int> v;
	for (int i = 0; i <= 100;i++){
		v.push_back(i);
	}

	/*
		
		template<class _InIt,
		class _Ty> inline
		_Ty accumulate(_InIt _First, _InIt _Last, _Ty _Val)
		{	// return sum of _Val and all in [_First, _Last)
		return (_STD accumulate(_First, _Last, _Val, plus<>()));
		}

	
	*/

	int n = accumulate(v.begin(),v.end(),0);
	cout << "n:" << n << endl;

}

//fill algorithm
class print{
public:
	void operator()(int v){
		cout << v << " ";
	}
};
void test02(){
	
	vector<int> v;
	v.resize(10);
	fill(v.begin(), v.end(), 100);

	cout << "size:" << v.size() << endl;
	for_each(v.begin(), v.end(), print());
	

}


int main(){

	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}
