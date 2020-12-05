#include "Snake.h"
#include<stdexcept>


//��ʼ���ߣ�����һ��ʼ��Ϊ3�Σ�2������1����ͷ
Snake::Snake(Wall& wall, Food& food) : wall(wall), food(food) {
	this->snakeList.push_back(std::make_pair<int, int>(5, 4)); //��β
	this->snakeList.push_back(std::make_pair<int, int>(5, 5)); //����
	this->snakeList.push_back(std::make_pair<int, int>(5, 6)); //��ͷ
	this->wall.setPoint(5, 4, '=');
	this->wall.setPoint(5, 5, '=');
	this->wall.setPoint(5, 6, '@');
}

//������β
void Snake::popSnakeTail() {
	std::pair<int, int> snakeTail = this->snakeList.front(); //��¼����β�����꣬�������ǽ�ж�ά�����еĵ�ǰ��β
	this->snakeList.pop_front();
	this->wall.setPoint(snakeTail.first, snakeTail.second, ' '); //����д��ո�
}

//������ͷ,�ٲ�����ͷ֮ǰ����Ҫ��ԭ��ͷλ�ñ�Ϊ����
void Snake::insertSnakeHead(int x, int y) {
	std::pair<int, int> snakeHead = this->snakeList.back();
	this->wall.setPoint(snakeHead.first, snakeHead.second, '=');  //����Ϊ����
	this->snakeList.push_back(std::pair<int, int>(x, y));  //���µ���ͷ���걣��
	this->wall.setPoint(x, y, '@');
}

bool Snake::moveSnake(char direction) {
	std::pair<int, int> snakeHead = this->snakeList.back(); //��ȡ����ͷ������
	int headX = snakeHead.first;
	int headY = snakeHead.second;
	switch (direction)  //���ݷ������ж���Ҫ����޸�
	{
	case UP:  //��������ƶ��ˣ���ô�µ���ͷ����Ӧ��Ϊ--headX, headY
		--headX;
		break;
	case DOWN:
		++headX; //�����ƶ���������ͷ����Ϊ++headX, headY
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
	//����������Ҫ�ܷ�ɹ��ƶ�һ��
	char space = this->wall.getPoint(headX, headY);
	if (space == ' ') {  //���Ҫ�ƶ����ĵ�Ϊ�ո���ÿռ����κζ������������ƶ�,����Ҫ��β��ͷ
		this->popSnakeTail();
		this->insertSnakeHead(headX, headY);
		return true;
	}

	//�ټ�һ���жϣ������ʱ��β������Ҫ�ƶ���ͬʱ��ͷ�������λ�ó��֣�����������
	/*
	=
	@  =   ����������£���ͷ���ϣ���β���ң���������������������ǳ�����ж�Ϊ��������Ϊ��ײ�ϣ����޸�
	=
	*/
	else if (space == '=') {  //�����һ��Ҫ�ߵĵ㻹������
		this->popSnakeTail();  //�Ƚ�ĩβ���������жϣ�Ҫ�ߵ�λ���Ƿ�λ�գ���������ǿգ�����ײ����
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

	else if (space == '#') { //�����ʳ���ô������Ҫ�ӳ�1����˲���Ҫ�ٽ���β������ֻ��ĵ�ͷ����
		this->insertSnakeHead(headX, headY);
		//ʳ�ﱻ�Ե�֮����Ҫ�����µ�ʳ��
		this->food.generateFood();
		return true;
	}
	else {  //����ײǽ�˻�ײ��������
		this->popSnakeTail();
		this->insertSnakeHead(headX, headY);
		return false;
	}
}

//���ߵĳ��ȴ���÷֣�ÿ����һ�μ��Ե�һ��ʳ�������10��
unsigned int Snake::getScore()const {
	return this->snakeList.size();  //ÿ����һ�ξͼ�10�ֲ��ڻ���ʱ���
}
