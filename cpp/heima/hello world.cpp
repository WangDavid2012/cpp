// C语言

#if 0
#include <stdio.h>

int main(void)
{
	int a=  0;
	printf("hello world\n"); //对黑屏幕输出

	printf("请输入一个数字");
	scanf("%d", &a);

	return 0;


}
#endif

#include <iostream>
//命名空间的
using namespace std; //iostream 有一个命名空间 叫std ， std{
	//																							cout
	//																					}
//  如果想使用cout endl 等等这些标准输出 一定要引入 std命名空间
// using namespace  std;


int main(void)
{
	int a = 0;

	cout << "hello world" <<endl; //cout 就是一个标准的输出， 就是黑屏幕
													//endl 他在C++中就是\n

	cout << "请输出一个数字" << endl;

	cin >> a;


	cout << "a = " << a << endl;

	return 0;
}