/**********************************************************************
3. 为什么要使用std::move

　　如果类X包含一个指向某资源的指针，在左值语义下，类X的赋值构造函数如下：

  复制代码
  X::X(const X& other)
  {
  // ....
  // 销毁资源
  // 复制other的资源，并使指针指向它
  // ...
  }
  复制代码
  　　应用代码如下，其中，tmp被赋给a之后，便不再使用。

	X tmp;
	// ...经过一系列初始化...
	X a = tmp;
	　如上，执行过程按照时间顺序如下:
	 首先执行一次默认构造函数(tmp申请资源)，再执行一次复制构造函数(a复制资源),
	 最后退出作用域时再执行一次析构函数(tmp释放资源)。
	 既然tmp迟早要被析构掉，在执行复制构造函数的时候，
	 a能不能将tmp的资源“偷“”过来，直接为我所用？

	  X::X(const X& other)
	  {
	  // 交换this和other的资源
	  }
	这样可以减少一次资源的创建和释放。这就是std::move所要实现的。
***********************************************************************/
#include <utility>
#include <iostream>
#include <string>
#include <vector>

void foo(const std::string &n)
{
    std::cout << "lvalue" << std::endl;
}

void foo(std::string &&n)
{
    std::cout << "rvalue" << std::endl;
}

void bar()
{
    foo("hello");                // rvalue 右值（只能在右边出现）
    std::string a = "world";
    foo(a);                      // lvalue（左值）
    foo(std::move(a));           // rvalue（强行转换）
}

int move_test()
{
    std::vector<std::string> a = { "hello", "world" };
    std::vector<std::string> b;
    //a[1].c_str();

    b.push_back("hello");
    b.push_back(std::move(a[1]));

    std::cout << "bsize: " << b.size() << std::endl;
    for (std::string &x : b)
        std::cout << x << std::endl;
    bar();
    return 0;
}
