#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Parent
{
public:
	Parent(int a)
	{
		this->a = a;
	}

	virtual void print()
	{
		cout << "Parent::print() " << a << endl;
	}
protected:
	int a;
};

class Child :public Parent{
public:
	Child(int a) :Parent(a)
	{

	}

	virtual void print()
	{
		cout << "Child :: Print() " << a <<endl;
	}
private:
	int b;
};

int main(void)
{
	Child array[] = {Child(0), Child(1), Child(2) };
	//						array[0]   array[1] array[2]

	Child *cp = &array[0];
	Parent *pp = &array[0];


	cp->print(); //Child::
	pp->print(); //Child::·¢Éú¶àÌ¬

	cout << "------" << endl;

	cp++; //Child::12
	//pp++;//8
	pp = cp;

	cp->print();
	pp->print();

	cout << " -----  " << endl;

	
	int i = 0;
	for (i = 0, cp = &array[0], pp = cp; i < 3; i++, cp++, pp =cp) {
		pp->print();
	}
	
	return 0;
}