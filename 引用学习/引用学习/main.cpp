#include <iostream>

using namespace std;

void func(int &a)
{
    a = 5;
}
void func(int *const a)
{
    *a = 5;
}

int getA1()
{
    int a;
    a = 10;
    return a;
}
int& getA2()
{
    int a;
    a = 10;
    return a;
}

int main()
{
    int a = 10;
	int &b = a;
	a = 11;

	int *p = &a;
	*p = 12;
	cout << a << endl;


	b = 14;
	cout << "a = " << a << ", b = " << b << endl;
    int x = 10;
    func(x);
    cout << "the x value is " << x << endl;

    int m1 = 0;
    int m2 = 0;

    m1 = getA1();
    //��һ�����ã���ֵ��һ�����������п����Ķ���
    //��⣺�����������������������ز��� m2 = *(getA2())
    m2 = getA2();
    //�����ø�ֵ����һ�����ã�������ջ�Ĳ������ڴ�Ƿ�
    int &m3 = getA2();

    cout << "m1 = " << m1 << endl;
    cout << "m2 = " << m2 << endl;
    cout << "m3 = " << m3 << endl;


	getchar();
	return 0;

}


// ִ�н���� 12    a=14,b=14


// ����û�ж��壬��һ�ֹ�ϵ����������������ԭ�е�ĳһ�������Ĺ�ϵ���ʶ�������ԭ���ͱ���һ�£�
// �Ҳ������ڴ档�뱻���õı���������ͬ�ĵ�ַ
// ������ʱ������ʼ����һ�����������ɸ���
// �ص㣺&����ǰ����������ʱ�������á�������Ϊȡ��ַ��
// ���õı���-----> һ������ָ��
// ��������������Type &name   �ȼ���  type * const name
// C++ �������ڱ��������ʹ�ó�ָ����Ϊ���õ��ڲ�ʵ�֣����������ռ�õĿռ��С��ָ����ͬ




