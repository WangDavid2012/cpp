#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<deque>
using namespace std;


//deque容器初始化
void test01(){
	deque<int> d1; //默认构造函数
	deque<int> d2(10,5); //带参数构造函数
	deque<int> d3(d2.begin(),d2.end());
	deque<int> d4(d3); //拷贝构造
}

//deque赋值操作
void test02(){
	

	deque<int> d1(10, 3);

	deque<int> d;
	//d.assign(10,5);  赋值
	//d.assign(d1.begin(),d1.end());

	d = d1;  //重载= 赋值

}

//大小操作
void test03(){
	
	deque<int> d1(10, 3);
	cout << d1.size() << endl;
	if (d1.empty()){
		cout << "空！" << endl;
	}
	else{
		cout << "不空!" << endl;
	}



	//d1.resize(5);
	//cout << d1.size() << endl;
	d1.resize(15);
}

//deque插入和删除
void test04(){
	
	deque<int> d;

	d.push_back(10);
	d.push_back(20);
	d.push_front(30);
	d.push_front(40);


	//第一种遍历方式
	for (int i = 0; i < d.size();i++){
		cout << d[i] << " ";
	}
	cout << endl;

	//第二种遍历方式
	for (int i = 0; i < d.size(); i++){
		cout << d.at(i) << " ";
	}
	cout << endl;

	//第三种方式
	for (deque<int>::iterator it = d.begin(); it != d.end(); it++){
		cout << *it << " ";
	}
	cout << endl;


	//删除元素
	/*
		while (d.size() > 0){
		cout << d.back() << "被删除!" << endl;
		d.pop_back();
	}
	cout << "大小:" << d.size() << endl;
	*/


	//头删除
	while (!d.empty()){
		cout << d.front() << "被删除!" << endl;
		d.pop_front();
	}


}

//deque容器插入
void test06(){
	
	deque<int> d;
	d.insert(d.begin(),100); //头插法
	d.insert(d.end(), 200); //尾差法

	for (deque<int>::iterator it = d.begin(); it != d.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
}


int main(){


	//test03();
	//test04();
	test06();

	system("pause");
	return EXIT_SUCCESS;
}
