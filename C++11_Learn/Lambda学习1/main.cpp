#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//lambda 表达式语法
// [capture list] (paramters list) mutable exception-> return type{function body}
// capture list，捕获外部变量列表；
// paramters list，形参列表；
// mutable，用来说明是否可以修改捕获的外部变量；
// exception，抛出异常；
// return type，返回类型；
// function body，函数体。

int main() 
{
	vector<int> v{ 12,52,67,87,34,95,16,48 };
	//使用格式3的Lambda表达式定义sort排序规则
	sort(v.begin(), v.end(),
		[](int&a, int&b) {return a<b; });
	for (auto&elem : v) {
		cout << elem << " ";
	}
	system("pause");
	return 0;
}

// #include<iostream>
// using namespace std;
// int main() {
// 	int a = 100;
// 	auto f = [a] {cout << a << endl; };
// 	f();// f相当于一个无参的函数调用
// 	return 0;
// }


// 值捕获方式
// #include<iostream>
// using namespace std;
// int main() {
// 	int a = 100;
// 	auto f = [a] {cout << a << endl; };
// 	a = 200;// 此时改变a的值
// 	f();// 依旧输出100，而不是200
// 	return 0;
// }


// #include<iostream>
// using namespace std;
// int main() {
// 	int a = 100;
// 	auto f = [a]()mutable {cout << ++a << endl; };
// 	a = 200;// 
// 	f();
// 	return 0;
// }


// 需要注意的是，捕获的外部变量是const的，无法修改。
// 如果需要修改，需添加mutable关键字，括号也不能省略，比如说—
// #include<iostream>
// using namespace std;
// int main() {
// 	int a = 100;
// 	auto f = [a]()mutable {cout << ++a << endl; };
// 	a = 200;// 
// 	f();
// 	return 0;
// }


//引用捕获
// 顾名思义，就是捕获一个外部变量的引用，只需要在捕获的外部变量前面加上一个&即可——
// #include<iostream>
// using namespace std;
// int main() {
// 	int a = 100;
// 	auto f = [&a] {cout << a << endl; };
// 	a = 200;// 此时改变a的值
// 	f();// 输出200
// 	a = 300；
// 	f();//输出300
// 	return 0;
// }
