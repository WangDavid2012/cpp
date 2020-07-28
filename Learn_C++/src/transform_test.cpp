#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

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
