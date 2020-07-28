#include "Food.h"

Food::Food(Wall& wall) : wall(wall) {}

void Food::generateFood() {
	int foodX = 0;
	int foodY = 0;
	while (true) {
		foodX = rand() % Wall::COLUMN + 1; //食物的x坐标限制在墙内
		foodY = rand() % Wall::ROW + 1; //同理，食物的y坐标也应限制在墙内

		if (this->wall.getPoint(foodX, foodY) == ' ') {  // 只有食物的坐标处无任何东西时，食物生成才算成功，否则重新生成
			this->wall.setPoint(foodX, foodY, '#');
			break;
		}
	}
}
