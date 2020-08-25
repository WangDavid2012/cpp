#include <iostream>
#include "Complex.h"

int main()
{
	mySTL::complex<int> com1(3,6);
	mySTL::complex<int> com2(4,5);
	mySTL::complex<int>  com3;
	mySTL::complex<int>  com4;
	mySTL::complex<int>  com5;
	mySTL::complex<int>  com6;
	std::cout<<"com1: ";
	com1.Display();
	std::cout<<"com2: ";
	com2.Display();
	std::cout<<std::endl;

	std::cout<<"com1 real: "<<com1.real()<<std::endl;
	std::cout<<"com1 image: "<<com1.image()<<std::endl;

	std::cout<<"com2 real: "<<com2.real()<<std::endl;
	std::cout<<"com2 image: "<<com2.image()<<std::endl;
	std::cout<<std::endl;

	//加
	std::cout<<"加法: ";
	com3 = com1 + com2;
	com3.Display();
	//减
	std::cout<<"减法: ";
	com4 = com1 - com2;
	com4.Display();

	//乘法
	std::cout<<"乘法: ";
	com5 = com1 * com2;
	com5.Display();

	//除法
	std::cout<<"除法: ";
	com6 = com1 / com2;
	com6.Display();
	std::cout<<std::endl;
	 return 0;
}