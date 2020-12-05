#pragma once
#pragma once
#include<list>
#include<algorithm>
#include "Wall.h"
#include "Food.h"

class Snake {
public:
	enum {
		LEFT = 'a',
		RIGHT = 'd',
		UP = 'w',
		DOWN = 's'
	};
	//构造函数，初始化时需要将wall对象传入，构造出的蛇需要存入wall中的二维数组
	Snake(Wall& wall);

	//重新写一个构造函数，需要将food类传入作为内部类
	Snake(Wall& wall, Food& food);

	//弹出当前的蛇尾
	void popSnakeTail();

	//插入新蛇头的位置,传入参数为新蛇头的坐标
	void insertSnakeHead(int x, int y);

	//通过wasd操纵移动蛇,传入的参数为蛇的移动方向，如果可以成功移动，则返回true，否则false
	bool moveSnake(char direction);

	//获取得分接口，用来提供得分
	unsigned int getScore()const;

private:
	Wall& wall;
	//维护一个蛇列表，其中蛇身或蛇头的坐标用pair形式保存
	std::list<std::pair<int, int>> snakeList;

	Food& food;
};
