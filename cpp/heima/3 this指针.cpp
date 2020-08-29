#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test(int k)
	{
		this->m_k = k;
		this->m_q = 0;
	}

	Test(int k, int q)
	{
		this->m_k = k;
		this->m_q = q;
	}

	/*
	int getK(Test * this) //this = &t2;
	{
		return this->m_k;
	}
	*/

	int  getK()  const   // int getK(const Test *const this) // this 是一个常指针
	{
		//this++;
		//this->m_k = 0; 在成员函数后面加const 修饰的不是函数，修饰的是隐藏的this指针
		return this->m_k;
	}

	
private:
	int m_k;
	int m_q;
};

int main(void)
{
	Test t1(10);  //  Test t1(&t1, 10)
	Test t2(20);

	t1.getK();

	t2.getK(); // t2.getK(&t2)
	
	return 0;
}