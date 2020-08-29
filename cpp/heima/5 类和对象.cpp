#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//定义一个类
struct  Hero
{
public:
	int sex;
	char name[64];

};

//定义一个类的关键字
class AdvHero //定义一个类名
{
public: //访问控制符  访问权限
	int sex;
	char name[64]; //成员变量


	//成员函数
	void printHero()
	{
		cout << "性别:" << sex << endl;
		cout << "姓名" << name << endl;
	}
};

//定义一个animal类
class Animal{
public:
	char color[64];
	char kind[64];

	//拥有写字的成员函数
	void write()
	{
		cout << kind << "开始写字了" << endl;
	}

	//拥有跑步的方法
	void run()
	{
		cout << kind << "跑步了" << endl;
	}
};

int main(void)
{
	struct Hero chunBro;

	chunBro.sex = 1;
	strcpy(chunBro.name, "chunBro");


	AdvHero gailun; //通过AdvHero类 创建一个对象。
	gailun.sex = 1;
	strcpy(gailun.name, "盖伦");


	/*
	cout << "性别" << gailun.sex << endl;
	cout << "姓名:" << gailun.name << endl;
	*/

	gailun.printHero();//通过对象 直接调用成员函数


	Animal dog;
	Animal sheep;

	strcpy(dog.kind, "狗");
	strcpy(dog.color, "黄色");

	dog.run();
	dog.write();

	strcpy(sheep.kind, "羊");
	strcpy(sheep.color, "白");

	sheep.run();
	sheep.write();



	return 0;
}