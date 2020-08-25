#include <iostream>
#include "Bitset.h"
int main(){
    mySTL::bitset<32> bit(0x0153cefa);
    for(int i = 0;i < 32;i++)
	std::cout << "bit" << i <<": " << bit[i] <<" \t ";
    std::cout<<std::endl;
    std::cout << "bit: " << bit << std::endl;
	
    std::cout << "The num of 1: " << bit.count() << std::endl;

    std::string tag = "";
    if(bit.test(6))
	tag = "true";
    else
	tag = "fasle";
    std::cout << "IS the position 6 1 ?: " << tag << std::endl;
 
    std::cout << "After flip bit: " << bit.flip() << std::endl;

    bit.set(4);
    std::cout << "Set position 4 to 1: " << bit << std::endl;

    bit.reset(4);
    std::cout << "Reset position 4 to 0: " << bit << std::endl;
    

}