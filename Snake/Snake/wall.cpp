#include"Wall.h"

//���캯�����Ȱ�ǽ��ã���i=0��i=ROW - 1��j=0��j=COLUMN - 1�ĵط���Ϊǽ��'*'��ʾ�������ط�Ϊ��ʹ��������' '��ʾ
Wall::Wall() {
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COLUMN; ++j)
			if (i == 0 || j == 0 || i == ROW - 1 || j == COLUMN - 1)
				this->gameArr[i][j] = '*';
			else
				this->gameArr[i][j] = ' ';
}

//���ݴ����Ԫ�أ����õ�λ��״̬��������ʳ��'#'��Ҳ��������ͷ'@'������'='
void Wall::setPoint(int x, int y, char ele) {
	this->gameArr[x][y] = ele;
}

//���ص�λ��Ԫ�أ������ж��Ƿ��ײ�ϣ������Ƿ�Ե���ʳ��
char Wall::getPoint(int x, int y)const {
	return this->gameArr[x][y];
}

//����ά������ά����״̬�������Ļ�ϣ�ͬʱ���Ҳ���뿪���ߣ��淨����Ϣ
void Wall::drawWall() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; j++)
			std::cout << this->gameArr[i][j] << " ";
		if (i == 6)
			std::cout << "������: ����ҲWJ";
		if (i == 8)
			std::cout << "�淨����a: left | w: up | s:down | d: right";
		std::cout << std::endl;
	}
}

//���ص������Ϣ������ͨ������ķ����������㵱ǰ�ĵ÷�
void Wall::drawWall(unsigned int score) {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; j++)
			std::cout << this->gameArr[i][j] << " ";
		if (i == 1)
			std::cout << "��ǰ�÷֣�" << (score - 3) * 10; //Ҫ��ȥһ��ʼ��ʱ���߾���3�μ�����30��
		if (i == 6)
			std::cout << "������: ����ҲWJ";
		if (i == 8)
			std::cout << "�淨����a: left | w: up | s:down | d: right";
		std::cout << std::endl;
	}
}
