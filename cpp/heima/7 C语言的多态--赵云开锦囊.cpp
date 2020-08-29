#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

// ����һ�����ҵķ��� ��һ������ָ�룬������c++�Ĵ��麯��
typedef void(TIPS_FUNC)(void);


//дһ�����ҵĽṹ��
struct tips
{
	char from[64]; //���������˭д��
	char to[64]; //д��˭��
	TIPS_FUNC *fp; //������ҵ�����
};


//дһ�������Ƶ��õļܹ�����
void open_tips(struct tips * tp)
{
	cout << "���˽���" << endl;
	cout << "�˽�������" << tp->from << ", д��" << tp->to << endl;
	cout << "������" << endl;
	tp->fp();//�𿪽��ң����þ�����ҵķ���
}

//ʵ��һ��һ���Ľ���  //������ʵ��һ�����麯��
void tips_1(void)
{
	cout << "һ������ʹ���������ǹ���" << endl;
}

void tips_2(void)
{
	cout << "ƭ���� ����ѹ��" << endl;
}

void tips_3(void)
{
	cout << "�����������" << endl;
}

void tips_4(void)
{
	cout << "���Ǿ����ڶ����" << endl;
}

struct tips* create_tips(char *from, char *to, TIPS_FUNC *fp)
{
	struct tips *tp = (struct tips*)malloc(sizeof(struct tips));
	if (tp == NULL) {
		return NULL;
	}
	strcpy(tp->from, from);
	strcpy(tp->to, to);
	//ע��ص�����
	tp->fp = fp; //��ӵ�к���ָ��Ľṹ��  ����ָ����� ��ֵ ���� ע��ص�����

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
	//�����ȥд����
	struct tips * tp1 = create_tips("����", "����", tips_1);
	struct tips * tp2 = create_tips("����", "����", tips_2);
	struct tips * tp3 = create_tips("����", "����", tips_3);
	struct tips *tp4= create_tips("��ͳ", "����", tips_4);


	// ����ȥ�����
	cout << "������ ���⾳�� �����˵�һ������" << endl;
	open_tips(tp1);

	cout << "�����ֲ�˼�� ���򿪵ڶ������� " << endl;

	open_tips(tp2);

	cout << "��Ȩ׷ɱ����, �򿪵���������" << endl;
	open_tips(tp3);
	cout << "���Ʒ���  �ֵ���ס ���ӣ��뵽����ͳ�����һ������ ����" << endl;

	open_tips(tp4);


	destory_tips(tp1);
	destory_tips(tp2);
	destory_tips(tp3);
	destory_tips(tp4);

	return 0;
}