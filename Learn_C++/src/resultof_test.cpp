/*******************************************************
用于在编译的时候推导出一个可调用对象(函数,std::funciton或者重载了operator()
操作的对象等)的返回值类型.主要用于模板编写中.

我的理解：推断一个函数的返回值类型

***********************************************/

#include <iostream>
#include <type_traits>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int fn(int) { return int(); }									// function
typedef int(&fn_ref)(int);										// function reference
typedef int(*fn_ptr)(int);										// function pointer
struct fn_class { int operator()(int i) { return i; } };		// function-like class

int result_of_test1() {
	typedef std::result_of<decltype(fn)&(int)>::type A;  // int
	typedef std::result_of<fn_ref(int)>::type B;         // int
	typedef std::result_of<fn_ptr(int)>::type C;         // int
	typedef std::result_of<fn_class(int)>::type D;       // int

	std::cout << std::boolalpha;
	std::cout << "typedefs of int:" << std::endl;

	std::cout << "A: " << std::is_same<int, A>::value << std::endl;
	std::cout << "B: " << std::is_same<int, B>::value << std::endl;
	std::cout << "C: " << std::is_same<int, C>::value << std::endl;
	std::cout << "D: " << std::is_same<int, D>::value << std::endl;

	return 0;
}
//输出结果:
//typedefs of int :
//	A : true
//	B : true
//	C : true
//	D : true




struct Person
{
	string name;
	int age;
	string city;
};

vector<Person> vt = {
	{ "aa",20,"shanghai" },
	{ "bb",25,"beijing" },
	{ "cc",20,"nanjing" },
	{ "dd",25,"nanjing" }
};

//Group_by函数
template<typename Fn>
multimap<typename result_of<Fn(Person)>::type, Person> GroupBy(const vector<Person>& vt, const Fn& keySelect)
{
	typedef typename result_of<Fn(Person)>::type key_type;
	multimap<key_type, Person> map;
	for_each(vt.begin(), vt.end(),
		[&](const Person& p) {
		map.insert(make_pair(keySelect(p), p));
	});
	return map;
}

int result_of_test2()
{
	//按年龄分组
	auto res = GroupBy(vt, [](const Person& p) { return p.age; });
	//按城市分组
	auto res1 = GroupBy(vt, [](const Person& p) { return p.city; });

	//打印结果
	cout << "----------group by age:---------------" << endl;
	for_each(res.begin(), res.end(), [](decltype(res)::value_type & p) {
		cout << p.second.name << " " << p.second.city << "  " << p.second.age << endl;
	});
	cout << "----------group by city:---------------" << endl;
	for_each(res1.begin(), res1.end(), [](decltype(res1)::value_type & p) {
		cout << p.second.name << " " << p.second.city << "  " << p.second.age << endl;
	});
	return 0;
}