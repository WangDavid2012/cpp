#include "Vector.h"
#include <iostream>
#include "Algorithm.h"

int summing(mySTL::vector<int> val)
{
    int sum = 0;
    mySTL::vector<int>::iterator ix = val.begin();
    for (;ix != val.end(); ix++)
        sum += *ix;//求和
    return sum;
}

void print(mySTL::vector<int> val){
    mySTL::vector<int>::iterator ix = val.begin();
    for (;ix != val.end(); ix++)
     std::cout<<*ix<<" ";
    std::cout<<std::endl;
}

int main(int argv,char *argc[])
{
    int sum;
    int input[5];
    std::cout<<"enter 5 numbers"<<std::endl;
    for(int i = 0;i < 5;i++)
    {
        std::cin>>input[i];//输入5个参数
    }
    mySTL::vector<int> val(input,input + 5);
    
    if(val.size() == 0)//判断a是否为空
    {
        std::cout<<"no element?"<<std::endl;
        return -1;
    }
    
    std::cout<<"The vector of val:"<<std::endl;
    print(val);

    std::cout<<"After insert:"<<std::endl;
    mySTL::vector<int>::iterator it = val.begin();
    mySTL::advance(it,2);
    val.insert(it,2,3);
    print(val);
    
    std::cout<<"The size of val:"<<std::endl;
    std::cout<<val.size()<<std::endl;
    
    std::cout<<"After pushback:"<<std::endl;
    val.push_back(11);
    print(val);

    std::cout<<"After erase:"<<std::endl;   
    val.erase(it);
    print(val);
 
    std::cout<<"After popback:"<<std::endl;
    val.pop_back();
    print(val); 

    sum = summing(val);
    std::cout<<"The sum of val = "<<sum<<std::endl;


    std::cout<<"After sort:"<<std::endl;
    mySTL::vector<int>::iterator beg = val.begin();
    mySTL::vector<int>::iterator end = val.end();
    mySTL::sort(beg,end);
    print(val);
    return 0;
}
