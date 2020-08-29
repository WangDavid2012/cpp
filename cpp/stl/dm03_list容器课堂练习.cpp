#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<list>
#include<string>
using namespace std;


//listf容器初始化
void list_test01()
{
    list<int> mylist; 			//默认构造
    list<int> mylist2(10, 5); 	//带参数的构造函数,使用10个5进行初始化
    list<int> mylist3(mylist2.begin(), mylist2.end()); //带参数的构造函数
    list<int> mylist4(mylist3); //拷贝构造
}


void print(list<int>& mylist)
{

    for (list<int>::iterator it = mylist.begin(); it != mylist.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

}

//list容器插入删除
void list_test02()
{

    list<int> mylist;
    mylist.push_back(10);  //尾差法
    mylist.push_back(20);
    mylist.push_front(30); //头插法
    mylist.push_front(40);
    mylist.insert(mylist.begin(),50);
    mylist.push_front(40);

    print(mylist);

    //删除
    mylist.remove(40);      //删除匹配的所有值
    print(mylist);

    /*
    	mylist.pop_back();
    mylist.pop_front();
    mylist.erase(mylist.begin());
    print(mylist);
    mylist.erase(mylist.begin(), mylist.end()); // mylist.clear()
    cout << "size:" << mylist.size() << endl;
    */

}

//list大小和赋值操作
void list_test03()
{

    list<int> mylist;
    cout << "size:" << mylist.size() << endl;
    for (int i = 0; i < 10; i++) {
        mylist.push_back(i);
    }
    cout << "size:" << mylist.size() << endl;

    if (mylist.empty()) {
        cout << "空!" << endl;
    } else {
        cout << "不空!" << endl;
    }

    //list赋值操作 
	//mylist2.assign(10,10);  //赋值10个10
    list<int> mylist2;
    mylist2.assign(mylist.begin(), mylist.end());
    print(mylist2);


    mylist2.assign(5,10);
    print(mylist2);

    list<int> mylist3;
    mylist3 = mylist2; //operatror= 赋值

    ::print(mylist);
    ::print(mylist3);
    mylist.swap(mylist3);
    cout << "------------" << endl;
    ::print(mylist);
    ::print(mylist3);

    cout << mylist3.front() << endl;
    cout << mylist3.back() << endl;

    //reverse 反转容器的元素 1 3 5----> 5 3 1
    mylist3.reverse();
    print(mylist3);


}

bool mycompare(int v1,int v2)
{
    return v1 > v2;
}

//list容器排序
void list_test04()
{

    list<int> mylist;
    mylist.push_back(2);
    mylist.push_back(8);
    mylist.push_back(5);
    mylist.push_back(9);

    print(mylist);
    mylist.sort(); //默认从小到大
    print(mylist);
    mylist.sort(mycompare);
    print(mylist);

}

class Teacher
{
public:
    Teacher(string name, int age) :name(name), age(age) {}
    string name;
    int age;
};

bool compare2(Teacher t1, Teacher t2)
{
    if (t1.age > t2.age) {
        return true;
    } else {
        return false;
    }

    //return t1.age > t2.age;
}
void list_test05()
{

    list<Teacher> mylist;
    Teacher t1("aaa", 10), t2("bbb", 5), t3("ccc", 15);

    mylist.push_back(t1);
    mylist.push_back(t2);
    mylist.push_back(t3);

    for (list<Teacher>::iterator it = mylist.begin(); it != mylist.end(); it++) {
        cout << it->name << " " << it->age << endl;
    }
    cout << endl;

    mylist.sort(compare2);

    for (list<Teacher>::iterator it = mylist.begin(); it != mylist.end(); it++) {
        cout << it->name << " " << it->age << endl;
    }
    cout << endl;

}

void list_test()
{
	list_test01();
	list_test02();
	list_test03();
	list_test04();
	list_test05();
}
