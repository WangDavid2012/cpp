#include "Player.h"

Player::Player(Snake& snake, Wall& wall) : snake(snake), wall(wall) {}


void Player::play() {
	//判断蛇是否还存活，即游戏是否要结束游戏
	bool isAlive = true;

	//放置一个激活变量，判断游戏是否激活，只有第一次按键为wsd中的一个则激活游戏
	bool isActive = false;

	//用来记录上一次的按键，如果上一次按键和本次按键正好相反（如上一次d，这一次是a，则认为蛇需要旋转180°，然而这是不可能实现的。 
	//并且刚开始激活游戏时不能按a，否则开局就死
	char preKey = Snake::RIGHT;

	while (true) {
		char ch = _getch();  //通过键盘获取一个按键值
		do {
			if (ch != Snake::LEFT && ch != Snake::UP && ch != Snake::RIGHT && ch != Snake::DOWN && !isActive)  //如果玩家按的不是asdw键则直接忽略
				break;

			else if (ch != Snake::LEFT && ch != Snake::UP && ch != Snake::RIGHT && ch != Snake::DOWN && isActive)  //如果激活了，但是按键不是wasd其中一个，则认为按键无效
				ch = preKey; //将之前的按键赋值给当前按键

			if (preKey == Snake::RIGHT && ch == Snake::LEFT ||
				preKey == Snake::LEFT && ch == Snake::RIGHT ||
				preKey == Snake::DOWN && ch == Snake::UP ||
				preKey == Snake::UP && ch == Snake::DOWN)
				ch = preKey;  //如果按了反方向，则认为没有按。

			isActive = true; //游戏已激活
			isAlive = snake.moveSnake(ch); //如果游戏失败则游戏终止
			system("cls");  //清屏用于下一次绘制
			wall.drawWall(snake.getScore());  //重新绘制当前状态
			if (!isAlive) {
				std::cout << "GAME OVER!!!" << std::endl;
				break;
			}

			//设置难度，根据蛇的长度来设置难度
			unsigned int difficultLevel = this->snake.getScore();

			if (difficultLevel < 8)  //如果蛇小于8段，则两帧画面刷新时间为800ms
				Sleep(800);
			else if (difficultLevel < 15 && difficultLevel >= 8) //如果蛇小于15段但大于8段则刷新时间为500ms
				Sleep(500);

			else if (difficultLevel < 20 && difficultLevel >= 15) //继续加快速度
				Sleep(200);

			else if (difficultLevel < 30 && difficultLevel >= 20)
				Sleep(100);

			else
				Sleep(50);

			preKey = ch;  //记住当前的按键，用于和下一次的按键作对比
		} while (!_kbhit()); //如果没有按键，则认为和上次按键一样
		if (!isAlive)
			break;
	}
}
