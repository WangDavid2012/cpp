#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;


//char* 和 string转换
void test01(){

	//string类型转换为char*字符串
	string s = "abc";
	const char* str = s.c_str();

	//char*类型字符串转换为string类型字符串
	char* str2 = "acbd";
	string s2(str2);

}

//string初始化
void test02(){
	
	string s; //默认构造
	string s2 = "acbd";
	string s3(s2);

	string s4(10, 'c');


	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;

}

//string容器字符串赋值和存取
void test03(){
	

	//string容器赋值
	string s;
	s = "abcd";

	string s2;
	s2.assign("pppp");


	//string容器存取
	string s3 = "abcdefg";
	for (int i = 0; i < s3.size();i++){
		cout << s3[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s3.size();i++){
		cout << s3.at(i) << " ";
	}
	cout << endl;


	//【】访问方式访问越界时候，不会抛异常，直接挂掉
	//at会抛出异常
	try{
		//cout << s3[100] << endl;
		cout << s3.at(100) << endl;
	}
	catch (...){
		cout << "访问越界!" << endl;
	}


}

//string容器拼接操作
void test04(){

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
void test05(){

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
void test06(){
	
	//比较
	string s1 = "abc";
	string s2 = "abd";

	int ret = s1.compare(s2);
	if (ret == 1){

		cout << "s1 > s2" << endl;
	}
	else if (ret == -1){

		cout << "s1 < s2" << endl;
	
	}
	else{
		cout << "s1 == s2" << endl;
	}

	//子串
	string s3 = "abcdefg";
	string s4 = s3.substr(0,2);
	cout << "s4" << s4 << endl;

	//插入和删除
	string s5 = "abcd";
	s5.insert(0, "pppp");
	string s6 = "qqqq";
	s5.insert(s5.size(), s6);

	cout << s5 << endl;

	s5.erase(0,4);
	cout << s5 << endl;

	 
}

int main(){


	//test02();
	//test03();
	//test04();
	//test05();
	test06();

	system("pause");
	return EXIT_SUCCESS;
}
