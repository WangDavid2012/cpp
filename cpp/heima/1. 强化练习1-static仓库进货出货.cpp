#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
static  --
*/

class Goods
{
public:
	//有参数的构造函数
	Goods()
	{
		next = NULL;
		weight = 0;
		cout << "创建了一个货物重量是" << 0 << "的物品" << endl;
	}

	Goods(int w)
	{
		weight = w;
		next = NULL;
		//每创建一个货物 总重量应该加
		cout << "创建了一个货物重量是" << w << "的物品" << endl;
		total_weight += w;
	}

	//提供一个静态的成员函数来访问静态成员
	static int getTotal()
	{
		return total_weight;
	}

	~Goods()
	{
		cout << "删除了一箱重量是" << weight << "货物" << endl;
		total_weight -= weight;
	}

	//给货物类变成一个链表的节点
	Goods* next;

private:
	int weight; //货物的重量
	static int total_weight; //所有货物的总重量
};

//已开是所有货物总重量是0
int Goods::total_weight = 0;

//进货的方法
void buy(Goods *  &head, int w)
{
	//创建一个新的货物
	Goods *new_goods = new Goods(10); //通过new 在堆上开辟空间， 调用了Goods类的有参构造函数

	//Goods goods1(w);

	if (head == NULL) {
		//如果head是空
		head = new_goods;
	}
	else {
		//如果head不为空， 从head表头添加
		new_goods->next = head;
		head = new_goods;
	}
}

//出货的方法
void sale(Goods * &head)
{
	if (head == NULL) {
		cout << "仓库已经没有货物了" << endl;
		return;
	}

	Goods *temp = head;
	head = head->next;
	delete temp;

	cout << "saled " << endl;
}

int main(void)
{
	int choice = 0;

	Goods *head = NULL; //所有货物 的 表头

	do {
		cout << "1 进货" << endl;
		cout << " 2 出货" << endl;
		cout << "0 退出" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			//进货
			cout << "请输入要创建的货物的重量" << endl;
			int w;
			cin >> w;
			buy(head, w);
			break;
		case 2:
			//出货
			sale(head);
			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}

		cout << "此时仓库中有 " << Goods::getTotal() << "重量的货物" << endl;
	} while (1);
	
	return 0;
}