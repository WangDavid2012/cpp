#include <iostream>
#include "Set.h"

int main(){
    int i;
    int arr[6] = {4,2,7,1,9,8};
    std::cout<<"Before putting in set: ";
    for(int i = 0;i < 6;i++)
	   std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
    
    mySTL::set<int> iset(arr,arr+6);
    std::cout<< "lower_bound 2: " <<*iset.lower_bound(2)<<std::endl;
    std::cout<< "upper_bound 2: " <<*iset.upper_bound(2)<<std::endl;
    
    std::cout<<"After insert and put 3: ";
    iset.insert(3);
    mySTL::set<int>::iterator it;
    for(it = iset.begin ();it != iset.end ();it++)
    {
        std::cout<<*it<<" "; 
    }
    std::cout<<std::endl;
    //print(iset);
    it = iset.find(8);
    std::cout <<"Can we find 8?: ";
    if(it == iset.end()) 
	std::cout<< "NO!" <<std::endl;
    else
	std::cout<< "YES!" <<std::endl;
    std::cout<<std::endl;
    
    return 0;
}
