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

	//³¤¶ÈÊÇ5£¬²»°üÀ¨\0×Ö·û
	printf("µ÷ÓÃstr.length()º¯Êý»ñÈ¡×Ö·û´®³¤¶È£º%d\n\n", length);
	return 0;
}
int string_test1()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string str4 = str1 + str2;
	string str5 = str3 + str2;
	cout << "×Ö·û´®str1+str2Á¬½Ó½á¹û£º" << str4 << endl;
	cout << endl;
	cout << "×Ö·û´®str3+str2Á¬½Ó½á¹û£º" << str5 << endl;
	return 0;
}

void string_test2()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	string::const_iterator it = str1.begin();
	cout << *it << endl;


	//endÊÇÖ¸Ïò×îºóÒ»¸ö×Ö·ûºóÃæµÄÔªËØ£¬¶øÇÒ²»ÄÜÊä³ö,ËùÒÔcout << *it << endl;ÕâÑùÊä³ö»á±¨´í
	it = str1.end();
	it--;
	cout << *it << endl;

}

int string_test3()
{
	string str1 = "hello";
	string str2 = "my girl!";
	string str3 = "hello ";

	//string ×ª»¯³Éunsigned char
	string str = "csdn";
	unsigned char dst[128] = "";
	strcpy((char*)dst, str.c_str());

	cout << "dst:" << hex << dst[0] << endl;

	char *d = new char[20];   //ÒòÎªÏÂÒ»¾äÄÇÀï²»ÊÇÖ±½Ó¸³Öµ£¬ËùÒÔÖ¸ÕëÀàÐÍ¿ÉÒÔ²»ÓÃconst char *
	strcpy(d, str3.c_str());  //c_str È¡µÃC·ç¸ñµÄconst char* ×Ö·û´®
	cout << "d:" << d << endl;

	return 0;
}





//char* ºÍ string×ª»»
void test01() {

	//stringÀàÐÍ×ª»»Îªchar*×Ö·û´®
	string s = "abc";
	const char* str = s.c_str();

	//char*ÀàÐÍ×Ö·û´®×ª»»ÎªstringÀàÐÍ×Ö·û´®
	char* str2 = "acbd";
	string s2(str2);

}

//string³õÊ¼»¯
void test02() {

	string s; //Ä¬ÈÏ¹¹Ôì
	string s2 = "acbd";
	string s3(s2);

	string s4(10, 'c');


	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;

}

//stringÈÝÆ÷×Ö·û´®¸³ÖµºÍ´æÈ¡
void test03() {


	//stringÈÝÆ÷¸³Öµ
	string s;
	s = "abcd";

	string s2;
	s2.assign("pppp");


	//stringÈÝÆ÷´æÈ¡
	string s3 = "abcdefg";
	for (int i = 0; i < s3.size(); i++) {
		cout << s3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s3.size(); i++) {
		cout << s3.at(i) << " ";
	}
	cout << endl;


	//¡¾¡¿·ÃÎÊ·½Ê½·ÃÎÊÔ½½çÊ±ºò£¬²»»áÅ×Òì³££¬Ö±½Ó¹Òµô
	//at»áÅ×³öÒì³£
	try {
		//cout << s3[100] << endl;
		cout << s3.at(100) << endl;
	}
	catch (...) {
		cout << "·ÃÎÊÔ½½ç!" << endl;
	}


}

//stringÈÝÆ÷Æ´½Ó²Ù×÷
void test04() {

	string s1 = "aaa";
	string s2 = "bbb";

	//string s3 = s1 + s2;
	//cout << s3 << endl;

	//s1 += s2;
	//cout << s1 << endl;

	//³ÉÔ±·½·¨·½Ê½ append
	s1.append(s2);
	cout << s1 << endl;
}

//string²éÕÒºÍÌæ»» ±È½Ï
void test05() {

	string s = " acbdefg";
	//²éÕÒ
	string target = "bd";
	int pos = s.find(target);
	char* target2 = "ef";
	int pos2 = s.find(target2);

	cout << "pos:" << pos << endl;
	cout << "pos2:" << pos2 << endl;

	int pos3 = s.rfind(target);
	cout << "pos3:" << pos3 << endl;

	//×Ö·û´®Ìæ»»
	string s1 = "acbd";
	s.replace(0, 2, s1);
	cout << s << endl;


}

//string ±È½Ï ×Ó´® ²åÈëºÍÉ¾³ý
void test06() {

	//±È½Ï
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

	//×Ó´®
	string s3 = "abcdefg";
	string s4 = s3.substr(0, 2);
	cout << "s4" << s4 << endl;

	//²åÈëºÍÉ¾³ý
	string s5 = "abcd";
	s5.insert(0, "pppp");
	string s6 = "qqqq";
	s5.insert(s5.size(), s6);

	cout << s5 << endl;

	s5.erase(0, 4);
	cout << s5 << endl;


}











=======
ï»¿#define _CRT_SECURE_NO_WARNINGS

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

    //é•¿åº¦æ˜¯5ï¼Œä¸åŒ…æ‹¬\0å­—ç¬¦
    printf("è°ƒç”¨str.length()å‡½æ•°èŽ·å–å­—ç¬¦ä¸²é•¿åº¦ï¼š%d\n\n", length);
    return 0;
}
int string_test1()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    string str4 = str1 + str2;
    string str5 = str3 + str2;
    cout << "å­—ç¬¦ä¸²str1+str2è¿žæŽ¥ç»“æžœï¼š" << str4 << endl;
    cout << endl;
    cout << "å­—ç¬¦ä¸²str3+str2è¿žæŽ¥ç»“æžœï¼š" << str5 << endl;
    return 0;
}

void string_test2()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    string::const_iterator it = str1.begin();
    cout << *it << endl;

    //endæ˜¯æŒ‡å‘æœ€åŽä¸€ä¸ªå­—ç¬¦åŽé¢çš„å…ƒç´ ï¼Œè€Œä¸”ä¸èƒ½è¾“å‡º,æ‰€ä»¥cout << *it << endl;è¿™æ ·è¾“å‡ºä¼šæŠ¥é”™
    it = str1.end();
    it--;
    cout << *it << endl;
}

int string_test3()
{
    string str1 = "hello";
    string str2 = "my girl!";
    string str3 = "hello ";

    //string è½¬åŒ–æˆunsigned char
    string str = "csdn";
    unsigned char dst[128] = "";
    strcpy((char *)dst, str.c_str());

    cout << "dst:" << hex << dst[0] << endl;

    char *d = new char[20];   //å› ä¸ºä¸‹ä¸€å¥é‚£é‡Œä¸æ˜¯ç›´æŽ¥èµ‹å€¼ï¼Œæ‰€ä»¥æŒ‡é’ˆç±»åž‹å¯ä»¥ä¸ç”¨const char *
    strcpy(d, str3.c_str());  //c_str å–å¾—Cé£Žæ ¼çš„const char* å­—ç¬¦ä¸²
    cout << "d:" << d << endl;

    return 0;
}

//char* å’Œ stringè½¬æ¢
void test01()
{
    //stringç±»åž‹è½¬æ¢ä¸ºchar*å­—ç¬¦ä¸²
    string s = "abc";
    const char *str = s.c_str();

    //char*ç±»åž‹å­—ç¬¦ä¸²è½¬æ¢ä¸ºstringç±»åž‹å­—ç¬¦ä¸²
    char *str2 = "acbd";
    string s2(str2);
}

//stringåˆå§‹åŒ–
void test02()
{
    string s; //é»˜è®¤æž„é€ 
    string s2 = "acbd";
    string s3(s2);

    string s4(10, 'c');

    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
}

//stringå®¹å™¨å­—ç¬¦ä¸²èµ‹å€¼å’Œå­˜å–
void test03()
{
    //stringå®¹å™¨èµ‹å€¼
    string s;
    s = "abcd";

    string s2;
    s2.assign("pppp");

    //stringå®¹å™¨å­˜å–
    string s3 = "abcdefg";
    for (int i = 0; i < s3.size(); i++) {
        cout << s3[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < s3.size(); i++) {
        cout << s3.at(i) << " ";
    }
    cout << endl;

    //ã€ã€‘è®¿é—®æ–¹å¼è®¿é—®è¶Šç•Œæ—¶å€™ï¼Œä¸ä¼šæŠ›å¼‚å¸¸ï¼Œç›´æŽ¥æŒ‚æŽ‰
    //atä¼šæŠ›å‡ºå¼‚å¸¸
    try {
        //cout << s3[100] << endl;
        cout << s3.at(100) << endl;
    } catch (...) {
        cout << "è®¿é—®è¶Šç•Œ!" << endl;
    }
}

//stringå®¹å™¨æ‹¼æŽ¥æ“ä½œ
void test04()
{
    string s1 = "aaa";
    string s2 = "bbb";

    //string s3 = s1 + s2;
    //cout << s3 << endl;

    //s1 += s2;
    //cout << s1 << endl;

    //æˆå‘˜æ–¹æ³•æ–¹å¼ append
    s1.append(s2);
    cout << s1 << endl;
}

//stringæŸ¥æ‰¾å’Œæ›¿æ¢ æ¯”è¾ƒ
void test05()
{
    string s = " acbdefg";
    //æŸ¥æ‰¾
    string target = "bd";
    int pos = s.find(target);
    char *target2 = "ef";
    int pos2 = s.find(target2);

    cout << "pos:" << pos << endl;
    cout << "pos2:" << pos2 << endl;

    int pos3 = s.rfind(target);
    cout << "pos3:" << pos3 << endl;

    //å­—ç¬¦ä¸²æ›¿æ¢
    string s1 = "acbd";
    s.replace(0, 2, s1);
    cout << s << endl;
}

//string æ¯”è¾ƒ å­ä¸² æ’å…¥å’Œåˆ é™¤
void test06()
{
    //æ¯”è¾ƒ
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

    //å­ä¸²
    string s3 = "abcdefg";
    string s4 = s3.substr(0, 2);
    cout << "s4" << s4 << endl;

    //æ’å…¥å’Œåˆ é™¤
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
