//参考博客 https://blog.csdn.net/WJ_SHI/article/details/107347142?utm_medium=distribute.pc_feed.415875.nonecase&depth_1-utm_source=distribute.pc_feed.415875.nonecase

#include <iostream>
#include <ctime>
#include "Wall.h"
#include "Snake.h"
#include "Food.h"
#include "Player.h"

int main()
{
	srand(time(NULL));					//随机数种子
	Wall wall;							//初始化一个墙对象
	Food food(wall);					//初始化一个食物对象
	Snake snake(wall, food);			//初始化一个蛇对象
	Player wangErdan(snake, wall);		//玩家王二蛋闪亮登场
	food.generateFood();				//第一次玩，需要有一个初始化的食物
	wall.drawWall(snake.getScore());	//绘制第一屏，此时蛇并未激活
	wangErdan.play();					//王二蛋开始玩游戏了
	return 0;
}
