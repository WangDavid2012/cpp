#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"

using namespace std;

int main(void)
{
	Animal *ap = new Dog;
	//调用架构函数
	AnimalVoice(ap);
	delete ap;

	ap = new Cat;

	AnimalVoice(ap);
	delete ap;
	
	return 0;
}