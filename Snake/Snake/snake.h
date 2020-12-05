#pragma once
#pragma once
#include<list>
#include<algorithm>
#include "Wall.h"
#include "Food.h"

class Snake {
public:
	enum {
		LEFT = 'a',
		RIGHT = 'd',
		UP = 'w',
		DOWN = 's'
	};
	//���캯������ʼ��ʱ��Ҫ��wall�����룬�����������Ҫ����wall�еĶ�ά����
	Snake(Wall& wall);

	//����дһ�����캯������Ҫ��food�ഫ����Ϊ�ڲ���
	Snake(Wall& wall, Food& food);

	//������ǰ����β
	void popSnakeTail();

	//��������ͷ��λ��,�������Ϊ����ͷ������
	void insertSnakeHead(int x, int y);

	//ͨ��wasd�����ƶ���,����Ĳ���Ϊ�ߵ��ƶ�����������Գɹ��ƶ����򷵻�true������false
	bool moveSnake(char direction);

	//��ȡ�÷ֽӿڣ������ṩ�÷�
	unsigned int getScore()const;

private:
	Wall& wall;
	//ά��һ�����б������������ͷ��������pair��ʽ����
	std::list<std::pair<int, int>> snakeList;

	Food& food;
};
