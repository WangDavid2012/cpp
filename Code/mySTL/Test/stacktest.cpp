#include <iostream>
#include "Stack.h"

void print(mySTL::stack<int> temp){
	
	while(!temp.empty()){
		std::cout<<temp.top()<<" ";
		temp.pop();	
	}
	std::cout<<std::endl;
}

int main(){
	mySTL::stack<int> stc;
	stc.push(3);
	stc.push(4);
	stc.push(2);
	stc.push(5);
	stc.push(7);
	std::cout<<"After push: ";
	print(stc);

	std::cout<<"The size of stcak: "<<stc.size()<<std::endl;
	
	stc.pop();
	stc.pop();
	std::cout<<"After pop: ";
	print(stc);

	std::cout<<"The size of stcak after pop: "<<stc.size()<<std::endl;
	return 0;
}