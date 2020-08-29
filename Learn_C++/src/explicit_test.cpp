<<<<<<< HEAD
#include <iostream>

using namespace std;


// ¹ØÓÚÏÔÊ½µ÷ÓÃµÄÑ§Ï°
// explicitº¯ÊıµÄ½éÉÜ!!!
// explicitº¯ÊıµÄ×÷ÓÃ£ºexplicit¹¹Ôìº¯ÊıÊÇÓÃÀ´·ÀÖ¹ÒşÊ½×ª»»µÄ
class Test1 {
public:
	Test1(int n) {  // ÆÕÍ¨ÒşÊ½µÄ¹¹Ôìº¯Êı
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(ÏÔÊ½)¹¹Ôìº¯Êı
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // ÒşÊ½µ÷ÓÃÆä¹¹Ôìº¯Êı,³É¹¦
	//Test2 t2 = 12;  // ±àÒë´íÎó,²»ÄÜÒşÊ½µ÷ÓÃÆä¹¹Ôìº¯Êı
	Test2 t3(12);   // ÏÔÊ½µ÷ÓÃ³É¹¦
	return 0;
}
class Test {
public:
	Test() :a(0) {
		cout << "void\n";
	}
	explicit Test(int i) :a(i) {
		cout << "int\n";
	}
	Test(short s) :a(s) {
		cout << "short\n";
	}
	Test & operator=(int n) {
		a = n;
		cout << "operator = ";
	}
private:
	int a;
};
//½ÓÊÜÒ»¸ö²ÎÊıµÄ¹¹Ôìº¯ÊıÔÊĞíÊ¹ÓÃ¸³ÖµÓï¾äÒşÊ½µ÷ÓÃÀ´³õÊ¼»¯¶ÔÏó; 
//¶øexplicit¹¹Ôìº¯ÊıÖ»ÄÜ±»ÏÔÊ½µ÷ÓÃ!ËùÒÔ£¬Êä³öµÄÊÇshort£¡
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
=======
ï»¿#include <iostream>

using namespace std;

// å…³äºæ˜¾å¼è°ƒç”¨çš„å­¦ä¹ 
// explicitå‡½æ•°çš„ä»‹ç»!!!
// explicitå‡½æ•°çš„ä½œç”¨ï¼šexplicitæ„é€ å‡½æ•°æ˜¯ç”¨æ¥é˜²æ­¢éšå¼è½¬æ¢çš„
class Test1 {
public:
	Test1(int n) {  // æ™®é€šéšå¼çš„æ„é€ å‡½æ•°
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(æ˜¾å¼)æ„é€ å‡½æ•°
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // éšå¼è°ƒç”¨å…¶æ„é€ å‡½æ•°,æˆåŠŸ
	//Test2 t2 = 12;  // ç¼–è¯‘é”™è¯¯,ä¸èƒ½éšå¼è°ƒç”¨å…¶æ„é€ å‡½æ•°
	Test2 t3(12);   // æ˜¾å¼è°ƒç”¨æˆåŠŸ
	return 0;
}
class Test {
public:
	Test() :a(0) {
		cout << "void\n";
	}
	explicit Test(int i) :a(i) {
		cout << "int\n";
	}
	Test(short s) :a(s) {
		cout << "short\n";
	}
	Test & operator=(int n) {
		a = n;
		cout << "operator = ";
	}
private:
	int a;
};
//æ¥å—ä¸€ä¸ªå‚æ•°çš„æ„é€ å‡½æ•°å…è®¸ä½¿ç”¨èµ‹å€¼è¯­å¥éšå¼è°ƒç”¨æ¥åˆå§‹åŒ–å¯¹è±¡;
//è€Œexplicitæ„é€ å‡½æ•°åªèƒ½è¢«æ˜¾å¼è°ƒç”¨!æ‰€ä»¥ï¼Œè¾“å‡ºçš„æ˜¯shortï¼
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
