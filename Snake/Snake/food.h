#pragma once
#include<math.h>
#include "Wall.h"


class Food {
public:

	//����ʱ��Ҫ��ǽ���룬��Ϊÿ������һ��ʳ��ʱ����Ҫ���µ�ǽ��
	Food(Wall& wall);

	//����ʳ��
	void generateFood();
private:
	Wall& wall;
};
