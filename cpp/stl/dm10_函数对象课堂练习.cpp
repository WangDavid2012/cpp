#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void print(){
	cout << "hello world" << endl;
}

class myprint{
public:
	void operator()(){
		cout << "hello world" << endl;
	}
};

//�����������ͨ�����Ա�
void test01(){

	print();
	myprint myp;
	myp();

}

void print02(int index){
	cout << "hello world :" << index  << endl;
}

class myprint02{
public:
	void operator()(int index){
		cout << "hello world :" << index << endl;
	}
};

void test02(){

	print02(10);
	myprint02 myp02;
	myp02(10);

}

//�������󳬳�����ͨ�����ĸ�����Ա��溯������״̬
//ͳ�ƺ������ô���
int g_count = 0;
void print03(){
	g_count++;
}

struct myprint03{
	myprint03() :count(0){}
	void operator()(){
		count++;
	}
	int count;
};


void test03(){

	print03();
	print03();
	cout << g_count << endl;
	
	myprint03 myp03;
	myp03();
	myp03();
	myp03();

	cout << myp03.count << endl;

}
//���������ֳ�Ϊ�º���
//�������������� ������ֵ
class myprint04{
public:
	myprint04() :count(0){}
	void operator()(int v){
		count++;
		cout << v << " ";
	}
	int count;
};
void test04(){
	
	vector<int> v;
	for (int i = 0; i < 10;i++){
		v.push_back(i);
	}
	myprint04 myp04;
	myprint04 myp05 = for_each(v.begin(), v.end(), myp04); //��������������
	cout << "count:" << myp04.count << endl; cout << endl;
	cout << "count:" << myp05.count << endl; cout << endl;
}




int main(){

	test01();
	test02();
	test03();
	test04();


	system("pause");
	return EXIT_SUCCESS;
}
