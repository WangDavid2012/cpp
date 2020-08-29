#include <iostream>
#include "Iterator.h"
#include "Vector.h"

int main()
{
    //advance使用
    mySTL::vector<int> vec;
    for(int i = 0;i < 10;i++)
        vec.push_back(i);

    mySTL::vector<int>::iterator it = vec.begin();
    mySTL::vector<int>::iterator end = vec.end();
    std::cout<<"The value of vector:";
    for(;it != vec.end();it++)
	std::cout<<*it<<" ";
    std::cout<<std::endl;
 
    it = vec.begin();
    std::cout<<"After advance 3:";
    mySTL::advance(it,3);
    std::cout << *it << " "<<std::endl;
    //distance使用
    std::cout<<"The distance of position 3 to the end:";
    std::cout<<mySTL::distance(it,end)<<std::endl;
    
  
}
