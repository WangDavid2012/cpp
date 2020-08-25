#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<deque>
using namespace std;


//deque������ʼ��
void test01(){
	deque<int> d1; //Ĭ�Ϲ��캯��
	deque<int> d2(10,5); //���������캯��
	deque<int> d3(d2.begin(),d2.end());
	deque<int> d4(d3); //��������
}

//deque��ֵ����
void test02(){
	

	deque<int> d1(10, 3);

	deque<int> d;
	//d.assign(10,5);  ��ֵ
	//d.assign(d1.begin(),d1.end());

	d = d1;  //����= ��ֵ

}

//��С����
void test03(){
	
	deque<int> d1(10, 3);
	cout << d1.size() << endl;
	if (d1.empty()){
		cout << "�գ�" << endl;
	}
	else{
		cout << "����!" << endl;
	}



	//d1.resize(5);
	//cout << d1.size() << endl;
	d1.resize(15);
}

//deque�����ɾ��
void test04(){
	
	deque<int> d;

	d.push_back(10);
	d.push_back(20);
	d.push_front(30);
	d.push_front(40);


	//��һ�ֱ�����ʽ
	for (int i = 0; i < d.size();i++){
		cout << d[i] << " ";
	}
	cout << endl;

	//�ڶ��ֱ�����ʽ
	for (int i = 0; i < d.size(); i++){
		cout << d.at(i) << " ";
	}
	cout << endl;

	//�����ַ�ʽ
	for (deque<int>::iterator it = d.begin(); it != d.end(); it++){
		cout << *it << " ";
	}
	cout << endl;


	//ɾ��Ԫ��
	/*
		while (d.size() > 0){
		cout << d.back() << "��ɾ��!" << endl;
		d.pop_back();
	}
	cout << "��С:" << d.size() << endl;
	*/


	//ͷɾ��
	while (!d.empty()){
		cout << d.front() << "��ɾ��!" << endl;
		d.pop_front();
	}


}

//deque��������
void test06(){
	
	deque<int> d;
	d.insert(d.begin(),100); //ͷ�巨
	d.insert(d.end(), 200); //β�

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
