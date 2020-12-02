#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
using std::vector;

char op(char ch)
{
	if (ch >= 'A'&&ch <= 'Z')
		return ch + 32;
	else
		return ch;
}

int transform_test()
{
	string first, second;
	cin >> first;
	second.resize(first.size());
	transform(first.begin(), first.end(), second.begin(), op);
	cout << second << endl;
	return 0;
}
int vector_test()
{
// 	std::vector array_test;
// 	array_test.push_back();
	return 0;
}




