#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// 定义一个锦囊的方法 是一个函数指针，类似于c++的纯虚函数
typedef void(TIPS_FUNC)(void);


//写一个锦囊的结构体
struct tips
{
	char from[64]; //这个锦囊是谁写的
	char to[64]; //写给谁的
	TIPS_FUNC *fp; //具体锦囊的内容
};


//写一个供赵云调用的架构函数
void open_tips(struct tips * tp)
{
	cout << "打开了锦囊" << endl;
	cout << "此锦囊是由" << tp->from << ", 写给" << tp->to << endl;
	cout << "内容是" << endl;
	tp->fp();//拆开锦囊，调用具体锦囊的方法
}

//实现一个一个的锦囊  //类似于实现一个纯虚函数
void tips_1(void)
{
	cout << "一到东吴就大张旗鼓找乔国老" << endl;
}

void tips_2(void)
{
	cout << "骗刘备 操作压境" << endl;
}

void tips_3(void)
{
	cout << "找孙尚香求救" << endl;
}

void tips_4(void)
{
	cout << "你们就死在东吴把" << endl;
}

struct tips* create_tips(char *from, char *to, TIPS_FUNC *fp)
{
	struct tips *tp = (struct tips*)malloc(sizeof(struct tips));
	if (tp == NULL) {
		return NULL;
	}
	strcpy(tp->from, from);
	strcpy(tp->to, to);
	//注册回调函数
	tp->fp = fp; //给拥有函数指针的结构体  函数指针变量 赋值 就是 注册回调函数

	return tp;
}

void destory_tips(struct tips * tp)
{
	if (tp != NULL) {
		free(tp);
	}
}

int main(void)
{
	//诸葛亮去写锦囊
	struct tips * tp1 = create_tips("孔明", "赵云", tips_1);
	struct tips * tp2 = create_tips("孔明", "赵云", tips_2);
	struct tips * tp3 = create_tips("孔明", "赵云", tips_3);
	struct tips *tp4= create_tips("庞统", "赵云", tips_4);


	// 赵云去拆机囊
	cout << "刚来到 东吴境内 ，打开了第一个锦囊" << endl;
	open_tips(tp1);

	cout << "刘备乐不思蜀 ，打开第二个锦囊 " << endl;

	open_tips(tp2);

	cout << "孙权追杀刘备, 打开第三个锦囊" << endl;
	open_tips(tp3);
	cout << "赵云发现  抵挡不住 军队，想到了庞统的最后一个锦囊 打开了" << endl;

	open_tips(tp4);


	destory_tips(tp1);
	destory_tips(tp2);
	destory_tips(tp3);
	destory_tips(tp4);

	return 0;
}