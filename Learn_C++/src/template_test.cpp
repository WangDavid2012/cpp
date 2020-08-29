<<<<<<< HEAD
#include <iostream>
using namespace std;

template <class T>
T myadd(T a, T b)
{
	return a + b;
}
//µ÷ÓÃÄ£°åÊ±£¬ĞèÒªÊ×ÏÈÉú³ÉµÄÒ»¸ö¾ßÌåµÄº¯Êı
//ĞèÒªÍ¨¹ıÄ£°åÈ¥Éú³Éº¯Êı£¬È»ºóÔÙµ÷ÓÃ
void template_test()
{
	int a = 2, b = 4;
	char c1 = 'a';
	char c2 = 'b';
	myadd(a, b);				//»áÉú³ÉÒ»¸ömyadd(int,int)ÀàĞÍµÄº¯Êı
	myadd(c1, c2);				//»áÉú³ÉÒ»¸ömyadd(char,char)ÀàĞÍµÄº¯Êı	

}

//ÀàÄ£°åµÄ»ù±¾Óï·¨
template <class T>
class Person
{
	// public:
	// 	Person(T id, T age) :mId(id), mAge(age);
	// 
	// private:
	// 	T mId;
	// 	T mAge;
};

//template<class T>
//Person::Person(T id, T age)
//{
//	this->mAge = age;
//	this->mId = id;
//}




template<class T>
class A
{
public:
	A(T a)
	{
		this->a = a;
	}

	void printA()
	{
		cout << "a = " << a << endl;
	}
private:
	T a;
};


//¼Ì³ĞÄ£°åÀà£¬ Ö±½Ó¼Ì³ĞÒÑ¾­ÊµÀı»¯µÄÄ£°åÀà
//ÕâÃ´¼Ì³ĞÍêµÄBÀà£¬ BÀà´ËÊ±ÊÇÒ»¸öÆÕÍ¨Àà¡£
class B :public A<int>
{
public:
	B(int a, int b) : A<int>(a)
	{
		this->b = b;
	}

	void printB()
	{
		cout << "b = " << b << endl;
	}
private:
	int b;
};


//CÀà¼Ì³ĞµÄÊÇÒ»¸öÄ£°åÀà£¬Ã»ÓĞÊµÀı»¯£¬´ËÊ±CÀàÒÀÈ»ÊÇÒ»¸öÄ£°åÀà£¬
//±àÒëÆ÷ÔÚ¶ÑcÀà´¦ÀíÒÀÈ»ĞèÒª¶ş´Î±àÒë
template <class T>
class C :public A<T>
{
public:
	C(T a, T c) : A(a)
	{
		this->c = c;
	}

	void printC()
	{
		cout << "c = " << c << endl;
	}
private:
	T c;
};


//ÆÕÍ¨º¯Êı
void func(A<int> & a)
{
	a.printA();
}

//Ä£°åº¯Êı
template <class T>
void func2(A<T> &a)
{
	a.printA();
}


int template_test1(void)
{
	A<int> a(10);

	a.printA();

	func(a);
	func2<int>(a);


	A<double> a2(30.0);
	a2.printA();

	cout << " ------  " << endl;
	B b(100, 200);

	b.printB();
	cout << "-------- " << endl;
	C<int>  c(1000, 2000); //CÀàÊÇÒ»¸öÄ£°åÀà
	c.printC();
	return 0;
}



=======
ï»¿#include <iostream>
using namespace std;

template <class T>
T myadd(T a, T b)
{
	return a + b;
}
//è°ƒç”¨æ¨¡æ¿æ—¶ï¼Œéœ€è¦é¦–å…ˆç”Ÿæˆçš„ä¸€ä¸ªå…·ä½“çš„å‡½æ•°
//éœ€è¦é€šè¿‡æ¨¡æ¿å»ç”Ÿæˆå‡½æ•°ï¼Œç„¶åå†è°ƒç”¨
void template_test()
{
	int a = 2, b = 4;
	char c1 = 'a';
	char c2 = 'b';
	myadd(a, b);				//ä¼šç”Ÿæˆä¸€ä¸ªmyadd(int,int)ç±»å‹çš„å‡½æ•°
	myadd(c1, c2);				//ä¼šç”Ÿæˆä¸€ä¸ªmyadd(char,char)ç±»å‹çš„å‡½æ•°
}

//ç±»æ¨¡æ¿çš„åŸºæœ¬è¯­æ³•
template <class T>
class Person
{
	// public:
	// 	Person(T id, T age) :mId(id), mAge(age);
	//
	// private:
	// 	T mId;
	// 	T mAge;
};

//template<class T>
//Person::Person(T id, T age)
//{
//	this->mAge = age;
//	this->mId = id;
//}

template<class T>
class A
{
public:
	A(T a)
	{
		this->a = a;
	}

	void printA()
	{
		cout << "a = " << a << endl;
	}
private:
	T a;
};

//ç»§æ‰¿æ¨¡æ¿ç±»ï¼Œ ç›´æ¥ç»§æ‰¿å·²ç»å®ä¾‹åŒ–çš„æ¨¡æ¿ç±»
//è¿™ä¹ˆç»§æ‰¿å®Œçš„Bç±»ï¼Œ Bç±»æ­¤æ—¶æ˜¯ä¸€ä¸ªæ™®é€šç±»ã€‚
class B :public A<int>
{
public:
	B(int a, int b) : A<int>(a)
	{
		this->b = b;
	}

	void printB()
	{
		cout << "b = " << b << endl;
	}
private:
	int b;
};

//Cç±»ç»§æ‰¿çš„æ˜¯ä¸€ä¸ªæ¨¡æ¿ç±»ï¼Œæ²¡æœ‰å®ä¾‹åŒ–ï¼Œæ­¤æ—¶Cç±»ä¾ç„¶æ˜¯ä¸€ä¸ªæ¨¡æ¿ç±»ï¼Œ
//ç¼–è¯‘å™¨åœ¨å †cç±»å¤„ç†ä¾ç„¶éœ€è¦äºŒæ¬¡ç¼–è¯‘
template <class T>
class C :public A<T>
{
public:
	C(T a, T c) : A(a)
	{
		this->c = c;
	}

	void printC()
	{
		cout << "c = " << c << endl;
	}
private:
	T c;
};

//æ™®é€šå‡½æ•°
void func(A<int> & a)
{
	a.printA();
}

//æ¨¡æ¿å‡½æ•°
template <class T>
void func2(A<T> &a)
{
	a.printA();
}

int template_test1(void)
{
	A<int> a(10);

	a.printA();

	func(a);
	func2<int>(a);

	A<double> a2(30.0);
	a2.printA();

	cout << " ------  " << endl;
	B b(100, 200);

	b.printB();
	cout << "-------- " << endl;
	C<int>  c(1000, 2000); //Cç±»æ˜¯ä¸€ä¸ªæ¨¡æ¿ç±»
	c.printC();
	return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
