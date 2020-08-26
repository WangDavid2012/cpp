<<<<<<< HEAD
#include <iostream>

using namespace std;


// 关于显式调用的学习
// explicit函数的介绍!!!
// explicit函数的作用：explicit构造函数是用来防止隐式转换的
class Test1 {
public:
	Test1(int n) {  // 普通隐式的构造函数
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(显式)构造函数
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // 隐式调用其构造函数,成功
	//Test2 t2 = 12;  // 编译错误,不能隐式调用其构造函数
	Test2 t3(12);   // 显式调用成功
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
//接受一个参数的构造函数允许使用赋值语句隐式调用来初始化对象; 
//而explicit构造函数只能被显式调用!所以，输出的是short！
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
=======
锘�#include <iostream>

using namespace std;

// 鍏充簬鏄惧紡璋冪敤鐨勫涔�
// explicit鍑芥暟鐨勪粙缁�!!!
// explicit鍑芥暟鐨勪綔鐢細explicit鏋勯�犲嚱鏁版槸鐢ㄦ潵闃叉闅愬紡杞崲鐨�
class Test1 {
public:
	Test1(int n) {  // 鏅�氶殣寮忕殑鏋勯�犲嚱鏁�
		num = n;
	}
private:
	int num;
};

class Test2 {
public:
	explicit Test2(int n) {   //explicit(鏄惧紡)鏋勯�犲嚱鏁�
		num = n;
	}
private:
	int num;
};

int explicit_test() {
	Test1 t1 = 12;  // 闅愬紡璋冪敤鍏舵瀯閫犲嚱鏁�,鎴愬姛
	//Test2 t2 = 12;  // 缂栬瘧閿欒,涓嶈兘闅愬紡璋冪敤鍏舵瀯閫犲嚱鏁�
	Test2 t3(12);   // 鏄惧紡璋冪敤鎴愬姛
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
//鎺ュ彈涓�涓弬鏁扮殑鏋勯�犲嚱鏁板厑璁镐娇鐢ㄨ祴鍊艰鍙ラ殣寮忚皟鐢ㄦ潵鍒濆鍖栧璞�;
//鑰宔xplicit鏋勯�犲嚱鏁板彧鑳借鏄惧紡璋冪敤!鎵�浠ワ紝杈撳嚭鐨勬槸short锛�
int explicit_test2() {
	int n = 0;;
	Test a = n;
	return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
