#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test(int value)
	{
		this->value = value;
	}

	int getValue()
	{
		cout << "value = " << this->value << endl;
		return this->value;
	}

	Test operator+(Test &another)
	{
		cout << "执行了+重载操作符" << endl;
		Test temp(this->value + another.value);
		return temp;
	}

	//重载&&操作符  
	bool operator&&(Test &another)
	{
		cout << "执行了&&重载操作符" << endl;
		if (this->value && another.value) {
			return true;
		}
		else{
			return false;
		}
	}
	//重载||操作符  
	bool operator||(Test &another)
	{
		cout << "执行了||重载操作符" << endl;
		if (this->value || another.value) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int value;
};

int main(void)
{
	int a = 10;
	int b = 20;

	a = 0;

	//普通的&& 和||会有短路的现象
	if (a && (a = 20)) //&& 如果遇见非逻辑 直接退出
	{
		
	}

	cout << "a = " << a << endl;

	a = 10;
	if (a || (a = 20)) //&& 如果遇见是 逻辑 直接退出
	{

	}
	cout << "a = " << a << endl;


	cout << " --------   " << endl;


	Test t1(10);
	Test t2(20);

	if (t1.getValue() && (t1 + t2).getValue() ) //普通&& 会短路现象
	{
		cout << "if 进入成功" << endl;
	}


	cout << " --------   " << endl;

	if (t1 && (t1 + t2))// t1.operator&&(    t1.operator+(t2)   ) //我们重载的&&不会发生短路现象。
	{
		cout << "if 进入成功" << endl;
	}


	cout << " --------   " << endl;


	if (t1 || (t1 + t2)) //t1.operator|| (  t1.operator+(t2)    ) 
	{
		cout << "if 进入成功" << endl;

	}



	
	return 0;
}