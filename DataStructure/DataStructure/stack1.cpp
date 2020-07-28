#include <iostream>
#include "stack1.h"
using namespace std;

namespace stacksavitch
{
	Stack::Stack() :top(nullptr)
	{
	}

	Stack::Stack(const Stack & a_stack)
	{
		if (a_stack.top == nullptr)
			this->top = nullptr;
		else
		{
			StatckFramePtr tmp = a_stack.top;
			StatckFramePtr end; //Ö½ÏäÐÂÕ»µÄÎ²²¿
			end = new StackFrame;
			end->data = tmp->data;
			top = end;

			tmp = tmp->link;
			while (tmp != nullptr)
			{
				end->link = new StackFrame;
				end = end->link;
				end->data = tmp->data;
				tmp = tmp->link;
			}
			end->link = nullptr;
		}
	}

	Stack::~Stack()
	{
		char next;
		while (!empty())
			next = pop();
	}

	void Stack::push(char  the_symbol)
	{
		StatckFramePtr tmp_ptr;
		tmp_ptr = new StackFrame;
		tmp_ptr->data = the_symbol;
		tmp_ptr->link = top;
		top = tmp_ptr->link;
	}

	char Stack::pop()
	{
		if (empty())
		{
			std::cout << "error" << std::endl;
			exit(1);
		}
		char result = top->data;
		StatckFramePtr tmp_ptr;
		tmp_ptr = top;
		top = top->link;
		delete tmp_ptr;
		return result;
		return 0;
	}

	bool Stack::empty() const
	{

		return (top == nullptr);
	}


	void stack_test1()
	{
		char ans, next;
		Stack s;
		do{
			cout << "Enter a Word:" << endl;
			cin.get(next);
			while (next != '\n')
			{
				s.push(next);
				cin.get(next);
			}
			cout << "Write a backward that is: ";
			while (!s.empty())
				cout << s.pop();
			cout << endl;

			cout << "Again?(y/n): ";
			cin >> ans;
			cin.ignore(10000, 'n');




		} while (ans != 'n' && ans != 'N');
	
	}


}

