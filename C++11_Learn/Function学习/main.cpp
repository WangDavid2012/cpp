#include <iostream>
#include <functional>
#include <string>
using namespace std;
using std::placeholders::_1;

class Foo {
public:
	Foo(int num) : num_(num) {
		cout << "Foo construct:  " << num_ << " num_ addr:" << &num_ << endl;
	}
	//拷贝构造函数
	Foo(const Foo &f) {
		cout << "copy construct：" << f.num_ << " num_ addr:" << &num_ << endl;
		num_ = f.num_;
	}

	Foo & operator= (const Foo &f) {
		cout << "assign construct" << " num_ addr:" << &num_ << endl;
		num_ = f.num_;
		return *this;
	}
	~Foo() { cout << "Foo destruct： " << num_ << " num_ addr:" << &num_ << endl; }

	inline void print_add(int i) const { cout << num_ + i << endl; }

	int num_;
	int aaa[1024];
};



void my_printfadd(int i)
{
	cout << "It is my printfadd function" << endl;
}



void print_num(int i)
{
	std::cout << i << '\n';
}

class PrintNum {
public:
	void operator() (int i) const {
		cout << i << endl;
	}
};

typedef std::function<void(int)> fun_test;
void fun1(fun_test fun, int iput) {
	fun(iput);
}

//--------------test 1----------------
//99
//f_display is : class std::function < void __cdecl(int)>
//42
//f_display_42 is : class std::function<void __cdecl(void)>
void test1()
{
	cout << "--------------test 1----------------" << endl;
	std::function< void(int) > f_display = print_num;
	f_display(99);
	cout << "f_display is: " << typeid(f_display).name() << endl;

	std::function<void()> f_display_42 = []() { print_num(42); };
	f_display_42();
	cout << "f_display_42 is: " << typeid(f_display_42).name() << endl;
}

//--------------test 2----------------
//Foo construct : 100 num_ addr : 001CE934
//111
//Foo construct : 12345 num_ addr : 001CD2F8
//12367
//Foo destruct： 12345 num_ addr : 001CD2F8
//f_add_display is : class std::function<void __cdecl(class Foo const &, int)>
//Foo destruct： 100 num_ addr : 001CE934
void test2()
{
	cout << "--------------test 2----------------" << endl;
	const Foo foo(100);
	//这是一个普通的函数对象，有两个参数
	std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
// 	std::function<void(const Foo&, int)> f_add_display = &my_printfadd;
	getchar();
	f_add_display(foo, 11);
	getchar();
	f_add_display(12345, 22); // 12345调用构造函数，先生成一个Foo对象
	getchar();
	cout << "f_add_display is: " << typeid(f_add_display).name() << endl;
}

//--------------test 3----------------
//Foo construct : 200 num_ addr : 001CE934
//copy construct：200 num_ addr : 001CD928
//bbb is : class std::_Binder<struct std::_Unforced, void(__thiscall Foo::*)(int)const, class Foo const &, struct std::_Ph<1> const &>
//Foo destruct： 200 num_ addr : 001CD928
//Foo destruct： 200 num_ addr : 001CE934
void test3()
{
	cout << "--------------test 3----------------" << endl;
	const Foo foo2(200);
	//调用一次拷贝构造函数
	auto bbb = std::bind(&Foo::print_add, foo2, _1);
	cout << "bbb is: " << typeid(bbb).name() << endl;
}

//--------------test 4----------------
//Foo construct : 300 num_ addr : 001CE934
//copy construct：300 num_ addr : 001CD928
//以下会调用两次拷贝构造函数, 一次是生成临时对象，一次是属于f_add_display2_1
//copy construct：300 num_ addr : 001CC2BC
//copy construct：300 num_ addr : 0069250C
//Foo destruct： 300 num_ addr : 001CC2BC
//sizeof(f_add_display2_1) : 40
//bbb is : class std::_Binder<struct std::_Unforced, void(__thiscall Foo::*)(int)const, class Foo const &, struct std::_Ph<1> const &>
//f_add_display2_1 is : class std::function<void __cdecl(int)>
//Foo destruct： 300 num_ addr : 0069250C
//Foo destruct： 300 num_ addr : 001CD928
//Foo destruct： 300 num_ addr : 001CE934
void test4()
{
	cout << "--------------test 4----------------" << endl;
	//函数对象, 绑定到了Foo类的print_add
	const Foo foo4(300);

	//调用一次拷贝构造函数
	auto bbb = std::bind(&Foo::print_add, foo4, _1);
	cout << "以下会调用两次拷贝构造函数, 一次是生成临时对象，一次是属于f_add_display2_1" << endl;
	// store a call to a member function and object
	std::function<void(int)> f_add_display2_1 = bbb;
	cout << "sizeof(f_add_display2_1): " << sizeof(f_add_display2_1) << endl;
	cout << "bbb is: " << typeid(bbb).name() << endl;
	cout << "f_add_display2_1 is: " << typeid(f_add_display2_1).name() << endl;
}

//--------------test 5----------------
//Foo construct : 400 num_ addr : 00AFE9DC
//以下会调用两次拷贝构造函数, 一次是生成临时对象，一次是属于f_add_display2_2
//copy construct：400 num_ addr : 00AFD348
//copy construct：400 num_ addr : 02EFFBAC
//Foo destruct： 400 num_ addr : 00AFD348
//433
//444
//copy construct：400 num_ addr : 02F00D2C
//499
//f_add_display2_2 is : class std::function<void __cdecl(int)>
//hahah is : class std::function<void __cdecl(int)>
//Foo destruct： 400 num_ addr : 02F00D2C
//Foo destruct： 400 num_ addr : 02EFFBAC
//Foo destruct： 400 num_ addr : 00AFE9DC
void test5()
{
	cout << "--------------test 5----------------" << endl;
	const Foo foo5(400);
	// store a call to a member function and object
	cout << "以下会调用两次拷贝构造函数, 一次是生成临时对象，一次是属于f_add_display2_2" << endl;
	std::function<void(int)> f_add_display2_2 = std::bind(&Foo::print_add, foo5, _1);
	f_add_display2_2(33);
	f_add_display2_2(44);
	auto hahah = f_add_display2_2;
	hahah(99);
	cout << "f_add_display2_2 is: " << typeid(f_add_display2_2).name() << endl;
	cout << "hahah is: " << typeid(hahah).name() << endl;
}



//--------------test 6----------------
//Foo construct : 500 num_ addr : 001CE934
//544
//f_add_display3 is : class std::function < void __cdecl(int)>
//555
//f_add_display4 is : class std::function < void __cdecl(int)>
//18
//f_display_obj is : class std::function<void __cdecl(int)>
//Foo destruct： 500 num_ addr : 001CE934
void test6()
{
	cout << "--------------test 6----------------" << endl;
	const Foo foo3(500);
	// store a call to a member function and object ptr, 不会生成一个新的临时对象
	std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo3, _1);
	f_add_display3(44);
	cout << "f_add_display3 is: " << typeid(f_add_display3).name() << endl;

	std::function<void(int)> f_add_display4 = f_add_display3;
	f_add_display4(55);
	cout << "f_add_display4 is: " << typeid(f_add_display4).name() << endl;

	// store a call to a function object
	std::function<void(int)> f_display_obj = PrintNum();
	f_display_obj(18);
	cout << "f_display_obj is: " << typeid(f_display_obj).name() << endl;
}

//--------------test 7----------------
//Foo construct : 500 num_ addr : 008FEB54
//num_ : 500
//  f_num is : class std::function<int __cdecl(class Foo const &)>
//  Foo destruct： 500 num_ addr : 008FEB54
void test7()
{
	cout << "--------------test 7----------------" << endl;
	const Foo foo3(500);
	// store a call to a data member accessor
	std::function<int(Foo const&)> f_num = &Foo::num_;
	std::cout << "num_: " << f_num(foo3) << '\n';
	cout << "f_num is: " << typeid(f_num).name() << endl;
}









int main() 
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	system("pause");
	return 0;
}


