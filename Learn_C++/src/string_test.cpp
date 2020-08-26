<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int string_test()
{
	string str1 = "hello";
	int length = str1.length();

	char data[8] = { 0x68,0x04, 0x43,0x00,0x00,0x00 };
	cout << hex << (unsigned int)(unsigned char)data << endl;

	//长度是5，不包括\0字符
	printf("调用str.length()函数获取字符串长度：%d\n\n", length);
	return 0;
}
int string_test1()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string str4 = str1 + str2;
	string str5 = str3 + str2;
	cout << "字符串str1+str2连接结果：" << str4 << endl;
	cout << endl;
	cout << "字符串str3+str2连接结果：" << str5 << endl;
	return 0;
}

void string_test2()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string::const_iterator it = str1.begin();
	cout << *it << endl;


	//end是指向最后一个字符后面的元素，而且不能输出,所以cout << *it << endl;这样输出会报错
	it = str1.end();
	it--;
	cout << *it << endl;

}

int string_test3()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	//string 转化成unsigned char
	string str = "csdn";
	unsigned char dst[128] = "";
	strcpy((char*)dst, str.c_str());

	cout << "dst:" << hex << dst[0] << endl;

	char *d = new char[20];   //因为下一句那里不是直接赋值，所以指针类型可以不用const char *
	strcpy(d, str3.c_str());  //c_str 取得C风格的const char* 字符串
	cout << "d:" << d << endl;

	return 0;
}





//char* 和 string转换
void test01() {

	//string类型转换为char*字符串
	string s = "abc";
	const char* str = s.c_str();

	//char*类型字符串转换为string类型字符串
	char* str2 = "acbd";
	string s2(str2);

}

//string初始化
void test02() {

	string s; //默认构造
	string s2 = "acbd";
	string s3(s2);

	string s4(10, 'c');


	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;

}

//string容器字符串赋值和存取
void test03() {


	//string容器赋值
	string s;
	s = "abcd";

	string s2;
	s2.assign("pppp");


	//string容器存取
	string s3 = "abcdefg";
	for (int i = 0; i < s3.size(); i++) {
		cout << s3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s3.size(); i++) {
		cout << s3.at(i) << " ";
	}
	cout << endl;


	//【】访问方式访问越界时候，不会抛异常，直接挂掉
	//at会抛出异常
	try {
		//cout << s3[100] << endl;
		cout << s3.at(100) << endl;
	}
	catch (...) {
		cout << "访问越界!" << endl;
	}


}

//string容器拼接操作
void test04() {

	string s1 = "aaa";
	string s2 = "bbb";

	//string s3 = s1 + s2;
	//cout << s3 << endl;

	//s1 += s2;
	//cout << s1 << endl;

	//成员方法方式 append
	s1.append(s2);
	cout << s1 << endl;
}

//string查找和替换 比较
void test05() {

	string s = " acbdefg";
	//查找
	string target = "bd";
	int pos = s.find(target);
	char* target2 = "ef";
	int pos2 = s.find(target2);

	cout << "pos:" << pos << endl;
	cout << "pos2:" << pos2 << endl;

	int pos3 = s.rfind(target);
	cout << "pos3:" << pos3 << endl;

	//字符串替换
	string s1 = "acbd";
	s.replace(0, 2, s1);
	cout << s << endl;


}

//string 比较 子串 插入和删除
void test06() {

	//比较
	string s1 = "abc";
	string s2 = "abd";

	int ret = s1.compare(s2);
	if (ret == 1) {

		cout << "s1 > s2" << endl;
	}
	else if (ret == -1) {

		cout << "s1 < s2" << endl;

	}
	else {
		cout << "s1 == s2" << endl;
	}

	//子串
	string s3 = "abcdefg";
	string s4 = s3.substr(0, 2);
	cout << "s4" << s4 << endl;

	//插入和删除
	string s5 = "abcd";
	s5.insert(0, "pppp");
	string s6 = "qqqq";
	s5.insert(s5.size(), s6);

	cout << s5 << endl;

	s5.erase(0, 4);
	cout << s5 << endl;


}











=======
锘�#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int string_test()
{
    string str1 = "hello";
    int length = str1.length();

    char data[8] = { 0x68, 0x04, 0x43, 0x00, 0x00, 0x00 };
    cout << hex << (unsigned int)(unsigned char)data << endl;

    //闀垮害鏄�5锛屼笉鍖呮嫭\0瀛楃
    printf("璋冪敤str.length()鍑芥暟鑾峰彇瀛楃涓查暱搴︼細%d\n\n", length);
    return 0;
}
int string_test1()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    string str4 = str1 + str2;
    string str5 = str3 + str2;
    cout << "瀛楃涓瞫tr1+str2杩炴帴缁撴灉锛�" << str4 << endl;
    cout << endl;
    cout << "瀛楃涓瞫tr3+str2杩炴帴缁撴灉锛�" << str5 << endl;
    return 0;
}

void string_test2()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    string::const_iterator it = str1.begin();
    cout << *it << endl;

    //end鏄寚鍚戞渶鍚庝竴涓瓧绗﹀悗闈㈢殑鍏冪礌锛岃�屼笖涓嶈兘杈撳嚭,鎵�浠out << *it << endl;杩欐牱杈撳嚭浼氭姤閿�
    it = str1.end();
    it--;
    cout << *it << endl;
}

int string_test3()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    //string 杞寲鎴恥nsigned char
    string str = "csdn";
    unsigned char dst[128] = "";
    strcpy((char *)dst, str.c_str());

    cout << "dst:" << hex << dst[0] << endl;

    char *d = new char[20];   //鍥犱负涓嬩竴鍙ラ偅閲屼笉鏄洿鎺ヨ祴鍊硷紝鎵�浠ユ寚閽堢被鍨嬪彲浠ヤ笉鐢╟onst char *
    strcpy(d, str3.c_str());  //c_str 鍙栧緱C椋庢牸鐨刢onst char* 瀛楃涓�
    cout << "d:" << d << endl;

    return 0;
}

//char* 鍜� string杞崲
void test01()
{
    //string绫诲瀷杞崲涓篶har*瀛楃涓�
    string s = "abc";
    const char *str = s.c_str();

    //char*绫诲瀷瀛楃涓茶浆鎹负string绫诲瀷瀛楃涓�
    char *str2 = "acbd";
    string s2(str2);
}

//string鍒濆鍖�
void test02()
{
    string s; //榛樿鏋勯��
    string s2 = "acbd";
    string s3(s2);

    string s4(10, 'c');

    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
}

//string瀹瑰櫒瀛楃涓茶祴鍊煎拰瀛樺彇
void test03()
{
    //string瀹瑰櫒璧嬪��
    string s;
    s = "abcd";

    string s2;
    s2.assign("pppp");

    //string瀹瑰櫒瀛樺彇
    string s3 = "abcdefg";
    for (int i = 0; i < s3.size(); i++) {
        cout << s3[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < s3.size(); i++) {
        cout << s3.at(i) << " ";
    }
    cout << endl;

    //銆愩�戣闂柟寮忚闂秺鐣屾椂鍊欙紝涓嶄細鎶涘紓甯革紝鐩存帴鎸傛帀
    //at浼氭姏鍑哄紓甯�
    try {
        //cout << s3[100] << endl;
        cout << s3.at(100) << endl;
    } catch (...) {
        cout << "璁块棶瓒婄晫!" << endl;
    }
}

//string瀹瑰櫒鎷兼帴鎿嶄綔
void test04()
{
    string s1 = "aaa";
    string s2 = "bbb";

    //string s3 = s1 + s2;
    //cout << s3 << endl;

    //s1 += s2;
    //cout << s1 << endl;

    //鎴愬憳鏂规硶鏂瑰紡 append
    s1.append(s2);
    cout << s1 << endl;
}

//string鏌ユ壘鍜屾浛鎹� 姣旇緝
void test05()
{
    string s = " acbdefg";
    //鏌ユ壘
    string target = "bd";
    int pos = s.find(target);
    char *target2 = "ef";
    int pos2 = s.find(target2);

    cout << "pos:" << pos << endl;
    cout << "pos2:" << pos2 << endl;

    int pos3 = s.rfind(target);
    cout << "pos3:" << pos3 << endl;

    //瀛楃涓叉浛鎹�
    string s1 = "acbd";
    s.replace(0, 2, s1);
    cout << s << endl;
}

//string 姣旇緝 瀛愪覆 鎻掑叆鍜屽垹闄�
void test06()
{
    //姣旇緝
    string s1 = "abc";
    string s2 = "abd";

    int ret = s1.compare(s2);
    if (ret == 1) {
        cout << "s1 > s2" << endl;
    } else if (ret == -1) {
        cout << "s1 < s2" << endl;
    } else {
        cout << "s1 == s2" << endl;
    }

    //瀛愪覆
    string s3 = "abcdefg";
    string s4 = s3.substr(0, 2);
    cout << "s4" << s4 << endl;

    //鎻掑叆鍜屽垹闄�
    string s5 = "abcd";
    s5.insert(0, "pppp");
    string s6 = "qqqq";
    s5.insert(s5.size(), s6);

    cout << s5 << endl;

    s5.erase(0, 4);
    cout << s5 << endl;
}

void string_test5()

{

    for (int i = 1; i < 10; i++)

    {

        std::string ip("ip");

        std::string newip = ip + std::to_string(i);

        std::cout << newip << std::endl;

    }



}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
