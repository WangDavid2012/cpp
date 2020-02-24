// C++11 function
#include <functional>
#include <iostream>

using namespace std;


void print_num(int i)
{
	std::cout << i << '\n';
}
void testFunctionTpl()
{
	// templet 匿名函数
	std::function<void(const int&, const int&)>getSum = [&](const int &nI1, const int &nI2)
	{
		int nSum = nI1 + nI2;
		std::cout << nSum << endl;
	};
	getSum(8, 9);

	//  lambda
	std::function<void()> f_display_42 = []() { print_num(42); };
	f_display_42();


	//********************* 测试成员函数 begin*********************//
	class TestClass
	{
	public:
		TestClass(int i) : m_nI(i) {}
		~TestClass() {}
		void testMemberFunc(int i) const { std::cout << m_nI + i << endl; }
		int  testResultFun(int i) const { return m_nI + i; }
		void testBindFun(int num) const { std::cout << m_nI + num << endl; }
		int m_nI;
	};


	std::function<void(const TestClass&, int)> testMemberFunc = &TestClass::testMemberFunc;
	const TestClass oTestObject(100);
	// 传对象
	testMemberFunc(oTestObject, 100);
	// 会根据模板构造对象
	testMemberFunc(300, 100);
	//  返回值成员函数
	std::function<int(const TestClass&, int)> testResultFun = &TestClass::testResultFun;
	int nRet = testResultFun(oTestObject, 100);
	std::cout << nRet << endl;
	// 成员变量
	std::function<int(const TestClass&)> f_num = &TestClass::m_nI;
	std::cout << "m_nI: " << f_num(oTestObject) << '\n';

	// 对象形式调用成员函数
	using std::placeholders::_1; // 占位符
	std::function<void(int)> testBindFun = std::bind(&TestClass::testBindFun, oTestObject, _1);
	testBindFun(222);

	// 指针形式调用成员函数
	std::function<void(int)> testBindFun2 = std::bind(&TestClass::testBindFun, &oTestObject, _1);
	testBindFun2(333);
	//********************* 测试成员函数 end*********************//

	//********************* 测试普通函数 begin*********************//
		// 绑定普通函数
	std::function<void()> f_display_31337 = std::bind(print_num, 31337);
	f_display_31337();
	//********************* 测试普通函数 end*********************//

	// bad_function_call
	std::function<int()> f = nullptr;
	try {
		f();
	}
	catch (const std::bad_function_call& e) {
		std::cout << e.what() << '\n';
	}

}
int main()
{
	testFunctionTpl();
	int i = 0;
}