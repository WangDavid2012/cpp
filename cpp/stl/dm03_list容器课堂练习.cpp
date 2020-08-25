#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<list>
#include<string>
using namespace std;


//listf������ʼ��
void list_test01()
{
    list<int> mylist; 			//Ĭ�Ϲ���
    list<int> mylist2(10, 5); 	//�������Ĺ��캯��,ʹ��10��5���г�ʼ��
    list<int> mylist3(mylist2.begin(), mylist2.end()); //�������Ĺ��캯��
    list<int> mylist4(mylist3); //��������
}


void print(list<int>& mylist)
{

    for (list<int>::iterator it = mylist.begin(); it != mylist.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

}

//list��������ɾ��
void list_test02()
{

    list<int> mylist;
    mylist.push_back(10);  //β�
    mylist.push_back(20);
    mylist.push_front(30); //ͷ�巨
    mylist.push_front(40);
    mylist.insert(mylist.begin(),50);
    mylist.push_front(40);

    print(mylist);

    //ɾ��
    mylist.remove(40);      //ɾ��ƥ�������ֵ
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

//list��С�͸�ֵ����
void list_test03()
{

    list<int> mylist;
    cout << "size:" << mylist.size() << endl;
    for (int i = 0; i < 10; i++) {
        mylist.push_back(i);
    }
    cout << "size:" << mylist.size() << endl;

    if (mylist.empty()) {
        cout << "��!" << endl;
    } else {
        cout << "����!" << endl;
    }

    //list��ֵ���� 
	//mylist2.assign(10,10);  //��ֵ10��10
    list<int> mylist2;
    mylist2.assign(mylist.begin(), mylist.end());
    print(mylist2);


    mylist2.assign(5,10);
    print(mylist2);

    list<int> mylist3;
    mylist3 = mylist2; //operatror= ��ֵ

    ::print(mylist);
    ::print(mylist3);
    mylist.swap(mylist3);
    cout << "------------" << endl;
    ::print(mylist);
    ::print(mylist3);

    cout << mylist3.front() << endl;
    cout << mylist3.back() << endl;

    //reverse ��ת������Ԫ�� 1 3 5----> 5 3 1
    mylist3.reverse();
    print(mylist3);


}

bool mycompare(int v1,int v2)
{
    return v1 > v2;
}

//list��������
void list_test04()
{

    list<int> mylist;
    mylist.push_back(2);
    mylist.push_back(8);
    mylist.push_back(5);
    mylist.push_back(9);

    print(mylist);
    mylist.sort(); //Ĭ�ϴ�С����
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
