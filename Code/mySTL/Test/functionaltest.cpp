#include <iostream>
#include "Vector.h"
#include "Functional.h"

using namespace std;

class compare:public binary_function<int,int,bool>{//用于接收两个参数
public:
    bool operator()(int i, int num) const {
        return i > num;
    }
};

class comparetonum:public unary_function<int,bool>{//用于接收一个参数
public:
    bool operator()(int i) const {
        return i > 5;
    }
};

void print(int i,int j)//普通函数对象
{
    if (i > j){
        cout << i << " ";
    }
}

int main(){

    mySTL::vector <int> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i + 1);
    }

    mySTL::vector<int>::iterator it = mySTL::find_if(vec.begin(), vec.end(), bind2nd(compare(),6));//找出大于6的第一个数
    if (it == vec.end())
    {
        cout << "cannot find the number!" << endl;
    }
    else
    {
        cout << "find num: " << *it << endl;
    }

    mySTL::vector<int>::iterator rit = mySTL::find_if(vec.begin(), vec.end(), not1(comparetonum()));  //取反适配器的用法，找出小于5的第一个数
    if (rit == vec.end())
    {
        cout << "cannot find the number!" << endl;
    }
    else
    {
        cout << "find num: " << *rit << endl;
    }

    mySTL::vector<int> vec1;
    for (int i = 0; i < 10; i++)
    {
        vec1.push_back(i);
    }
    
    mySTL::for_each(vec1.begin(), vec1.end(), bind2nd(ptr_fun(print),5)); //使用ptr_fun将普通函数转换为函数对象，然后给函数对象绑定参数。
    cout << endl;
    
    return 0;
}
