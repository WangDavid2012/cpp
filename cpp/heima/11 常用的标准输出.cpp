#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include	<iomanip>

using namespace std;

/*
cout.put()
cout.write() //向输出缓冲区中写数据
cout.width()
cout.fill()
cout.setf(标记)


操作符、控制符
flush
endl
oct
dec
hex
setbase
setw
setfill
setprecision
*/

void test1()
{
	cout << "hello " << endl;
	cout.put('h').put('e').put('l') << endl;

	char *str = "hello wolrd";
	cout.write(str, strlen(str));
	cout << endl;
	cout.write(str, strlen(str) - 1);
	cout << endl;
}


void test2()
{
	/*
	//使⽤类成员函数
	cout << "<start>";
	cout.width(30); //设置接下来要输出的长度，是30
	cout.fill('*'); //将没有填充的多余的空间，填充成*
	cout.setf(ios::showbase);	//#include	<iomanip>
	cout.setf(ios::internal);	//设置
	cout << hex << 123 << "<End>\n";
	cout << endl;
	*/

	
	//使⽤ 操作符、控制符
	cout << "<Start>"
		<< setw(30)
		<< setfill('*')
		<< setiosflags(ios::showbase)	//基数
		<< setiosflags(ios::internal)
		<< hex
		<< 123
		<< "<End>\n"
		<< endl;

}

void test3()
{
#if 0
	int	a;
	cout << "input	a:";
	cin >> a;
	cout << "dec:" << dec << a << endl;	//以⼗进制形式输出整数
	cout << "hex:" << hex << a << endl;	//以⼗六进制形式输出整数a
	cout << "oct:" << setbase(8) << a << endl;	//以⼋进制形式输出整数a

	const char	*pt = "China";	//pt指向字符串"China"
	cout << setw(10) << pt << endl;	//指定域宽为,输出字符串
	cout << setfill('*') << setw(10) << pt << endl;	//指定域宽,输出字符串,空⽩处以'*'填>充
#endif

	double	pi = 22.0 / 7.0;	//计算pi值
	//按指数形式输出,8位⼩数
	cout << setiosflags(ios::scientific) << setprecision(8);
	cout << "pi=" << pi << endl;	//输出pi值
	cout << "pi=" << setiosflags(ios::fixed) << pi << endl;	//改为⼩数形式输出

	//cout << "pi=" << setprecision(4) << pi << endl;	//改为位⼩数
}

void test4()
{
	double a = 123.456, b = 3.14159, c = -3214.67;
	cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(2);
	cout << setw(10) << a << endl;
	cout << setw(10) << b << endl;
	cout << setw(10) << c << endl;

	//       123.45
	//          3.14
	//    -3214.67
}
int main(void)
{
	
	//test1();
	//test2();
	//test3(); 
	test4();
	return 0;
}