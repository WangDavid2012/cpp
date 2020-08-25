#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main(){

	vector<int> v1, v2,v3;
	for (int i = 0; i < 10;i++){
		v1.push_back(i);
	}

	for (int i = 5; i < 15;i++){
		v2.push_back(i);
	}	


	v3.resize(v1.size()+v2.size());
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for_each(v3.begin(), v3.end(), [](int v)->void{cout << v << endl; });




	system("pause");
	return EXIT_SUCCESS;
}
