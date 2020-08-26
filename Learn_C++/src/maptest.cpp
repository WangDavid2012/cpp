<<<<<<< HEAD
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
=======
锘�#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>      //pair 瀹氫箟鐨勬枃浠�
#include <fstream>
#include <sstream>
#include "debug.h"

using namespace std;

typedef unsigned long long u64;

void map_test()
{
	// 瀹氫箟涓�涓猰ap瀵硅薄
	map<int, string> mapStudent;

	// 绗竴绉� 鐢╥nsert鍑芥暩鎻掑叆pair
	mapStudent.insert(pair<int, string>(000, "student_zero"));
	mapStudent.insert(make_pair(10, "wangzhanbei"));

	// 绗簩绉� 鐢╥nsert鍑芥暟鎻掑叆value_type鏁版嵁
	mapStudent.insert(map<int, string>::value_type(001, "student_one"));

	// 绗笁绉� 鐢�"array"鏂瑰紡鎻掑叆
	mapStudent[123] = "student_first";
	mapStudent[456] = "student_second";
}

void readfile(string _filepath)
{
	std::ifstream _in(_filepath.c_str());  //瀹氫箟涓�涓緭鍏ユ枃浠舵祦  ifstream
	if (!_in.good()) {
		_in.close();
		return;
	}

	string line;
	while (getline(_in, line)) {   //璇诲彇_in 鏂囦欢鐨勬瘡涓�琛屾暟鎹紝鏀惧叆瀛楃line涓�
		std::istringstream iss(line);
		std::string key;
		std::string value;
		iss >> key >> value;
		//_configMap[key] = value;   //map鍙橀噺璧嬪��
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
	std::ifstream _in(_filepath.c_str());  //瀹氫箟涓�涓緭鍏ユ枃浠舵祦  ifstream
	if (!_in.good()) {
		_in.close();
		mydebug << "openfile failed!" << endl;
		return;
	}

	string line;
	while (getline(_in, line)) {   //璇诲彇_in 鏂囦欢鐨勬瘡涓�琛屾暟鎹紝鏀惧叆瀛楃line涓�
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
	* multimap瀹瑰櫒鏄笉鏀寔涓嬫爣鎿嶄綔鐨勶紝鍥犱负娌℃湁瀹為檯鎰忎箟銆�
	* 鏁呮垜浠噰鍙栬皟鐢╥nsert鍑芥暟鐨勬柟娉曠粰瀹瑰櫒璧嬪�笺��
	*/
	book.insert(make_pair("閲戝焊", "鍊氬ぉ灞犻緳璁�"));
	book.insert(make_pair("閲戝焊", "灏勯洉鑻遍泟浼�"));
	book.insert(make_pair("閲戝焊", "绗戝偛姹熸箹"));
	book.insert(make_pair("鍙ら緳", "妤氱暀棣欎紶濂�"));
	book.insert(make_pair("鍙ら緳", "闄嗗皬鍑や紶濂�"));
	book.insert(make_pair("榛勬槗", "杈硅崚浼犺"));

	/*
	* 浣跨敤equal_range鍑芥暟鑾峰彇鎸囧悜閿�煎尮閰嶅厓绱犱笅鐣屽拰涓婄晫鐨勮凯浠ｅ櫒
	*/
	typedef multimap<string, string>::iterator bookit;
	pair<bookit, bookit> p = book.equal_range("鍙ら緳");

	/*
	* 鎵撳嵃妫�绱㈢粨鏋�
	*/
	cout << "浣滆��: " << p.first->first << endl << "涔﹀悕:" << endl;
	while (p.first != p.second) {
		cout << p.first->second << " ";
		p.first++;
	}
	cout << endl;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
