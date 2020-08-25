#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
using namespace std;


//vector��ֵ����
void test01(){
	
	vector<int> v;
	v.assign(5,1); //��ֵ����

	vector<int> v1;
	v1.assign(v.begin(),v.end()); //������V��Ԫ�ظ�ֵ��v1

	vector<int> v2;
	v2 = v1;

}

//vector��С����
void test02(){
	
	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr,arr+sizeof(arr)/sizeof(int));

	cout << "��С:" << v.size() << endl;
	cout << "����" << v.capacity() << endl;

	if (v.empty()){
		cout << "����Ϊ��!" << endl;
	}
	else{
		cout << "������Ϊ��!" << endl;
	}

}
//vector��ȡ
void test03(){

	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));


	try{
		//cout << v[100] << endl;
		cout << v.at(100) << endl;
	}
	catch (...){
		cout << "�������Խ��!" << endl;
	}

	cout << "first:" << v.front() << endl;
	cout << "last:" << v.back() << endl;
	
}

//vector�����Ĳ����ɾ��
void test04(){
	
	int arr[] = { 6, 8, 3, 9 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));
	v.insert(v.begin(),100);  //ͷ������Ԫ��

	v.push_back(100); //β�巨

	vector<int>::iterator pStart = v.begin();
	vector<int>::iterator pEnd = v.end();

	while (pStart != pEnd){
		cout << *pStart << " ";
		pStart++;
	}
	cout << endl;





	//ɾ��
	int val = v.back();
	cout << val << "��ɾ��" << endl;
	v.pop_back();

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
	

	//ָ��λ��ɾ��
	v.erase(v.begin());

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	//����ɾ��
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
