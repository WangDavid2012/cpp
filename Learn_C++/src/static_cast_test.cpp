<<<<<<< HEAD
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
=======
锘�#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void static_cast_test(void)
{
	double PI = 3.14159265;

	//int num = PI;
	int num2 = (int)PI; //C璇█鐨勮浆鎹㈡柟寮�
						//static_cast 澧炲姞鍙鎬э紝浠ｈ〃鏅�氱被鍨嬬殑寮哄埗杞崲锛�
						//static_cast 瀹為檯涓婃槸鍙堢紪璇戝櫒鍦ㄧ紪璇戠殑鏃跺�欏氨宸茬粡灏哖I瑙ｉ噴鎴恘um绫诲瀷浜�
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

//鍔ㄧ墿鐨勬娊璞＄被
class Animal
{
public:
	virtual void cry() = 0;// 绾櫄鍑芥暟
	virtual void doHome() = 0;// 绾櫄鍑芥暟
};

class Dog :public Animal {
public:
	virtual void cry() {
		cout << "姹豹~~" << endl;
	}

	void doHome() {
		cout << "鐪嬪" << endl;
	}
};

class Cat :public Animal {
public:
	virtual void cry() {
		cout << "鍠靛柕~~" << endl;
	}
	void doHome() {
		cout << "鎶撹�侀紶" << endl;
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
		cout << "杞崲鎴愬姛" << endl;
		dog->cry();
		dog->doHome();
	}
	else {
		cout << "杞崲澶辫触" << endl;
	}
	//dynamic _cast 鏄皢鐖剁被杞崲鎴愬瓙绫汇�傝鑰佸瓙鍙樻垚鍎垮瓙銆�
	//璁╁瓙绫绘寚閽堟墽琛岀埗绫荤殑瀵硅薄銆�

	Cat *cat = dynamic_cast<Cat*>(animal);
	//鍑嗗璇曞浘璁╀竴鍙嫍鍙樻垚涓�鍙尗
	if (cat != NULL) {
		cout << "杞崲鎴愬姛" << endl;
		cat->cry();
		cat->doHome();
	}
	else {
		cout << "杞崲澶辫触" << endl;
	}

	A *ap = new A;
	B *bp = dynamic_cast<B*>(ap);
	if (bp != NULL) {
		bp->func();
	}
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
