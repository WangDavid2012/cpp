#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Dog
{
public:
	void eat(char *food)
	{
		cout << name << "吃了" << food << endl;
	}
	char name[64];
};

//面向过程是写一个过程，
void eat(Dog &dog, char *food)
{
	cout << dog.name << "吃了" << food << endl;
}

int main(void)
{
	//如果是面向对象
	Dog dog;

	strcpy(dog.name, "狗");
	//通过对象作为主驱动
	dog.eat("翔");

	//如果是面向过程
	eat(dog, "翔");
	
	return 0;
}