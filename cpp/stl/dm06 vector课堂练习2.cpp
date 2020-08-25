#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
using namespace std;


//vector赋值操作
void test01(){
	
	vector<int> v;
	v.assign(5,1); //赋值方法

	vector<int> v1;
	v1.assign(v.begin(),v.end()); //将容器V中元素赋值给v1

	vector<int> v2;
	v2 = v1;

}

//vector大小操作
void test02(){
	
	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr,arr+sizeof(arr)/sizeof(int));

	cout << "大小:" << v.size() << endl;
	cout << "容量" << v.capacity() << endl;

	if (v.empty()){
		cout << "容器为空!" << endl;
	}
	else{
		cout << "容器不为空!" << endl;
	}

}
//vector存取
void test03(){

	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));


	try{
		//cout << v[100] << endl;
		cout << v.at(100) << endl;
	}
	catch (...){
		cout << "数组访问越界!" << endl;
	}

	cout << "first:" << v.front() << endl;
	cout << "last:" << v.back() << endl;
	
}

//vector容器的插入和删除
void test04(){
	
	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	v.insert(v.begin(),100);  //头部插入元素

	v.push_back(100); //尾插法

	vector<int>::iterator pStart = v.begin();
	vector<int>::iterator pEnd = v.end();

	while (pStart != pEnd){
		cout << *pStart << " ";
		pStart++;
	}
	cout << endl;





	//删除
	int val = v.back();
	cout << val << "被删除" << endl;
	v.pop_back();

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	

	//指定位置删除
	v.erase(v.begin());

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	//区间删除
	//v.erase(v.begin(),v.end());
	v.clear();
	cout << "size:" << v.size() << endl;

}

int main(){


	//test02();
	//test03();
	test04();


	system("pause");
	return EXIT_SUCCESS;
}
