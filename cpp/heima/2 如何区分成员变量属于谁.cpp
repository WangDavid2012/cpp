#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Test
{
public:
	Test(int i)
	{
		mI = i;
	}

	int getI()
	{
		return mI;
	}
private:
	int mI;
};

/*
struct Test
{
	int mI;
}

Test_init(Test *pthis, int i)
{
  pthis->mI = i;
}

Test_getI(Test *pthis)
{
   return pthis->mI;
}
*/

int main(void)
{
	Test t1(10);

	t1.getI();

	//Test t1;
	//Test_init(&t1, 10);

	//Test_getI(&t1);
	
	return 0;
}