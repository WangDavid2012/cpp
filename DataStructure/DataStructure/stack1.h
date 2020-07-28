#pragma once
namespace stacksavitch
{
	struct StackFrame {
		char data;
		StackFrame *link;
	};
	typedef StackFrame * StatckFramePtr;


	class Stack {
	public:
		Stack();
		Stack(const Stack &a_stack);
		~Stack();
		void push(char the_symbol);
		char pop();
		bool empty() const;
	private:
		StatckFramePtr top;

	};



}