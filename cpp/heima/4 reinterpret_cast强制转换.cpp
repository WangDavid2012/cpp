#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//动物的抽象类
class Animal
{
public:
	virtual void cry() = 0;// 纯虚函数
	virtual void doHome() = 0;// 纯虚函数
};

class Dog :public Animal {
public:
	Dog(int a){
		this->a = a;
	}
	virtual void cry()  {
		cout << "汪汪~~" << endl;
	}

	void doHome() {
		cout << "看家" << endl;
	}
	int a;
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


class Tree
{
public:
	Tree(){
		age = 10;
	}
	virtual void printT() {
		cout << "我是大叔" << endl;
	}
	int age1;
	int age; //在类的内存内部
};

int main(void)
{
	Animal *animal = new Dog(10);
   animal->cry();


	Tree* tree = reinterpret_cast<Tree*>(animal); //C++中 真正的强制转换
	if (tree != NULL) {
		cout << "转换成功" << endl;
		cout << tree->age << endl;
		tree->printT(); //vptr
	}
	else {
		cout << "转换失败" << endl;
	}
	
	return 0;
}