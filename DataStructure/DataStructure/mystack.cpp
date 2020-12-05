#include<iostream>

template<class T>
class stackNode
{
public:
	stackNode() :next(nullptr) {}
	T data;					//ֵ
	stackNode* next;		//ָ����һ���ڵ��ָ��
};

template<class T>
class mystack
{
private:
	unsigned int stacklength;
	stackNode<T>* node;			//��ʱ�ڵ�
	stackNode<T>* headnode;		//β���
public:
	mystack();					//��ʼ��
	unsigned int length();		//ջԪ�صĸ���
	void push(T x);				//��ջ
	bool isEmpty();				//�ж�ջ�Ƿ�Ϊ��
	void pop();					//��ջ
	T top();					//���ջ��Ԫ��
	void clear();				//���ջ

};


template<class T>
mystack<T>::mystack()
{
	node = nullptr;
	headnode = nullptr;
	stacklength = 0;
}


template<class T>
inline unsigned int mystack<T>::length() { return stacklength; }


template<class T>
void  mystack<T>::push(T x)
{
	node = new stackNode<T>();
	node->data = x;
	node->next = this->headnode;//��node���ͷ�ڵ�
	this->headnode = node;
	++stacklength;
}


template<class T>
bool  mystack<T>::isEmpty()
{
	return stacklength == 0;
}


template<class T>
void  mystack<T>::pop()
{
	if (isEmpty()) return;
	node = headnode;
	headnode = headnode->next;	//ͷ�ڵ���������һ���ڵ�
	delete(node);				//ɾ��ͷ�ڵ�
	--stacklength;
}


template<class T>
T  mystack<T>::top()
{
	if (!isEmpty())
		return headnode->data;
}


template<class T>
void  mystack<T>::clear()
{
	while (headnode != nullptr)
	{
		node = headnode;
		headnode = headnode->next;
		delete(node);
	}
	node = nullptr;
	headnode = nullptr;
	stacklength = 0;
}

using namespace std;

int stack_test()
{
	mystack<int>  *p = new mystack<int>;

	int a = 10;
	p->push(a);
	p->push(a + 1);
	p->push(a + 2);
	p->push(a + 3);
	p->push(a + 4);

	for (int i = 0; i < 5; i++) {
		cout << p->top() << "len=" << p->length() << endl;
		p->pop();
	}

	return 0;
}