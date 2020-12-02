#include <iostream>     // std::cout
#include <iterator>     // std::advance
#include <list>         // std::list

/*
	advance()函数用法
	参数1 ---迭代器的引用
	参数2----迭代器增加的个数
	理解：迭代器是list的一个参数
*/
int iterator_test() {
	std::list<int> mylist;
	for (int i = 0; i < 10; i++)
		mylist.push_back(i * 10);
	std::list<int>::iterator it = mylist.begin();
	std::advance(it, 5);
	std::cout << "The sixth element in mylist is: " << *it << '\n';

	return 0;
}

int distance_test() {
	std::list<int> mylist;
	for (int i = 0; i < 10; i++) mylist.push_back(i * 10);

	std::list<int>::iterator first = mylist.begin();
	std::list<int>::iterator last = mylist.end();

	std::cout << "The distance is: " << std::distance(first, last) << '\n';

	return 0;
}
//————————————————------------
//版权声明：本文为CSDN博主「Donghao_Y」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/baidu_34884208/article/details/88362823