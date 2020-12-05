#pragma once
#include<iostream>

class Wall {
public:
	enum
	{
		ROW = 25, COLUMN = 25
	};

	//���캯��
	Wall();

	//�����������õ��Ԫ�أ�����Ϊʳ�����Ϊ�������Ϊ��ͷ
	void setPoint(int x, int y, char ele);

	//��ȡĳһ�����Ԫ�أ����ڸ���Ҫ�ƶ�������һ���ж��Ƿ��װ��
	char getPoint(int x, int y)const;

	//����Ļ�������ǰ״̬
	void drawWall();

	//���ػ��Ʒ�������ʱ����һ������Ϊ�÷֣���д�ڵ�һ��
	void drawWall(unsigned int score);

private:
	char gameArr[ROW][COLUMN];  //ά��һ����ά����
};

