/**************************************************************************
1.˳��ջ�Ľṹ�ص�

˳��ջ����˳��洢�ṹ��ջ���ţ����ٷ�������仰��ɶ��˼�أ�
�������ڴ�����һ���ַ�����Ĵ洢��Ԫ���δ�Ŵ�ջ�׵�ջ����Ԫ�أ�
one by one������һ��֪������

ջ�������������£�
typedef struct {
	ElemType data[MaxSize];
	int top;��������//���ջ��Ԫ���������е��±�
}SqStack;
��ʼѧ��ʱ����ĺ��ԣ������top����ָ����������û��ŵ�ַ���š�������
������ͨ�������ҵ���ӦԪ�أ�Ҳ��������ָ������ðɡ�

�ڿα��ϲ�������һ��������

��û��ElemType�����鶨���ˣ�������������ָ��

typedef struct {
	ElemType *base;
	ElemType *top;
	int MaxSize;    //��ǰ�ѷ���Ŀռ�
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
	int stacksize;    //��ǰ�ѷ���Ŀռ�
}SqStack;

//ʹ�����鶨��ķ�ʽ����һ��ջ
//void InitStack(SqStack &s)
//{
//	s = (SqStack *)malloc(sizeof(SqStack));
//	s->top = 0;
//}
//ʹ�����鷽ʽ����ջ����
//int Push(SqStack &S, ElemType e) {
//	//������Ԫ��eѹ��ջ��
//	if (S.top == MaxSize)
//		return 0;
//	S.elem[S.top] = e;
//	S.top++;
//	return 1;
//}
//int Pop(SqStack &s, ElemType &e) {
//	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
//	if (S.top != 0)
//		return 0;
//	else {
//		S.top--;
//		e = S.elem[S.top];
//	}
//	return 1;
//}
//ʹ�����鷽ʽȡջ��Ԫ��
//int GetTop(SqStack &S, ElemType &e) {
//	//��ջ���գ�����e����ջ��Ԫ�ز�����1�����򷵻�0
//	if (S.top == 0)
//		return 0;
//	e = S.elem[S.top - 1];
//	return 1;
//}
/****************************************************
�������ܣ�����һ����ջ
***/
Status InitStack(SqStack &S) 
{
	//����һ����ջ
	S.base = (ElemType *)malloc(MaxSize * sizeof(ElemType));
	if (!S.base)   //�洢����ʧ��
		return 0;
	S.top = S.base;
	S.stacksize = MaxSize;
	return 1;
}//InitStack;

int Push(SqStack &S, ElemType e)
{
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if ((S.top - S.base) >= S.stacksize) //ջ����׷�Ӵ���ռ�
	{  
		S.base = (ElemType *)realloc(S.base,
			(S.stacksize + STACKINCREASEMENT) * sizeof(ElemType));

		if (!S.base)
			exit(0);    //�洢�ռ����ʧ��
		S.top = S.base + S.stacksize;
		//��ʱstacksize����ԭ����ֵľ�б��ָ�����û�����ӿռ��ջ��
		S.stacksize += STACKINCREASEMENT;
	}
	*S.top++ = e;
	return 1;
}
//��ջ����
int Pop(SqStack &S, ElemType &e) 
{
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
	if (S.top == S.base)
		return 0;
	e = *--S.top;
	return 1;
}//Pop
//ȡջ��Ԫ��
int GetTop(SqStack &S, ElemType &e) 
{
	//��ջ���գ�����e����ջ��Ԫ�ز�����1�����򷵻�0
	if (S.top == S.base)
		return 0;
	e = *(S.top - 1);
	return 1;
}//GetTOP




/************************************************************************************************
����ѧϰ��
&(����)----------------�����ڱ������������λ�ڱ������ʱ,��ʾ������������.
&(ȡ��ַ�����)--------- �ڸ���������ֵʱ�����ڵȺ��ұ߻���ִ���������ΪһԪ���������ʱ
��ʵ���ǵ����������һ�仰��������������һ��������ã��ͱ�����һ�����ȡַ��
	int a=3��
	int &b=a��        //����
	int *p=&a;        //ȡ��ַ

	int function(int &i)  //����
	{
	}  //����

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
	//����ѧϰ
	int N;
	int &rN = N;
	N = 1;
	cout << "rN��ֵΪ:" << rN << endl;
	cout << "&rN��ֵΪ��" << &rN << endl;

	//�ȿ�һ�µ�2��3�еĺ���ԭ�͡����������Ĺ��ܶ��ǽ�����������swap1�������βζ���ָ�룬��swap2���β����������á�
	//�ٿ�һ�µ�8�С���9�У�����swap1��ʱ����������ַ������x=&a,y=&b������xָ��a�Ŀռ䣬yָ��b�Ŀռ䡣
	//����swap2��ʱ�����������ø�����x=a,y=b������xֻ��a��һ��������y��b��һ��������ʵ�򶼴���ͬһ��ռ䡣
	//�������õ�ʱ�����������ָ����˵����Ч������㡣��Ϊָ�봫�ε�ʵ�ʻ��Ǵ�ֵ���ã�copy��ַ��Ҫ������
	//������ֱ�ӱ��������Ż�����Щʱ����Ҫ����ָ��ĵط���ʹ��ָ������û�ʹ����򻯺ܶ࣬
	//ԭ�ģ�https://blog.csdn.net/huecheung/article/details/39153341?utm_source=copy 
	//��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�
	int a = 10; 
	int b = 20;

	cout << "a = " << a << "  b =  " << b << endl;
	cout << "swap1 function the value!" << endl;
	swap1(&a,&b);
	cout << "a = " << a << "  b =  " << b << endl;

	cout << "swap2 function the value!" << endl;
	swap2(a,b);
	cout << "a = " << a << "  b =  " << b << endl;

	//ջ�ĺ�����дʹ�õ������ã�����������֪ʶ�ĸ�ϰ

	//ջ����ز�����ʼ
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