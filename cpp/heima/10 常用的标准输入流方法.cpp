#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
cin.get() //一次只能读取一个字符
cin.get(一个参数) //读一个字符
cin.get(三个参数) //可以读字符串
cin.getline()
cin.ignore()
cin.putback()
*/

//cin的operator>>操作符 //根据回车来刷新缓冲区  根据空格来隔离每个变量的内容
void test1()
{
	int myInt;
	long myLong;

	char buf[128] = { 0 };

	cin >> myInt;
	cin >> myLong;
	cin >> buf;

	cout << "myInt: " << myInt << endl;
	cout << "myLong: " << myLong << endl;
	cout << "buf: " << buf << endl;
}


//cin.get()方法
void test2()
{
	char ch;

	//cin.get()如果读到的不是EOF标识符，那么会永远的阻塞等待
	//从键盘来讲ctrl+z 代表EOF标识符
	while ((ch = cin.get() )!= EOF) {
		cout << ch << endl;
	}
}

void test3()
{
	char a, b, c;

	char buf[10] = { 0 };

	cout << "从输入缓冲区去读取数据，如果缓冲区中没有数据，就阻塞" << endl;
	//cin.get(a); //从输入缓冲区去读取数据，如果有就给a
	//cin.get(b);
	//cin.get(c);
	//cin.get(a).get(b).get(c);


	//cout << "a  =" << a << endl;
	//cout << "b  =" << b<< endl;
	//cout << "c  =" << c<< endl;

	cin.get(buf, 10, ' ');

	cout << buf << endl;
}

//cin.getline()
void test4()
{
	char buf[128] = { 0 };
	cout << "请输入一个字符串 aa bb cc dd" << endl;
	cin.getline(buf, 128); //从输入缓冲区中读数据到buf中，最多读128 ，知道遇到\n为止

	cout << "buf:" <<buf << endl;
}


//cin.ignore()
void test5()
{
	char buf1[128];
	char buf2[128];

	cout << "请输入一个字符串 aa  bb cc dd" << endl;
	cin >> buf1; //aa
	cin.ignore(2);
	cin.getline(buf2, 128);// bb cc dd

	cout << "buf1:" << buf1 << endl;
	cout << "buf2:" << buf2 << endl;

}

//cin.putback()
void test6()
{
	cout << "请输入一个数字或者字符串" << endl;
	char ch;
	ch = cin.get(); //从输入缓冲区去读一个字符
	if ((ch >= '0') && ch <= '9') {
		cout << "输入的是一个数字" << endl;
		int num;
		//此时数字第一个字符已经读出来了。 需要将ch放回到输入缓冲区
		cin.putback(ch); //将ch仍会缓冲区， 位置就缓冲区的头部。
		cin >> num;

		cout << "num =" << num << endl;
	}
	else {
		cout << "输入的是一个字符串" << endl;
		char buf[128] = { 0 };
		//cin.putback(ch);
		cin.getline(buf, 128);

		cout << "buf:" << buf << endl;
	}
}

int main(void)
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
	
	return 0;
}