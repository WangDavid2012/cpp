#include <iostream>
#include "List.h"

void print(mySTL::list<int> temp){
    mySTL::list<int>::iterator it = temp.begin();
    for(; it != temp.end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
}

int main(){
    mySTL::list<int> val;
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
    mySTL::list<int> val1(val);
    print(val1);

    std::cout<<"After popback:"<<std::endl;
    val.pop_back();
    print(val);

    std::cout<<"After popfront:"<<std::endl;
    val.pop_front();
    print(val);
  
    mySTL::list<int>::iterator ix = val.begin();
    std::cout<<"After erase position 2:"<<std::endl;
    advance(ix,1);
    val.erase(ix);
    print(val);

    ix = val.begin();
    std::cout<<"After insert to position 2:"<<std::endl;
    advance(ix,1);
    val.insert(ix,6);
    print(val);
    
    std::cout<<"After splice val and val1:"<<std::endl;
    val.splice(val.begin(),val1);
    print(val);
    
    std::cout<<"After sort:"<<std::endl;
    val.sort();
    print(val);
}