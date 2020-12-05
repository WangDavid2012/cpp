#include"Wall.h"

//构造函数，先把墙搭建好，即i=0或i=ROW - 1或j=0或j=COLUMN - 1的地方就为墙用'*'表示，其他地方为待使用区域用' '表示
Wall::Wall() {
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			if (i == 0 || j == 0 || i == ROW - 1 || j == COLUMN - 1)
				this->gameArr[i][j] = '*';
			else
				this->gameArr[i][j] = ' ';
}

//根据传入的元素，设置点位的状态，可能是食物'#'，也可能是蛇头'@'或蛇身'='
void Wall::setPoint(int x, int y, char ele) {
	this->gameArr[x][y] = ele;
}

//返回点位的元素，用来判断是否会撞上，或者是否吃到了食物
char Wall::getPoint(int x, int y)const {
	return this->gameArr[x][y];
}

//将二维数组中维护的状态输出在屏幕上，同时在右侧加入开发者，玩法等信息
void Wall::drawWall() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; j++)
			std::cout << this->gameArr[i][j] << " ";
		if (i == 6)
			std::cout << "开发者: 方人也WJ";
		if (i == 8)
			std::cout << "玩法——a: left | w: up | s:down | d: right";
		std::cout << std::endl;
	}
}

//重载的输出信息，并且通过传入的分数参数计算当前的得分
void Wall::drawWall(unsigned int score) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; j++)
			std::cout << this->gameArr[i][j] << " ";
		if (i == 1)
			std::cout << "当前得分：" << (score - 3) * 10; //要减去一开始的时候蛇就有3段即减掉30分
		if (i == 6)
			std::cout << "开发者: 方人也WJ";
		if (i == 8)
			std::cout << "玩法——a: left | w: up | s:down | d: right";
		std::cout << std::endl;
	}
}
