#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void static_cast_test(void)
{
	double PI = 3.14159265;

	//int num = PI;
	int num2 = (int)PI; //C语言的转换方式
						//static_cast 增加可读性，代表普通类型的强制转换，
						//static_cast 实际上是又编译器在编译的时候就已经将PI解释成num类型了
	int num3 = static_cast<int>(PI);

	cout << "num2" << num2 << endl;
	cout << "num3" << num3 << endl;
}



class A
{
public:
	virtual void func() {
		cout << "A" << endl;
	}
	int a;
};

class B :public A
{
public:
	virtual void func() {
		cout << "B" << endl;
	}
	int b;
};

//动物的抽象类
class Animal
{
public:
	virtual void cry() = 0;// 纯虚函数
	virtual void doHome() = 0;// 纯虚函数
};

class Dog :public Animal {
public:
	virtual void cry() {
		cout << "汪汪~~" << endl;
	}

	void doHome() {
		cout << "看家" << endl;
	}
};

class Cat :public Animal {
public:
	virtual void cry() {
		cout << "喵喵~~" << endl;
	}
	void doHome() {
		cout << "抓老鼠" << endl;
	}
};



void dynamic_cast_test(void)
{
	Animal *animal = NULL;
	animal = new Dog;
	animal->cry();

	Dog *dog = new Dog;
	cout << " ----- " << endl;

	dog = dynamic_cast<Dog*> (animal);
	if (dog != NULL) {
		cout << "转换成功" << endl;
		dog->cry();
		dog->doHome();
	}
	else {
		cout << "转换失败" << endl;
	}
	//dynamic _cast 是将父类转换成子类。让老子变成儿子。
	//让子类指针执行父类的对象。

	Cat *cat = dynamic_cast<Cat*>(animal);
	//准备试图让一只狗变成一只猫
	if (cat != NULL) {
		cout << "转换成功" << endl;
		cat->cry();
		cat->doHome();
	}
	else {
		cout << "转换失败" << endl;
	}

	A *ap = new A;
	B *bp = dynamic_cast<B*>(ap);
	if (bp != NULL) {
		bp->func();
	}
}