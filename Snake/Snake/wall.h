#pragma once
#include<iostream>

class Wall {
public:
	enum
	{
		ROW = 25, COLUMN = 25
	};

	//构造函数
	Wall();

	//根据条件设置点的元素，可能为食物，可能为蛇身可能为蛇头
	void setPoint(int x, int y, char ele);

	//获取某一坐标的元素，用于给需要移动到的下一点判断是否会装上
	char getPoint(int x, int y)const;

	//在屏幕上输出当前状态
	void drawWall();

	//重载绘制方法，此时传入一个参数为得分，并写在第一行
	void drawWall(unsigned int score);

private:
	char gameArr[ROW][COLUMN];  //维护一个二维数组
};

