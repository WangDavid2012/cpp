#include "Snake.h"
#include<stdexcept>


//初始化蛇，假设一开始蛇为3段，2段蛇身，1段蛇头
Snake::Snake(Wall& wall, Food& food) : wall(wall), food(food) {
	this->snakeList.push_back(std::make_pair<int, int>(5, 4)); //蛇尾
	this->snakeList.push_back(std::make_pair<int, int>(5, 5)); //蛇身
	this->snakeList.push_back(std::make_pair<int, int>(5, 6)); //蛇头
	this->wall.setPoint(5, 4, '=');
	this->wall.setPoint(5, 5, '=');
	this->wall.setPoint(5, 6, '@');
}

//弹出蛇尾
void Snake::popSnakeTail() {
	std::pair<int, int> snakeTail = this->snakeList.front(); //记录下蛇尾的坐标，用于清除墙中二维数组中的当前蛇尾
	this->snakeList.pop_front();
	this->wall.setPoint(snakeTail.first, snakeTail.second, ' '); //重新写入空格
}

//插入蛇头,再插入蛇头之前，需要将原蛇头位置变为蛇身
void Snake::insertSnakeHead(int x, int y) {
	std::pair<int, int> snakeHead = this->snakeList.back();
	this->wall.setPoint(snakeHead.first, snakeHead.second, '=');  //更新为蛇身
	this->snakeList.push_back(std::pair<int, int>(x, y));  //将新的蛇头坐标保存
	this->wall.setPoint(x, y, '@');
}

bool Snake::moveSnake(char direction) {
	std::pair<int, int> snakeHead = this->snakeList.back(); //先取出蛇头的坐标
	int headX = snakeHead.first;
	int headY = snakeHead.second;
	switch (direction)  //根据方向来判断需要如何修改
	{
	case UP:  //如果向上移动了，那么新的蛇头坐标应该为--headX, headY
		--headX;
		break;
	case DOWN:
		++headX; //向下移动，则新蛇头坐标为++headX, headY
		break;
	case LEFT:
		--headY;
		break;
	case RIGHT:
		++headY;
		break;
	default:
		break;
	}
	//接下来就需要能否成功移动一步
	char space = this->wall.getPoint(headX, headY);
	if (space == ' ') {  //如果要移动到的点为空格，则该空间无任何东西，可正常移动,则需要掐尾改头
		this->popSnakeTail();
		this->insertSnakeHead(headX, headY);
		return true;
	}

	//再加一个判断，如果此时蛇尾正好需要移动，同时蛇头会在这个位置出现，并不会死亡
	/*
	=
	@  =   在这种情况下，蛇头往上，蛇尾向右，这种情况不会死亡，但是程序会判定为死亡，因为先撞上，再修改
	=
	*/
	else if (space == '=') {  //如果下一个要走的点还是蛇身
		this->popSnakeTail();  //先将末尾弹出，再判断，要走的位置是否位空，如果还不是空，则是撞上了
		space = this->wall.getPoint(headX, headY);
		if (space == ' ') {
			this->insertSnakeHead(headX, headY);
			return true;
		}
		else {
			this->insertSnakeHead(headX, headY);
			return false;
		}

	}

	else if (space == '#') { //如果是食物，那么蛇身需要加长1，因此不需要再将蛇尾弹出，只需改掉头即可
		this->insertSnakeHead(headX, headY);
		//食物被吃掉之后需要生成新的食物
		this->food.generateFood();
		return true;
	}
	else {  //否则撞墙了或撞到蛇身了
		this->popSnakeTail();
		this->insertSnakeHead(headX, headY);
		return false;
	}
}

//以蛇的长度代替得分，每增加一段即吃掉一个食物，则增加10分
unsigned int Snake::getScore()const {
	return this->snakeList.size();  //每增加一段就加10分并在绘制时输出
}
