#include <iostream>
#include "Multiset.h"

int main(){
    mySTL::multiset<int> imultiset;
    imultiset.insert(1);
    imultiset.insert(2);
    imultiset.insert(1);
    imultiset.insert(4);
    imultiset.insert(4);
    std::cout<<"After insert ";

    auto it = imultiset.begin();
    for(;it != imultiset.end();it++)
	    std::cout<<*it<<" ";
    std::cout<<std::endl;
    std::cout<<"size:"<<imultiset.size()<<std::endl;
    std::cout<< "lower_bound 2: " <<*imultiset.lower_bound(2)<<std::endl;
    std::cout<< "upper_bound 2: " <<*imultiset.upper_bound(2)<<std::endl;
    it = imultiset.find(2);
    std::cout <<"Can we find 2?: ";
    if(it == imultiset.end())
	    std::cout<< "NO!" <<std::endl;
    else
	    std::cout<< "YES!" <<std::endl;

    std::cout<<"After eraase 2"<<std::endl;
    imultiset.erase(2);
    it = imultiset.find(2);
    std::cout <<"Can we find 2?: ";
    if(it == imultiset.end())
	    std::cout<< "NO!" <<std::endl;
    else
	    std::cout<< "YES!" <<std::endl;
    std::cout<<std::endl;
    return 0;
}
