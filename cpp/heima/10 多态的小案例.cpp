#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Hero
{
public:
	//当前Hero的战斗力是10
	virtual int getAd(){
		return 10;
	}
};

//超级英雄
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

//怪兽
class Monster
{
public:
	int getAd()
	{
		return 30;
	}
};

//战斗的函数
//先写的 战斗函数， 通过用父类的指针作为参数
//多态具有调用未来的 意义。
void PlayerFight(Hero *hero, Monster *m)
{
	//多态这种现象较 动态联编 是迟绑定 或是 晚绑定
	if (hero->getAd() > m->getAd()) { //在此hero->getAd()就发生了多态
		cout << "英雄战胜了 叫兽" << endl;
	}
	else {
		cout << "英雄挂了。" << endl;
	}
}

int main(void)
{
	Hero hero1;
	Monster mon1;

	//后写的超级英雄
	SuperHero hero2;

	BugHero hero3;


	//开始战斗
	PlayerFight(&hero1, &mon1);

	PlayerFight(&hero2, &mon1); //Hero *hero = &hero2;

	PlayerFight(&hero3, &mon1);


	//指针的三个必要条件
	int a;
	int*p = NULL;

	p = &a;

	*p;


	//多态发生的三个必要条件
	//1 要有继承。
	//2 要有子类重写父类的虚函数
	//3  父类指针(或者引用) 指向子类对象。


	

	//int a = 10;

	cin >> a;

	//func(a); //

	if (a > 10)
	{
		cout << a << endl;
	}
	else {
		cout << "a 不大于10" << endl;
	}
	return 0;
}

/*
void func(int a);
void func(int a, int b);
*/