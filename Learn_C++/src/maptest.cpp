#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>      //pair ������ļ�



using namespace std;


void map_test()
{
	// ����һ��map����
	map<int, string> mapStudent;

	// ��һ�� ��insert��������pair
	mapStudent.insert(pair<int, string>(000, "student_zero"));
	mapStudent.insert(make_pair(10, "wangzhanbei"));

	// �ڶ��� ��insert��������value_type����
	mapStudent.insert(map<int, string>::value_type(001, "student_one"));

	// ������ ��"array"��ʽ����
	mapStudent[123] = "student_first";
	mapStudent[456] = "student_second";

}