#include <iostream>
#include "Multimap.h"

int main(){
	mySTL::multimap<std::string, int> mtmap;
	mtmap.insert(mySTL::pair<std::string,int>("zhangsan",110));
	mtmap.insert(mySTL::pair<std::string,int>("lisi",120));
	mtmap.insert(mySTL::pair<std::string,int>("wangwu",130));
	mtmap.insert(mySTL::pair<std::string,int>("mazi",140));
	const mySTL::pair<const std::string, int> value(std::string("zhangsan"),150);
	mtmap.insert(value);

	std::cout<<"After insert: "<<std::endl;
	auto iter = mtmap.begin();
	for(;iter != mtmap.end();++iter) 
 		std::cout<<"name: "<<iter->first <<' ' <<"id: "<<iter->second<<std::endl;  
	std::cout <<"Can we find lisi?: ";
	iter = mtmap.find(std::string("lisi"));
	if(iter == mtmap.end()) 
		std::cout<< "NO!" <<std::endl;
	else
		std::cout<< "YES!" <<std::endl;
	std::cout <<"His id is "<<iter->second<< std::endl;
	std::cout<<std::endl;

   	std::cout<< "After erase lisi" <<std::endl;
	mtmap.erase(iter);
	iter = mtmap.begin();
	for(;iter != mtmap.end();++iter) 
 		std::cout<<"name: "<<iter->first <<' ' <<"id: "<<iter->second<<std::endl; 
	return 0;
}	

