#pragma once
#include<conio.h>
#include<Windows.h>
#include "Snake.h"

//引入玩家类
class Player {
public:
	//snake用于移动蛇，wall用于更新画面
	Player(Snake& snake, Wall& wall);

	//玩起来
	void play();
private:
	Snake& snake;
	Wall& wall;
};
