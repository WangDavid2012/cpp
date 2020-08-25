#include <iostream>
#include "Queue.h"

void print(mySTL::queue<int> temp){
	
	while(!temp.empty()){
		std::cout<<temp.front()<<" ";
		temp.pop();	
	}
	std::cout<<std::endl;
}

int main(){
	mySTL::queue<int> stc;
	stc.push(3);
	stc.push(4);
	stc.push(2);
	stc.push(5);
	stc.push(7);
	std::cout<<"After push: ";
	print(stc);

	std::cout<<"The size of queue: "<<stc.size()<<std::endl;
	
	stc.pop();
	stc.pop();
	std::cout<<"After pop: ";
	print(stc);

	std::cout<<"The size of queue after pop: "<<stc.size()<<std::endl;

	std::cout<<"The front of queue: "<<stc.front()<<std::endl;
	std::cout<<"The back of queue: "<<stc.back()<<std::endl;
	return 0;
}