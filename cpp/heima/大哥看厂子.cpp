#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

//���ĳ�����
class BigBrother
{
public:
	//���Ϊ��� һ��Ҫ����ˡ�
	virtual void fightPeople() = 0;
};

//��������
class EastNeverLost :public BigBrother
{
public:
	virtual void fightPeople()
	{
		cout << "ʹ�ÿ����������" << endl;
	}
};


//boss
int main(void)
{
	//boss ֪����һ�� ����ְλ �����
	BigBrother *bro = new EastNeverLost;

	//��������ȥ����
	bro->fightPeople();
	

	delete bro;

	return 0;
}