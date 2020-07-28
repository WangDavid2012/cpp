#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>      //pair 定义的文件
#include <fstream>
#include <sstream>
#include "debug.h"

using namespace std;

typedef unsigned long long u64;

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

void readfile(string _filepath)
{
	std::ifstream _in(_filepath.c_str());  //定义一个输入文件流  ifstream
	if (!_in.good()) {
		_in.close();
		return;
	}

	string line;
	while (getline(_in, line)) {   //读取_in 文件的每一行数据，放入字符line中
		std::istringstream iss(line);
		std::string key;
		std::string value;
		iss >> key >> value;
		//_configMap[key] = value;   //map变量赋值
	}
	_in.close();
}

void multimap_test()
{
	ofstream ofs("D:\\logSDF\\deviceHandle.conf");

	multimap<string, u64> m_deviceMultimap;

	m_deviceMultimap.insert(pair<string, u64>("zero", 9911111111111111));
	m_deviceMultimap.insert(make_pair("zero", 9922222222222222));
	m_deviceMultimap.insert(make_pair("zero", 9933222222222222));
	m_deviceMultimap.insert(make_pair("wang", 9933222288222));
	m_deviceMultimap.insert(make_pair("zhan", 9933222288222));

	//auto tmp = m_deviceMultimap.begin();

	if (!ofs.bad())
	{
		for (multimap<string, u64>::iterator it = m_deviceMultimap.begin(); it != m_deviceMultimap.end(); it++) {
			cout << "key:" << it->first << " value:" << it->second << endl;
			ofs << it->first << ":" << it->second << endl;
		}
		ofs.close();
	}
	if (!ofs.bad())
	{
		ofs.seekp(10, ios::ate);
		ofs << "wang" << ":" << "123456789" << endl;
		ofs.close();
	}

	cout << endl;
}

void filefunction_test()
{
	multimap<string, u64> tmpDeviceMultimap;
	string _filepath("D:\\logSDF\\deviceHandle.conf");
	mydebug << "filepath:" << _filepath << endl;
	std::ifstream _in(_filepath.c_str());  //定义一个输入文件流  ifstream
	if (!_in.good()) {
		_in.close();
		mydebug << "openfile failed!" << endl;
		return;
	}

	string line;
	while (getline(_in, line)) {   //读取_in 文件的每一行数据，放入字符line中
		std::istringstream iss(line);
		std::string key;
		u64 value;
		iss >> key >> value;

		tmpDeviceMultimap.insert(make_pair(key, value));
	}
	_in.close();

	cout << "bef del " << endl;
	auto it = tmpDeviceMultimap.begin();
	for (; it != tmpDeviceMultimap.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	cout << endl;

	string delkey("wang");
	multimap<string, u64> delMultimap;
	multimap<string, u64>::iterator iter = tmpDeviceMultimap.find(delkey);

	if (iter != tmpDeviceMultimap.end())
		tmpDeviceMultimap.erase(delkey);

	cout << "after del " << endl;

	auto it1 = tmpDeviceMultimap.begin();
	for (; it1 != tmpDeviceMultimap.end(); it1++)
	{
		cout << it1->first << " " << it1->second << endl;
	}
	cout << endl;
}

int file_test2()
{
	multimap<string, string> authors;
	string author, work, searchItem;

	do {
		cout << "Enter author name(Ctrl+Z to end):" << endl;
		cin >> author;
		if (!cin)
			break;
		cout << "Enter author's works(Ctrl+Z to end):" << endl;
		while (cin >> work)
			authors.insert(make_pair(author, work));
		cin.clear();
	} while (cin);
	cin.clear();

	cout << "Who is the author that you want erase:" << endl;
	cin >> searchItem;
	multimap<string, string>::iterator iter = authors.find(searchItem);
	if (iter != authors.end())
		authors.erase(searchItem);
	else
		cout << "Can not find this author!" << endl;
	cout << "author\t\twork:" << endl;
	for (iter = authors.begin(); iter != authors.end(); ++iter)
		cout << iter->first << "\t\t" << iter->second << endl;
	return 0;
}

void multimap_test1()
{
	multimap<string, string> book;

	/*
	* multimap容器是不支持下标操作的，因为没有实际意义。
	* 故我们采取调用insert函数的方法给容器赋值。
	*/
	book.insert(make_pair("金庸", "倚天屠龙记"));
	book.insert(make_pair("金庸", "射雕英雄传"));
	book.insert(make_pair("金庸", "笑傲江湖"));
	book.insert(make_pair("古龙", "楚留香传奇"));
	book.insert(make_pair("古龙", "陆小凤传奇"));
	book.insert(make_pair("黄易", "边荒传说"));

	/*
	* 使用equal_range函数获取指向键值匹配元素下界和上界的迭代器
	*/
	typedef multimap<string, string>::iterator bookit;
	pair<bookit, bookit> p = book.equal_range("古龙");

	/*
	* 打印检索结果
	*/
	cout << "作者: " << p.first->first << endl << "书名:" << endl;
	while (p.first != p.second) {
		cout << p.first->second << " ";
		p.first++;
	}
	cout << endl;
}
