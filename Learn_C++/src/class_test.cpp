<<<<<<< HEAD
#include <iostream>
#include <string>

using namespace std;

class ClassOne
{
public:
	int m_one;
public:
	void PrintSomething(const string& strInput, const int& nInput);
};

void ClassOne::PrintSomething(const string & strInput, const int & nInput)
{
	cout << strInput << nInput << endl;
}


int class_test()
{
	// 直接使用类名创建对象
	ClassOne c1;
	c1.m_one = 1;
	string strSomething = "m_one value is: ";
	c1.PrintSomething(strSomething, c1.m_one);

	// 使用new创建对象
	ClassOne *c2 = new ClassOne();
	c2->m_one = 2;
	c2->PrintSomething(strSomething, c2->m_one);
	if (NULL != c2)
	{
		// 使用delete删除对象
		delete c2;
		c2 = NULL;
	}

	return 0;
}
=======
锘�#include <iostream>
#include <string>

using namespace std;

class ClassOne {
public:
    int m_one;
public:
    void PrintSomething(const string &strInput, const int &nInput);
};

void ClassOne::PrintSomething(const string &strInput, const int &nInput) {
    cout << strInput << nInput << endl;
}

int class_test() {
    // 鐩存帴浣跨敤绫诲悕鍒涘缓瀵硅薄
    ClassOne c1;
    c1.m_one = 1;
    string strSomething = "m_one value is: ";
    c1.PrintSomething(strSomething, c1.m_one);

    // 浣跨敤new鍒涘缓瀵硅薄
    ClassOne *c2 = new ClassOne();
    c2->m_one = 2;
    c2->PrintSomething(strSomething, c2->m_one);
    if (NULL != c2) {
        // 浣跨敤delete鍒犻櫎瀵硅薄
        delete c2;
        c2 = NULL;
    }

    return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
