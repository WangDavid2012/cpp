#pragma once
#include<math.h>
#include "Wall.h"


class Food {
public:

	//构造时需要将墙传入，因为每当生成一个食物时，需要更新到墙中
	Food(Wall& wall);

	//生成食物
	void generateFood();
private:
	Wall& wall;
};
