<<<<<<< HEAD
#include<iostream>  
#include<sstream>        //istringstream ±ØĞë°üº¬Õâ¸öÍ·ÎÄ¼ş
#include<string>  
using namespace std;

void isstringstream_test()
{
	string str = "i am a boy";
	istringstream is(str);
	string s;
	while (is >> s)
	{
		cout << s << endl;
	}

	//½«¶ÁÈëµÄÒ»ĞĞÖĞµÄÈı¸öÕûÊı´æ´¢µ½ÁËa, b, cÖĞ
	//ifstream fin(fname);
	//int a, b, c;
	//string s;
	//getline(fin, s);
	//istringstream ss(s);
	//ss >> a >> b >> c;
}



void getline_test()
{
	// greet the user
	std::string name;
	std::cout << "What is your name? ";
	std::getline(std::cin, name);
	std::cout << "Hello " << name << ", nice to meet you.\n";

	// read file line by line
	std::istringstream input;
	input.str("1\n2\n3\n4\n5\n6\n7\n");
	int sum = 0;
	for (std::string line; std::getline(input, line); ) {
		sum += std::stoi(line);
	}
	std::cout << "\nThe sum is: " << sum << "\n";
}


//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//int getcwd_test()
//{
//	char *path = NULL;
//	path = getcwd(NULL, 0);
//	puts(path);
//	free(path);
//	return 0;
//}
=======
ï»¿#include<iostream>
#include<sstream>        //istringstream å¿…é¡»åŒ…å«è¿™ä¸ªå¤´æ–‡ä»¶
#include<string>
using namespace std;

void isstringstream_test()
{
	string str = "i am a boy";
	istringstream is(str);
	string s;
	while (is >> s)
	{
		cout << s << endl;
	}

	//å°†è¯»å…¥çš„ä¸€è¡Œä¸­çš„ä¸‰ä¸ªæ•´æ•°å­˜å‚¨åˆ°äº†a, b, cä¸­
	//ifstream fin(fname);
	//int a, b, c;
	//string s;
	//getline(fin, s);
	//istringstream ss(s);
	//ss >> a >> b >> c;
}

void getline_test()
{
	// greet the user
	std::string name;
	std::cout << "What is your name? ";
	std::getline(std::cin, name);
	std::cout << "Hello " << name << ", nice to meet you.\n";

	// read file line by line
	std::istringstream input;
	input.str("1\n2\n3\n4\n5\n6\n7\n");
	int sum = 0;
	for (std::string line; std::getline(input, line); ) {
		sum += std::stoi(line);
	}
	std::cout << "\nThe sum is: " << sum << "\n";
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//int getcwd_test()
//{
//	char *path = NULL;
//	path = getcwd(NULL, 0);
//	puts(path);
//	free(path);
//	return 0;
//}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
