#include "Food.h"

Food::Food(Wall& wall) : wall(wall) {}

void Food::generateFood() {
	int foodX = 0;
	int foodY = 0;
	while (true) {
		foodX = rand() % Wall::COLUMN + 1; //ʳ���x����������ǽ��
		foodY = rand() % Wall::ROW + 1; //ͬ��ʳ���y����ҲӦ������ǽ��

		if (this->wall.getPoint(foodX, foodY) == ' ') {  // ֻ��ʳ������괦���κζ���ʱ��ʳ�����ɲ���ɹ���������������
			this->wall.setPoint(foodX, foodY, '#');
			break;
		}
	}
}
