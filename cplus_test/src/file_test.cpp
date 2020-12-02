#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "debug.h"

using std::map;
using std::set;
using std::string;
using namespace std;

class Configuration
{
public:
	Configuration(const string& filepath);
	void init();
	map<string, string> & getConfigMap();
	void debug();
private:
	string				_filepath;          //文件路径
	map<string, string>	_configMap;         //定义了一个map变量
};

//构造函数，_filepathbi变量初始赋值
//参数赋值，调用init()函数
Configuration::Configuration(const string& filepath) :_filepath(filepath) {
	init();
	mydebug << "Configuration init" << endl;
}

void Configuration::debug()
{
	//for (auto & ele : _configMap)
	//	std::cout << ele.first << '\t' << ele.second << std::endl;
}

//程序配置初始化
//实现的功能：
// 从配置文件中，读取内容，然后存放在_configMap变量中
void Configuration::init()
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
		_configMap[key] = value;   //map变量赋值
	}
	_in.close();
}
//对外提供一个接口，获取_configMap变量
map<string, string> & Configuration::getConfigMap()
{
	return _configMap;
}

/**************************************************************
王占备---20200714
需要使用到一个DeviceManage类来管理deviceHandle信息。
map<string,id> m_deviceInfoMap;

可能需要的类型 map<string,array>
	string类型ID，字符串32byre，hash(IP+程序路径)
	array数组存放devicehandle（64bit）

	可以使用multimap类型 <string,u64>
实现的功能：
	一、开机启动的时候，从文件中读取deviceHandle信息，然后将这些信息放到
		m_deviceInfoMap中，让后下发置零，删除，使 m_deviceInfoMap清0
	二、OpenDevice时，向文件中写入信息，m_deviceInfoMap 是否需要变化？
	三、CloseDevice时，从文件中删除信息，m_deviceInfoMap 是否需要变化？


***************************************************************/

void  ofstream_test()
{
	using namespace std;
	ofstream x("basic_ostream_seekp.txt");
	streamoff i = x.tellp();
	cout << i << endl;
	x << "testing";
	i = x.tellp();
	cout << i << endl;
	x.seekp(2);             // Put char in third char position in file
	x << " ";

	x.seekp(2, ios::end);   // Put char two after end of file
	x << "z";
	x.close();
}
