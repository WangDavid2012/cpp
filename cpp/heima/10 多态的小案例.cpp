#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Hero
{
public:
	//��ǰHero��ս������10
	virtual int getAd(){
		return 10;
	}
};

//����Ӣ��
class SuperHero :public Hero
{
public:
	virtual int getAd()
	{
		return 100;
	}
};

class BugHero : public Hero
{
public:
	virtual int getAd()
	{
		return 10000;
	}
};

//����
class Monster
{
public:
	int getAd()
	{
		return 30;
	}
};

//ս���ĺ���
//��д�� ս�������� ͨ���ø����ָ����Ϊ����
//��̬���е���δ���� ���塣
void PlayerFight(Hero *hero, Monster *m)
{
	//��̬��������� ��̬���� �ǳٰ� ���� ���
	if (hero->getAd() > m->getAd()) { //�ڴ�hero->getAd()�ͷ����˶�̬
		cout << "Ӣ��սʤ�� ����" << endl;
	}
	else {
		cout << "Ӣ�۹��ˡ�" << endl;
	}
}

int main(void)
{
	Hero hero1;
	Monster mon1;

	//��д�ĳ���Ӣ��
	SuperHero hero2;

	BugHero hero3;


	//��ʼս��
	PlayerFight(&hero1, &mon1);

	PlayerFight(&hero2, &mon1); //Hero *hero = &hero2;

	PlayerFight(&hero3, &mon1);


	//ָ���������Ҫ����
	int a;
	int*p = NULL;

	p = &a;

	*p;


	//��̬������������Ҫ����
	//1 Ҫ�м̳С�
	//2 Ҫ��������д������麯��
	//3  ����ָ��(��������) ָ���������


	

	//int a = 10;

	cin >> a;

	//func(a); //

	if (a > 10)
	{
		cout << a << endl;
	}
	else {
		cout << "a ������10" << endl;
	}
	return 0;
}

/*
void func(int a);
void func(int a, int b);
*/