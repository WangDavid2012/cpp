#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>      //pair 定义的文件



using namespace std;


void map_test()
{
	// 定义一个map对象
	map<int, string> mapStudent;

	// 第一种 用insert函數插入pair
	mapStudent.insert(pair<int, string>(000, "student_zero"));
	mapStudent.insert(make_pair(10, "wangzhanbei"));

	// 第二种 用insert函数插入value_type数据
	mapStudent.insert(map<int, string>::value_type(001, "student_one"));

	// 第三种 用"array"方式插入
	mapStudent[123] = "student_first";
	mapStudent[456] = "student_second";

}