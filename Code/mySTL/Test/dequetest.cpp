#include <iostream>
#include "Deque.h"

void print(mySTL::deque<int> temp){
    mySTL::deque<int>::iterator it = temp.begin();
	for(; it != temp.end();it++)
	    std::cout<<*it<<" ";
	std::cout<<std::endl;
}

int main(){
    mySTL::deque<int> val;
    val.push_back(1);
    val.push_back(4);
    val.push_back(7);
    std::cout<<"After pushback:"<<std::endl;
    print(val);

    val.push_front(8);
    val.push_front(5);
    val.push_front(2);
    std::cout<<"After pushfront:"<<std::endl;
    print(val);

    std::cout<<"The size of val: "<<val.size()<<std::endl;

    std::cout<<"After copy:"<<std::endl;
    mySTL::deque<int> val1(val);
    print(val1);

    std::cout<<"After popback:"<<std::endl;
    val.pop_back();
    print(val);

    std::cout<<"After popfront:"<<std::endl;
    val.pop_front();
    print(val);
  
  
}
