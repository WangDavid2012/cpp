#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//使用异常的方式进行处理


void my_strcpy1(char *dst, char *from) {
	if (dst == NULL) {
		throw 1; //1 代表目的地址有问题
	}
	else if (from == NULL) {
		throw 2; //2 代表源地址有问题
	}

	if (*from == 'a') {
		throw 3; //代表copy过程出现问题
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}


void my_strcpy2(char* dst, char *from) 
{
	if (dst == NULL) {
		throw "目的地址有问题"; //1 代表目的地址有问题
	}
	else if (from == NULL) {
		throw "源地址有问题"; //2 代表源地址有问题
	}

	if (*from == 'a') {
		throw "copy过程出现问题"; //代表copy过程出现问题
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}

//目的地址有问题的异常类型
class BadDstAddrType{};
class BadSrcAddrType{};
class BadProcessAddrType{
public:
	BadProcessAddrType()
	{
		cout << "BadProcessAddrType().." << endl;
	}
	BadProcessAddrType(const BadProcessAddrType & obj)
	{
		cout << "BadProcessAddrType(const BadProcessAddrType &)..." << endl;
	}
	void print() {
		cout << "copy过程出现了异常" << endl;
	}
	~BadProcessAddrType(){
		cout << "~BadProcessAddrType()..." << endl;
	}
};

void my_strcpy3(char *dst, char *from)
{
	if (dst == NULL) {
		throw BadDstAddrType(); //1 代表目的地址有问题
	}
	else if (from == NULL) {
		throw BadSrcAddrType(); //2 代表源地址有问题
	}

	if (*from == 'a') {
		//throw new BadProcessAddrType(); //在抛出这个BadProcessAddrType() 会创建一个匿名对象 
		throw BadProcessAddrType();
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';
}

int main(void)
{
	char buf1[] = "a234567";
	char buf2[128] = { 0 };

	try {
		my_strcpy3(buf2, buf1);
	}
	catch (int e)
	{
		cout << "捕获到异常代码e = " << e << endl;
	}
	catch (char *e)
	{
		cout << "捕获到char*类型异常e = " << e << endl;
	}
	//catch (BadProcessAddrType e) { //BadProcessAddrType e = 匿名对象temp //在捕获的时候，如果用一个元素捕获
													//会发生拷贝构造，异常对象e和被抛出来的匿名对象不是一个对象
													//会有深拷贝和浅拷贝的风险
//		cout << "捕获到了BadProcessAddrType 异常类型e  " << endl;
//		e.print();
//	}
	catch (BadProcessAddrType *e) { //此时那个匿名对象已经被释放了，e是一个野指针
		cout << "捕获到了BadProcessAddrType* 异常类型e" << endl;
		delete e; //如果抛出的异常类型是new出来的，需要显示的delete掉
	}
	catch (BadProcessAddrType &e) { //1 普通元素类型的异常捕获，不能够跟 引用捕获同时存在。
		cout << "捕获到了 BadProcessAddrType & 异常类型" << endl;
		//编译器发现使用引用捕获的，那么不会立刻释放掉匿名对象， 而是在异常处理完之后，才把e释放。
		//可以理解为 BadProcessAddrType &e = BadProcessAddrType()
	}
	catch(...) 
	{
		cout << "捕获到未知异常" << endl;
	}
}

#if 0
int my_strcpy(char *dst, char *from)
{
	if (dst == NULL) {
		return 1; //1 代表目的地址有问题
	}
	else if (from == NULL) {
		return 2; //2 代表源地址有问题
	}

	if (*from == 'a') {
		return 3; //代表copy过程出现问题
	}


	while (*from != '\0') {
		*dst = *from;
		dst++;
		from++;
	}
	*dst = '\0';

	return 0;
}

//传统的捕获错误方法
int main(void)
{
	char buf1[] = "a234567";
	char buf2[128] = { 0};
	int ret = 0;

	ret = my_strcpy(buf2, buf1);
	if (ret != 0) {
		switch (ret)
		{
		case 1:
			cout << "目的地址有问题" << endl;
			break;
		case 2:
			cout << "原地址有问题" << endl;

			break;
		case 3:
			cout << "拷贝过程有问题" << endl;

			break;
		default:
			break;
		}
	}
	else {
		cout << "buf2 = " << buf2 << endl;
	}

	
	return 0;
}
#endif