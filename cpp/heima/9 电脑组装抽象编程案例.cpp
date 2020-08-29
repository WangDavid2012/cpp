#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// --------    抽象层 - --------------

//抽象的cpu类
class CPU
{
public:
	//抽象的计算方法
	virtual void caculate() = 0;
};

//抽象的显卡
class Card
{
public:
	virtual void display() = 0;
};

class Memory
{
public:
	virtual void storage() = 0;
};

class Computer
{
public:
	Computer(CPU *cpu, Card *card, Memory *mem) //cpu = new IntelCPU
	{
		this->cpu = cpu;
		this->card = card;
		this->mem = mem;
	}

	//给电脑提供一个工作的方法
	void work()
	{
		cpu->caculate(); //发生多态
		card->display(); //发生多态
		mem->storage();//发生多态
	}

	~Computer()
	{
		if (cpu != NULL) {
				delete cpu;
				cpu = NULL;
		}
		if (card != NULL) {
			delete card;
			card = NULL;
		}
		if (mem != NULL) {
			delete mem;
			mem = NULL;
		}
	}

private:
	CPU *cpu;
	Card* card;
	Memory*mem;
};

// ----------------- 抽象层(end) -------------



// --------- 实现层  -------
//intel 的cpu
class IntelCPU :public CPU
{
public:
	virtual void caculate()
	{
		cout << "intel 的cpu 开始计算了" << endl;
	}
};

class IntelCard :public Card
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示了" << endl;
	}
};

class IntelMem :public Memory
{
public:
	virtual void storage() {
		cout << "Intel  的内存条 开始 存储了" << endl;
	}
};


class KingstonMem :public Memory
{
public:
	virtual void storage() {
		cout << "Kingston 的内存条 开始 存储了" << endl;
	}
};

class NvdiaCard :public Card
{
public:
	virtual void display()
	{
		cout << "Nvdia的显卡开始显示了" << endl;
	}

};

// --------- 实现层(end)  -------


//高层业务逻辑层
int main(void)
{
	CPU *intelCPU = new IntelCPU;
	Card* intelCard = new IntelCard;
	Memory *intelMem = new IntelMem;

#if 0

	cout << "第一台电脑" << endl;
	intelCPU->caculate();
	intelCard->display();
	intelMem->storage();
#endif
	Computer *computer1 = new Computer(intelCPU, intelCard, intelMem);
	computer1->work();
	//delete computer1;



	//组装第二台
	cout << "0000 " << endl;

	Card* nvdiaCard = new NvdiaCard;
	Memory *kingstonMem = new KingstonMem; //两个具体的产品拿到了

	Computer *computer2 = new Computer(intelCPU, nvdiaCard, kingstonMem);
	computer2->work();
	delete computer2;


	//delete intelCard;
	//delete intelCPU;
	//delete intelMem;





	Computer *computer3 = new Computer(new IntelCPU, new IntelCard, new IntelMem);
	
	computer3->work();

	delete computer3;

	return 0;
}