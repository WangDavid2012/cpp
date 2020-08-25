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
	// ֱ��ʹ��������������
	ClassOne c1;
	c1.m_one = 1;
	string strSomething = "m_one value is: ";
	c1.PrintSomething(strSomething, c1.m_one);

	// ʹ��new��������
	ClassOne *c2 = new ClassOne();
	c2->m_one = 2;
	c2->PrintSomething(strSomething, c2->m_one);
	if (NULL != c2)
	{
		// ʹ��deleteɾ������
		delete c2;
		c2 = NULL;
	}

	return 0;
}
