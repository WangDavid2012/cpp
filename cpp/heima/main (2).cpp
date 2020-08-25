#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "Circle.h"
#include "Point.h"

using namespace std;

int main(void)
{
	Point p;
	Circle c;

	p.setXY(6, 8);
	c.setXY(2, 2);
	c.setR(4);

	if (c.judgePoint(p) == true) {
		cout << "在圆的内部" << endl;
	}
	else {
		cout << "在圆的外部" << endl;
	}
	
	return 0;
}