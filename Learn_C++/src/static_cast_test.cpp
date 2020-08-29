<<<<<<< HEAD
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void static_cast_test(void)
{
	double PI = 3.14159265;

	//int num = PI;
	int num2 = (int)PI; //CÓïÑÔµÄ×ª»»·½Ê½
						//static_cast Ôö¼Ó¿É¶ÁĞÔ£¬´ú±íÆÕÍ¨ÀàĞÍµÄÇ¿ÖÆ×ª»»£¬
						//static_cast Êµ¼ÊÉÏÊÇÓÖ±àÒëÆ÷ÔÚ±àÒëµÄÊ±ºò¾ÍÒÑ¾­½«PI½âÊÍ³ÉnumÀàĞÍÁË
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

//¶¯ÎïµÄ³éÏóÀà
class Animal
{
public:
	virtual void cry() = 0;// ´¿Ğéº¯Êı
	virtual void doHome() = 0;// ´¿Ğéº¯Êı
};

class Dog :public Animal {
public:
	virtual void cry() {
		cout << "ÍôÍô~~" << endl;
	}

	void doHome() {
		cout << "¿´¼Ò" << endl;
	}
};

class Cat :public Animal {
public:
	virtual void cry() {
		cout << "ß÷ß÷~~" << endl;
	}
	void doHome() {
		cout << "×¥ÀÏÊó" << endl;
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
		cout << "×ª»»³É¹¦" << endl;
		dog->cry();
		dog->doHome();
	}
	else {
		cout << "×ª»»Ê§°Ü" << endl;
	}
	//dynamic _cast ÊÇ½«¸¸Àà×ª»»³É×ÓÀà¡£ÈÃÀÏ×Ó±ä³É¶ù×Ó¡£
	//ÈÃ×ÓÀàÖ¸ÕëÖ´ĞĞ¸¸ÀàµÄ¶ÔÏó¡£

	Cat *cat = dynamic_cast<Cat*>(animal);
	//×¼±¸ÊÔÍ¼ÈÃÒ»Ö»¹·±ä³ÉÒ»Ö»Ã¨
	if (cat != NULL) {
		cout << "×ª»»³É¹¦" << endl;
		cat->cry();
		cat->doHome();
	}
	else {
		cout << "×ª»»Ê§°Ü" << endl;
	}

	A *ap = new A;
	B *bp = dynamic_cast<B*>(ap);
	if (bp != NULL) {
		bp->func();
	}
}
=======
ï»¿#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void static_cast_test(void)
{
	double PI = 3.14159265;

	//int num = PI;
	int num2 = (int)PI; //Cè¯­è¨€çš„è½¬æ¢æ–¹å¼
						//static_cast å¢åŠ å¯è¯»æ€§ï¼Œä»£è¡¨æ™®é€šç±»å‹çš„å¼ºåˆ¶è½¬æ¢ï¼Œ
						//static_cast å®é™…ä¸Šæ˜¯åˆç¼–è¯‘å™¨åœ¨ç¼–è¯‘çš„æ—¶å€™å°±å·²ç»å°†PIè§£é‡Šæˆnumç±»å‹äº†
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

//åŠ¨ç‰©çš„æŠ½è±¡ç±»
class Animal
{
public:
	virtual void cry() = 0;// çº¯è™šå‡½æ•°
	virtual void doHome() = 0;// çº¯è™šå‡½æ•°
};

class Dog :public Animal {
public:
	virtual void cry() {
		cout << "æ±ªæ±ª~~" << endl;
	}

	void doHome() {
		cout << "çœ‹å®¶" << endl;
	}
};

class Cat :public Animal {
public:
	virtual void cry() {
		cout << "å–µå–µ~~" << endl;
	}
	void doHome() {
		cout << "æŠ“è€é¼ " << endl;
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
		cout << "è½¬æ¢æˆåŠŸ" << endl;
		dog->cry();
		dog->doHome();
	}
	else {
		cout << "è½¬æ¢å¤±è´¥" << endl;
	}
	//dynamic _cast æ˜¯å°†çˆ¶ç±»è½¬æ¢æˆå­ç±»ã€‚è®©è€å­å˜æˆå„¿å­ã€‚
	//è®©å­ç±»æŒ‡é’ˆæ‰§è¡Œçˆ¶ç±»çš„å¯¹è±¡ã€‚

	Cat *cat = dynamic_cast<Cat*>(animal);
	//å‡†å¤‡è¯•å›¾è®©ä¸€åªç‹—å˜æˆä¸€åªçŒ«
	if (cat != NULL) {
		cout << "è½¬æ¢æˆåŠŸ" << endl;
		cat->cry();
		cat->doHome();
	}
	else {
		cout << "è½¬æ¢å¤±è´¥" << endl;
	}

	A *ap = new A;
	B *bp = dynamic_cast<B*>(ap);
	if (bp != NULL) {
		bp->func();
	}
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
