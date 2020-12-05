#include<iostream>

template<class T>
class stackNode
{
public:
	stackNode() :next(nullptr) {}
	T data;					//值
	stackNode* next;		//指向下一个节点的指针
};

template<class T>
class mystack
{
private:
	unsigned int stacklength;
	stackNode<T>* node;			//临时节点
	stackNode<T>* headnode;		//尾结点
public:
	mystack();					//初始化
	unsigned int length();		//栈元素的个数
	void push(T x);				//入栈
	bool isEmpty();				//判断栈是否为空
	void pop();					//出栈
	T top();					//获得栈顶元素
	void clear();				//清空栈

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
	node->next = this->headnode;//把node变成头节点
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
	headnode = headnode->next;	//头节点变成它的下一个节点
	delete(node);				//删除头节点
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