#include <iostream>
#include <typeinfo>
using namespace std;

void auto_test1()
{
	auto value1 = 1;
	auto value2 = 2.33;
	auto value3 = 'a';
	std::cout << "value1 �������� " << typeid(value1).name() << std::endl;
	std::cout << "value2 �������� " << typeid(value2).name() << std::endl;
	std::cout << "value3 �������� " << typeid(value3).name() << std::endl;

}