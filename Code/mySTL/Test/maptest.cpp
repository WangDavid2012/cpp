#include <iostream>
#include "Map.h"

int main(){
	mySTL::map<std::string, int> map;
	map.insert(mySTL::pair<std::string,int>("zhangsan",110));
	map.insert(mySTL::pair<std::string,int>("lisi",120));
	map.insert(mySTL::pair<std::string,int>("wangwu",130));
	map.insert(mySTL::pair<std::string,int>("mazi",140));
	const mySTL::pair<const std::string, int> value(std::string("pangdun"),150);
	map.insert(value);

	std::cout<<"After insert: "<<std::endl;
	auto iter = map.begin();
	for(;iter != map.end();++iter) 
 		std::cout<<"name: "<<iter->first <<' ' <<"id: "<<iter->second<<std::endl;  
	std::cout <<"Can we find lisi?: ";
	iter = map.find(std::string("lisi"));
	if(iter == map.end()) 
		std::cout<< "NO!" <<std::endl;
	else
		std::cout<< "YES!" <<std::endl;
	std::cout <<"His id is "<<iter->second<< std::endl;
	std::cout<<std::endl;

   	std::cout<< "After erase lisi" <<std::endl;
	map.erase(iter);
	iter = map.begin();
	for(;iter != map.end();++iter) 
 		std::cout<<"name: "<<iter->first <<' ' <<"id: "<<iter->second<<std::endl; 
	return 0;
}	

