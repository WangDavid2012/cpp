#include "Player.h"

Player::Player(Snake& snake, Wall& wall) : snake(snake), wall(wall) {}


void Player::play() {
	//�ж����Ƿ񻹴�����Ϸ�Ƿ�Ҫ������Ϸ
	bool isAlive = true;

	//����һ������������ж���Ϸ�Ƿ񼤻ֻ�е�һ�ΰ���Ϊwsd�е�һ���򼤻���Ϸ
	bool isActive = false;

	//������¼��һ�εİ����������һ�ΰ����ͱ��ΰ��������෴������һ��d����һ����a������Ϊ����Ҫ��ת180�㣬Ȼ�����ǲ�����ʵ�ֵġ� 
	//���Ҹտ�ʼ������Ϸʱ���ܰ�a�����򿪾־���
	char preKey = Snake::RIGHT;

	while (true) {
		char ch = _getch();  //ͨ�����̻�ȡһ������ֵ
		do {
			if (ch != Snake::LEFT && ch != Snake::UP && ch != Snake::RIGHT && ch != Snake::DOWN && !isActive)  //�����Ұ��Ĳ���asdw����ֱ�Ӻ���
				break;

			else if (ch != Snake::LEFT && ch != Snake::UP && ch != Snake::RIGHT && ch != Snake::DOWN && isActive)  //��������ˣ����ǰ�������wasd����һ��������Ϊ������Ч
				ch = preKey; //��֮ǰ�İ�����ֵ����ǰ����

			if (preKey == Snake::RIGHT && ch == Snake::LEFT ||
				preKey == Snake::LEFT && ch == Snake::RIGHT ||
				preKey == Snake::DOWN && ch == Snake::UP ||
				preKey == Snake::UP && ch == Snake::DOWN)
				ch = preKey;  //������˷���������Ϊû�а���

			isActive = true; //��Ϸ�Ѽ���
			isAlive = snake.moveSnake(ch); //�����Ϸʧ������Ϸ��ֹ
			system("cls");  //����������һ�λ���
			wall.drawWall(snake.getScore());  //���»��Ƶ�ǰ״̬
			if (!isAlive) {
				std::cout << "GAME OVER!!!" << std::endl;
				break;
			}

			//�����Ѷȣ������ߵĳ����������Ѷ�
			unsigned int difficultLevel = this->snake.getScore();

			if (difficultLevel < 8)  //�����С��8�Σ�����֡����ˢ��ʱ��Ϊ800ms
				Sleep(800);
			else if (difficultLevel < 15 && difficultLevel >= 8) //�����С��15�ε�����8����ˢ��ʱ��Ϊ500ms
				Sleep(500);

			else if (difficultLevel < 20 && difficultLevel >= 15) //�����ӿ��ٶ�
				Sleep(200);

			else if (difficultLevel < 30 && difficultLevel >= 20)
				Sleep(100);

			else
				Sleep(50);

			preKey = ch;  //��ס��ǰ�İ��������ں���һ�εİ������Ա�
		} while (!_kbhit()); //���û�а���������Ϊ���ϴΰ���һ��
		if (!isAlive)
			break;
	}
}
