#include <iostream>
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
    // 直接使用类名创建对象
    ClassOne c1;
    c1.m_one = 1;
    string strSomething = "m_one value is: ";
    c1.PrintSomething(strSomething, c1.m_one);

    // 使用new创建对象
    ClassOne *c2 = new ClassOne();
    c2->m_one = 2;
    c2->PrintSomething(strSomething, c2->m_one);
    if (NULL != c2) {
        // 使用delete删除对象
        delete c2;
        c2 = NULL;
    }

    return 0;
}
