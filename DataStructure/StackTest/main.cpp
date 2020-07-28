/**************************************************************************
1.顺序栈的结构特点

顺序栈是用顺序存储结构的栈。嗯，贼官方啊，这句话是啥意思呢，
就是在内存中用一组地址连续的存储单元依次存放从栈底到栈顶的元素，
one by one，都在一块知道不。

栈的声明代码如下：
typedef struct {
	ElemType data[MaxSize];
	int top;　　　　//存放栈顶元素在数组中的下标
}SqStack;
开始学的时候真的好迷，干嘛把top叫做指针啦，它又没存放地址来着。。。。
不过能通过它来找到对应元素，也算是起了指针的作用吧。

在课本上采用了另一种描述：

就没有ElemType的数组定义了，而是用了两个指针

typedef struct {
	ElemType *base;
	ElemType *top;
	int MaxSize;    //当前已分配的空间
}SqStack;
*****************************************************************************/
#include <iostream>
#include <ctime>
using namespace std;

typedef int ElemType;
typedef int Status;


#define STACKINCREASEMENT 100

#define ERROR 0
#define OK    1

#define MaxSize 100

typedef struct {
	ElemType *base;
	ElemType *top;
	int stacksize;    //当前已分配的空间
}SqStack;

//使用数组定义的方式创建一个栈
//void InitStack(SqStack &s)
//{
//	s = (SqStack *)malloc(sizeof(SqStack));
//	s->top = 0;
//}
//使用数组方式的入栈操作
//int Push(SqStack &S, ElemType e) {
//	//将数据元素e压入栈顶
//	if (S.top == MaxSize)
//		return 0;
//	S.elem[S.top] = e;
//	S.top++;
//	return 1;
//}
//int Pop(SqStack &s, ElemType &e) {
//	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回1，否则返回0
//	if (S.top != 0)
//		return 0;
//	else {
//		S.top--;
//		e = S.elem[S.top];
//	}
//	return 1;
//}
//使用数组方式取栈顶元素
//int GetTop(SqStack &S, ElemType &e) {
//	//若栈不空，则用e返回栈顶元素并返回1，否则返回0
//	if (S.top == 0)
//		return 0;
//	e = S.elem[S.top - 1];
//	return 1;
//}
/****************************************************
函数功能：创建一个空栈
***/
Status InitStack(SqStack &S) 
{
	//构造一个空栈
	S.base = (ElemType *)malloc(MaxSize * sizeof(ElemType));
	if (!S.base)   //存储分配失败
		return 0;
	S.top = S.base;
	S.stacksize = MaxSize;
	return 1;
}//InitStack;

int Push(SqStack &S, ElemType e)
{
	//插入元素e为新的栈顶元素
	if ((S.top - S.base) >= S.stacksize) //栈满，追加储存空间
	{  
		S.base = (ElemType *)realloc(S.base,
			(S.stacksize + STACKINCREASEMENT) * sizeof(ElemType));

		if (!S.base)
			exit(0);    //存储空间分配失败
		S.top = S.base + S.stacksize;
		//此时stacksize还是原来的值木有变大，指向的是没有增加空间的栈顶
		S.stacksize += STACKINCREASEMENT;
	}
	*S.top++ = e;
	return 1;
}
//出栈操作
int Pop(SqStack &S, ElemType &e) 
{
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回1，否则返回0
	if (S.top == S.base)
		return 0;
	e = *--S.top;
	return 1;
}//Pop
//取栈顶元素
int GetTop(SqStack &S, ElemType &e) 
{
	//若栈不空，则用e返回栈顶元素并返回1，否则返回0
	if (S.top == S.base)
		return 0;
	e = *(S.top - 1);
	return 1;
}//GetTOP




/************************************************************************************************
引用学习：
&(引用)----------------出现在变量声明语句中位于变量左边时,表示声明的是引用.
&(取地址运算符)--------- 在给变量赋初值时出现在等号右边或在执行语句中作为一元运算符出现时
其实他们的区别可以用一句话概括：和类型在一起的是引用，和变量在一起的是取址。
	int a=3；
	int &b=a；        //引用
	int *p=&a;        //取地址

	int function(int &i)  //引用
	{
	}  //引用

**************************************************************************************************/
void swap1(int *x, int *y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void swap2(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

int main()
{
	//引用学习
	int N;
	int &rN = N;
	N = 1;
	cout << "rN的值为:" << rN << endl;
	cout << "&rN的值为：" << &rN << endl;

	//先看一下第2、3行的函数原型。两个函数的功能都是交换两个数。swap1的两个形参都是指针，而swap2的形参是两个引用。
	//再看一下第8行、第9行，调用swap1的时候传了两个地址给它（x=&a,y=&b），即x指向a的空间，y指向b的空间。
	//调用swap2的时候传了两个引用给它（x=a,y=b），即x只是a的一个别名，y是b的一个别名，实则都代表同一块空间。
	//函数调用的时候，引用相对于指针来说更高效、跟简便。因为指针传参的实质还是传值调用，copy地址需要开销，
	//而引用直接被编译器优化。有些时候需要二级指针的地方，使用指针的引用会使问题简化很多，
	//原文：https://blog.csdn.net/huecheung/article/details/39153341?utm_source=copy 
	//版权声明：本文为博主原创文章，转载请附上博文链接！
	int a = 10; 
	int b = 20;

	cout << "a = " << a << "  b =  " << b << endl;
	cout << "swap1 function the value!" << endl;
	swap1(&a,&b);
	cout << "a = " << a << "  b =  " << b << endl;

	cout << "swap2 function the value!" << endl;
	swap2(a,b);
	cout << "a = " << a << "  b =  " << b << endl;

	//栈的函数编写使用到了引用，以上是引用知识的复习

	//栈的相关操作开始
	SqStack s;
	int e;
	InitStack(s);

	Push(s,1);
	Push(s, 2);
	Push(s, 3);
	Push(s, 4);
	Push(s, 5);
	Push(s, 6);
	Push(s, 7);
	Push(s, 8);
	Push(s, 9);
	Push(s, 10);

	cout << "the stack value is ..." << endl;
	ElemType *ptmp = s.top;
	while (ptmp != s.base)
	{
		ptmp--;
		cout << *ptmp << " ";
	}
	cout << endl;
	Pop(s,e);
	cout << "the pop stack value is " << e << endl;
	getchar();
	return 0;
}