#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<functional>  //预定义函数对象
#include<set>
#include<stdlib.h>
#include<time.h>

using namespace std;

//初始化
void test01(){
	set<int> myset; //默认构造
	set<int> myset2(myset); //拷贝构造
}

void printSet(set<int>& myset){
	for (set<int>::iterator it = myset.begin(); it != myset.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
}
//set容器插入和删除
void test02(){
	
	set<int> myset; //默认从小到大排序
	myset.insert(4);
	myset.insert(2);
	myset.insert(1);
	myset.insert(5);
	myset.insert(2);

	printSet(myset);

	//删除
	myset.erase(myset.begin()); //删除第一个元素
	myset.erase(2); //根据元素值删除
	printSet(myset);
	myset.erase(myset.begin(),myset.end()); // myset.clear()
	cout << "size:" << myset.size() << endl;
}

template<class T>
class mycompare03{
public:
	bool operator()(T v1,T v2) const{
		return v1 > v2;
	}
};

//set容器查找
void test03(){

	//函数对象
	//mycompare03 mycom;
	//mycom(10); //函数对象 仿函数
	
	set<int, mycompare03<int>> myset; //默认从小到大排序
	myset.insert(4);
	myset.insert(2);
	myset.insert(1);
	myset.insert(5);

	for (set<int, greater<int>>::iterator it = myset.begin(); it != myset.end();it++){
		cout << *it << " ";
	}
	cout << endl;

	/*

	set<int>::iterator pos =  myset.find(20); //返回值为2的元素所在的位置
	if (pos == myset.end()){
		cout << "没有查找到!" << endl;
	}
	else{
		cout << "查找到:" << *pos << endl;
	}
	
	*/
}

class Teacher{
public:
	Teacher(int id,int age) :id(id), age(age){}
	int id;
	int age;
};

class mycompare04{
public:
	bool operator()(Teacher t1, Teacher t2){
		return t1.id > t2.id;
	}
};
void test04(){

	set<Teacher, mycompare04> myset;
	Teacher t1(1, 2), t2(3, 4), t3(5, 6);

	myset.insert(t1);
	myset.insert(t2);
	myset.insert(t3);

	for (set<Teacher, mycompare04>::iterator it = myset.begin(); it != myset.end();it ++){
		cout << it->id << " " << it->age << endl;
	}
	cout << endl;

	/*
	set<Teacher, mycompare04>::iterator pos =  myset.find(t2);
	if (pos == myset.end()){
		cout << "没有查找到!" << endl;
	}
	else{
		cout << "查找到:" << pos->id << ":" << pos->age << endl;
	}
	*/


	set<Teacher, mycompare04>::iterator pos = myset.find(Teacher(3, 4));
	if (pos == myset.end()){
		cout << "没有查找到!" << endl;
	}
	else{
		cout << "查找到:" << pos->id << ":" << pos->age << endl;
	}

}


void test05(){

	set<int> myset;
	myset.insert(10);
	myset.insert(5);
	myset.insert(1);
	myset.insert(8);

	set<int>::iterator pos = myset.lower_bound(5);  //返回大于等于5 迭代器
	if (pos == myset.end()){
		cout << "没有找到!" << endl;
	}
	else{
		cout << "找到：" << *pos << endl;
	}

	pos = myset.upper_bound(5);
	if (pos == myset.end()){
		cout << "没有找到!" << endl;
	}
	else{
		cout << "找到：" << *pos << endl;
	}

	pair<set<int>::iterator, set<int>::iterator> pos2 =  myset.equal_range(5);
	if (pos2.first == myset.end()){
		cout << "meiyouzhaodao!" << endl;
	}
	else{
		cout << "zhaodao!" << *(pos2.first) << endl;
	}

	if (pos2.second == myset.end()){
		cout << "meiyouzhaodao!" << endl;
	}
	else{
		cout << "zhaodao!" << *(pos2.second) << endl;
	}

}

int main(){


	//test02();
	//test03();
	//test04();
	test05();

	system("pause");
	return EXIT_SUCCESS;
}
