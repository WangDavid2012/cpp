#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
using namespace std;


//vector初始化
void test01(){
	
	vector<int> v; //默认构造 空的vector容器
	vector<int> v2(10,5); //带参数构造函数
	vector<int> v3(v2.begin(), v2.end());
	vector<int> v4(v3); //拷贝构造

	int arr[] = {2,3,6,7};
	vector<int> v5(arr,arr+ sizeof(arr)/sizeof(int));

	for (int i = 0; i < v4.size();i++){
		cout << v4[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < v5.size(); i++){
		cout << v5[i] << " ";
	}
	cout << endl;

}

int main(){

	test01();
	

	system("pause");
	return EXIT_SUCCESS;
}
