#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//
void test01(){
	//容器
	vector<int> v; //创建一个容器 动态数组 指定这个容器中放的数据类型 都是Int
	v.push_back(10); //通过vector通过成员方法 向容器的尾部添加元素
	v.push_back(4);
	v.push_back(5);
	v.push_back(4);

	//迭代器
	vector<int>::iterator pStart = v.begin(); //拿到了指向第一个元素的迭代器
	vector<int>::iterator pEnd = v.end(); //返回指向最后一个元素下一个位置

	while (pStart != pEnd){
		cout << *pStart << " ";
		pStart++;
	}
	cout << endl;

	//count统计容器中某个元素的个数
	int n = count(v.begin(),v.end(),4);
	cout << "n:" << n << endl;

}

class Teacher{
public:
	Teacher(int id, int age) :ID(id), age(age){}
	int ID;
	int age;
};

void test02(){
	
	vector<Teacher> v; //创建一个容器 指定里面放Teacher类型的数据
	Teacher t1(1, 2), t2(3, 4), t3(5, 6);

	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);


	vector<Teacher>::iterator pStart = v.begin(); //拿到指向第一元素的迭代器
	vector<Teacher>::iterator pEnd = v.end();//指向最后一个元素下一个位置

	while (pStart != pEnd){
		Teacher t = *pStart;
		cout << "ID：" << t.ID << " AGE:" << t.age << endl;
		pStart++;
	}

}

//容器放类对象指针
void test03(){
	
	vector<Teacher*> v; //容器中放Teacher类型指针
	Teacher t1(1, 2), t2(3, 4), t3(5, 6);

	Teacher* p1 = &t1;
	Teacher* p2 = &t2;
	Teacher* p3 = &t3;

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);

	vector<Teacher*>::iterator pStart = v.begin(); //指向第一个元素的迭代器
	vector<Teacher*>::iterator pEnd = v.end();

	while (pStart != pEnd){
		Teacher* ttemp = *pStart;
		cout << ttemp->ID << " " << ttemp->age << endl;
		pStart++;
	}
	cout << endl;

}


int main(){

	//test01();
	//test02();
	test03();
	

	system("pause");
	return EXIT_SUCCESS;
}
