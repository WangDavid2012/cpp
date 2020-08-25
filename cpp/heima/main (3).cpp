#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "Circle.h"

using namespace std;

int main(void)
{
	Circle c1;

	c1.setR(10.0);

	cout << c1.getArea() << endl;
	cout << c1.getGirth() << endl;
	
	return 0;
}