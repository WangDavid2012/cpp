#include <iostream>


// 命名空间的引入方式   
//引入命名空间的第一种方式
//第二种
using std::cout; //using 关键字 不是引入整个命名空间 而是引入命名空间一个变量
using std::endl; 


//第三种
using namespace  std; //using namespace 是引入整个命名空间

int aa;//是属于默认的全局作用域命名空间


//如何定义一个命名空间?
namespace namespaceA//定义一个命名空间 namespace是命名空间关键字类型， namespaceA 是命名空间的名字
{
	// namespace A 空间领域
	int a = 10;

	int b = 20;
}

namespace namespaceB
{
	int a = 20;

	namespace namespaceC
	{
		struct teacher
		{
			int id;
			char name[64];
		};
	}

	namespace namespaceD
	{
		struct teacher
		{

		};
	}
}



//使用自定义的命名空间
void test()
{
	//using namespaceA::a;//真个test（）函数领域中所有的a 默认都是 namespaceA中的a
	//using namespace namespaceA; //引入整个namespaceA空间
	cout << "A::a = " << namespaceA::a << endl;
	cout << "B::a = " << namespaceB::a << endl;
	//cout << "a = " << a << endl;


	//创建一个struct teacher的变量
	//using namespace namespaceB::namespaceC;//把namepaceC中的所有定义的遍历都引入
	//using namespaceB::namespaceC::teacher;

	//namespaceB::namespaceC::teacher t;
	using namespace namespaceB::namespaceC;
	teacher t;

}

int main(void)
{
	cout << "hello world" << endl;


	//第一种使用命名空间变量的方式
	std::cout << "你好" << std::endl;

	test();

	return 0;
}