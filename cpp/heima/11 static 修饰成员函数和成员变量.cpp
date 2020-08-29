#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class AA
{
public:
	AA(int a, int b)
	{
		m_a = a;
		m_b = b;
	}

	int getC()
	{
		cout << "c = " << m_c << endl;
		m_c++;
		return m_c;
	}

	static int m_c;//静态的成员变量  //1 在类的内部声明这个变量 用static
						//静态的成员变量是对本来共享，所有本类中的对象 都是公用一个内存区域
private:
	int m_a;
	int m_b;
};


//2 静态成员变量的初始化， 在类的外部去写
int AA::m_c = 0;

int main(void)
{
	AA aa1(10, 20), aa2(100,200), aa3(1000,2000);

	aa1.getC();
	aa2.getC();
	aa3.getC();

	//怎么去修改一个静态的成员变量
	AA::m_c = 200;

	aa1.getC();
	aa2.getC();
	aa3.getC();



	
	return 0;
}