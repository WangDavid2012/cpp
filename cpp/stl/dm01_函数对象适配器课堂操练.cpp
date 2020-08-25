#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;


//bind1st bind2nd

//第一步 需要让你自定义函数对象去继承父类  binary_function  unary_function
class print : public binary_function<int,int,void>{
public:
	void operator()(int v ,int v2) const{
		cout << "v:" << v << "v2:" << v2 << endl;

		//if (v > v2){
		//	cout << v << " ";
		//}
	}
};

void test01(){
	

	vector<int> v;
	for (int i = 0; i < 10;i++){
		v.push_back(i);
	}

	print p;
	for_each(v.begin(), v.end(), bind1st(p,5));
	cout << endl;


	//bind1sst bind2nd绑定适配器  调用绑定适配器，统统编程一元函数对象
}

//not1 not2 取反适配器
struct mycompare02 : public unary_function<int,bool> {
	bool operator()(int v) const{
		return v > 5;
	}
};
void test02(){
	
	vector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
	}

	mycompare02 myp02;
	vector<int>::iterator pos = find_if(v.begin(), v.end(), not1(myp02));
	if (pos != v.end()){
		cout << "找到:" << *pos << endl;
	}
	else{
		cout << "没有找到!" << endl;
	}


	//sort算法
	greater<int> mygreater;
	sort(v.begin(), v.end(), mygreater);

	for (vector<int>::iterator it = v.begin(); it != v.end();it++){
		cout << *it << " ";
	}
	cout << endl;

	sort(v.begin(), v.end(), not2(mygreater));

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
}

//ptr_func  普通函数适配器
/*
struct print03{
void operator()(int v){
cout << v << " ";
}
};
*/

void print03(int v, int v2){
	if(v > v2){
		cout << v << " ";
	}
}

//对普通函数进行绑定参数
// 1 需要将普通函数转化为函数对象 ptr_fun
// 2 可以用Bind适配器了
void test03(){
	
	vector<int> v;
	for (int i = 0; i < 10; i++){
		v.push_back(i);
	}

	
	for_each(v.begin(), v.end(), bind2nd(ptr_fun(print03),5));

}

//mem_fun mem_fun_ref
class Teacher{
public:
	Teacher(int id, int age) :id(id), age(age){}
	int id;
	int age;

	void print(){
		cout << "成员方法:" << this->id << " " << this->age << endl;
	}
};

class print04{
public:
	void operator()(Teacher t){
		cout << t.id << " " << t.age << endl;
	}
};
void test04(){
	
	vector<Teacher> v;

	Teacher t1(1, 2), t2(3, 4), t3(5, 6);

	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);

	//函数对象方式
	//for_each(v.begin(), v.end(), print04());

	//希望用类的成员方法来打印类对象
	for_each(v.begin(), v.end(), mem_fun_ref(&Teacher::print));

	//如果你的容器中放的是类对象实体 用mem_fun_ref
	//如果你的容器中放的是类对象指针 用mem_fun

	vector<Teacher*> v2;
	Teacher* tt1 = new Teacher(1,2);
	Teacher* tt2 = new Teacher(3, 4);
	Teacher* tt3 = new Teacher(5, 6);

	v2.push_back(tt1);
	v2.push_back(tt2);
	v2.push_back(tt3);

	for_each(v2.begin(), v2.end(), mem_fun(&Teacher::print));
}

int main(){

	//test01();
	//test02();

	//test03();
	test04();


	system("pause");
	return EXIT_SUCCESS;
}
