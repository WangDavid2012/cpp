#pragma once
#include<conio.h>
#include<Windows.h>
#include "Snake.h"

//���������
class Player {
public:
	//snake�����ƶ��ߣ�wall���ڸ��»���
	Player(Snake& snake, Wall& wall);

	//������
	void play();
private:
	Snake& snake;
	Wall& wall;
};
