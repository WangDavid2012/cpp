//�ο����� https://blog.csdn.net/WJ_SHI/article/details/107347142?utm_medium=distribute.pc_feed.415875.nonecase&depth_1-utm_source=distribute.pc_feed.415875.nonecase

#include <iostream>
#include <ctime>
#include "Wall.h"
#include "Snake.h"
#include "Food.h"
#include "Player.h"

int main()
{
	srand(time(NULL));					//���������
	Wall wall;							//��ʼ��һ��ǽ����
	Food food(wall);					//��ʼ��һ��ʳ�����
	Snake snake(wall, food);			//��ʼ��һ���߶���
	Player wangErdan(snake, wall);		//��������������ǳ�
	food.generateFood();				//��һ���棬��Ҫ��һ����ʼ����ʳ��
	wall.drawWall(snake.getScore());	//���Ƶ�һ������ʱ�߲�δ����
	wangErdan.play();					//��������ʼ����Ϸ��
	return 0;
}
