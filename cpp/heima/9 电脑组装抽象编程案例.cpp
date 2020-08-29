#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// --------    ����� - --------------

//�����cpu��
class CPU
{
public:
	//����ļ��㷽��
	virtual void caculate() = 0;
};

//������Կ�
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

	//�������ṩһ�������ķ���
	void work()
	{
		cpu->caculate(); //������̬
		card->display(); //������̬
		mem->storage();//������̬
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

// ----------------- �����(end) -------------



// --------- ʵ�ֲ�  -------
//intel ��cpu
class IntelCPU :public CPU
{
public:
	virtual void caculate()
	{
		cout << "intel ��cpu ��ʼ������" << endl;
	}
};

class IntelCard :public Card
{
public:
	virtual void display()
	{
		cout << "Intel���Կ���ʼ��ʾ��" << endl;
	}
};

class IntelMem :public Memory
{
public:
	virtual void storage() {
		cout << "Intel  ���ڴ��� ��ʼ �洢��" << endl;
	}
};


class KingstonMem :public Memory
{
public:
	virtual void storage() {
		cout << "Kingston ���ڴ��� ��ʼ �洢��" << endl;
	}
};

class NvdiaCard :public Card
{
public:
	virtual void display()
	{
		cout << "Nvdia���Կ���ʼ��ʾ��" << endl;
	}

};

// --------- ʵ�ֲ�(end)  -------


//�߲�ҵ���߼���
int main(void)
{
	CPU *intelCPU = new IntelCPU;
	Card* intelCard = new IntelCard;
	Memory *intelMem = new IntelMem;

#if 0

	cout << "��һ̨����" << endl;
	intelCPU->caculate();
	intelCard->display();
	intelMem->storage();
#endif
	Computer *computer1 = new Computer(intelCPU, intelCard, intelMem);
	computer1->work();
	//delete computer1;



	//��װ�ڶ�̨
	cout << "0000 " << endl;

	Card* nvdiaCard = new NvdiaCard;
	Memory *kingstonMem = new KingstonMem; //��������Ĳ�Ʒ�õ���

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