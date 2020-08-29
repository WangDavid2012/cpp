#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

/*
static  --
*/

class Goods
{
public:
	//�в����Ĺ��캯��
	Goods()
	{
		next = NULL;
		weight = 0;
		cout << "������һ������������" << 0 << "����Ʒ" << endl;
	}

	Goods(int w)
	{
		weight = w;
		next = NULL;
		//ÿ����һ������ ������Ӧ�ü�
		cout << "������һ������������" << w << "����Ʒ" << endl;
		total_weight += w;
	}

	//�ṩһ����̬�ĳ�Ա���������ʾ�̬��Ա
	static int getTotal()
	{
		return total_weight;
	}

	~Goods()
	{
		cout << "ɾ����һ��������" << weight << "����" << endl;
		total_weight -= weight;
	}

	//����������һ������Ľڵ�
	Goods* next;

private:
	int weight; //���������
	static int total_weight; //���л����������
};

//�ѿ������л�����������0
int Goods::total_weight = 0;

//�����ķ���
void buy(Goods *  &head, int w)
{
	//����һ���µĻ���
	Goods *new_goods = new Goods(10); //ͨ��new �ڶ��Ͽ��ٿռ䣬 ������Goods����вι��캯��

	//Goods goods1(w);

	if (head == NULL) {
		//���head�ǿ�
		head = new_goods;
	}
	else {
		//���head��Ϊ�գ� ��head��ͷ���
		new_goods->next = head;
		head = new_goods;
	}
}

//�����ķ���
void sale(Goods * &head)
{
	if (head == NULL) {
		cout << "�ֿ��Ѿ�û�л�����" << endl;
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

	Goods *head = NULL; //���л��� �� ��ͷ

	do {
		cout << "1 ����" << endl;
		cout << " 2 ����" << endl;
		cout << "0 �˳�" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			//����
			cout << "������Ҫ�����Ļ��������" << endl;
			int w;
			cin >> w;
			buy(head, w);
			break;
		case 2:
			//����
			sale(head);
			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}

		cout << "��ʱ�ֿ����� " << Goods::getTotal() << "�����Ļ���" << endl;
	} while (1);
	
	return 0;
}