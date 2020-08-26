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
	// ÷±Ω” π”√¿‡√˚¥¥Ω®∂‘œÛ
	ClassOne c1;
	c1.m_one = 1;
	string strSomething = "m_one value is: ";
	c1.PrintSomething(strSomething, c1.m_one);

	//  π”√new¥¥Ω®∂‘œÛ
	ClassOne *c2 = new ClassOne();
	c2->m_one = 2;
	c2->PrintSomething(strSomething, c2->m_one);
	if (NULL != c2)
	{
		//  π”√delete…æ≥˝∂‘œÛ
		delete c2;
		c2 = NULL;
	}

	return 0;
}
=======
Ôªø#include <iostream>
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
    // Áõ¥Êé•‰ΩøÁî®Á±ªÂêçÂàõÂª∫ÂØπË±°
    ClassOne c1;
    c1.m_one = 1;
    string strSomething = "m_one value is: ";
    c1.PrintSomething(strSomething, c1.m_one);

    // ‰ΩøÁî®newÂàõÂª∫ÂØπË±°
    ClassOne *c2 = new ClassOne();
    c2->m_one = 2;
    c2->PrintSomething(strSomething, c2->m_one);
    if (NULL != c2) {
        // ‰ΩøÁî®deleteÂà†Èô§ÂØπË±°
        delete c2;
        c2 = NULL;
    }

    return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
