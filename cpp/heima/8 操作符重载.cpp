#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class Complex
{
public:
	Complex()
	{
		this->a = 0;
		this->b = 0;
	}
	Complex(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	//�ṩһ����ӡ�����ķ���
	void print()
	{
		cout << "(" << a << "+ " << b << " i )" << endl;
	}

	friend Complex addComplex(Complex &c1, Complex &c2);
	//�����ⲿ��ȫ�ֺ���Ϊ��Ԫ
#if 0
	friend Complex operator+(Complex &c1, Complex &c2);
	friend Complex operator-(Complex &c1, Complex &c2);
	friend Complex& operator+=(Complex &c1, Complex &c2);
	friend Complex & operator-=(Complex &c1, Complex &c2);
	//ȫ��ǰ++д��
	friend Complex & operator++(Complex &c1);
	friend Complex &operator--(Complex &c1);
	friend const Complex operator++(Complex &c1, int);


#endif

	friend ostream&  operator<<(ostream & os, Complex &c);
	friend istream & operator>>(istream &is, Complex & c);

	/*
	//<<������� ���� ֻ��д��ȫ���У� ���д���Լ���Complex�� ����˳��ͷ���
	//�����޸�ostream���Դ�� ��������дһ�� ostream & operator<<(Complex &c);
	ostream & operator<<(ostream &os) //c1.operator<<(cout) ---> c1 <<cout;
	{
		os << "( " << this->a << "+" << this->b << ")" << endl;

		return os;
	}
	*/

	//��++��Ա����
	const Complex operator++(int)
	{
		Complex temp(this->a, this->b);

		a++;
		b++;
		return temp;
	}

	//ǰ--�ĳ�Ա����
	Complex &operator--()
	{
		this->a--;
		this->b--;

		return *this;
	}

	//ǰ++�ĳ�Ա����
	Complex & operator++() // c1.operator++()
	{
		this->a++;
		this->b++;

		return *this;
	}

	//���������صĳ�Ա����
	Complex operator+(Complex &another)
	{
		Complex temp(this->a + another.a, this->b + another.b);
		return temp;
	}

	//��Ա��������-������
	Complex operator-(Complex &another) 
	{
		Complex temp(this->a - another.a, this->b - another.b);
		return temp;
	}


	//ʵ��+= ������
	Complex& operator+=(Complex &another)
	{
		this->a += another.a;
		this->b += another.b;

		return *this;
	}

	Complex & operator-=(Complex &another)
	{
		this->a -= another.a;
		this->b -= another.b;

		return *this;
	}



private:
	int a; //ʵ������
	int b;//��������
};

//дһ��ȫ�ֺ���
Complex addComplex(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);

	return temp;
}

#if 0
//ȫ���ṩһ��+�Ų���������
Complex operator+(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);
	return temp;
}

Complex operator-(Complex &c1, Complex &c2)
{
	Complex temp(c1.a - c2.a, c1.b - c2.b);
	return temp;
}
Complex operator+(Complex &c1)
{

}

Complex& operator+=(Complex &c1, Complex &c2)
{
	c1.a += c2.a;
	c1.b += c2.b;

	return c1;
}


Complex & operator-=(Complex &c1, Complex &c2)
{
	c1.a -= c2.a;
	c1.b -= c2.b;
	return c1;
}

//ȫ��ǰ++д��
Complex & operator++(Complex &c1)
{
	c1.a++;
	c1.b++;

	return c1;
}

//ȫ�ַ���ʵ��ǰ--
Complex &operator--(Complex &c1)
{
	c1.a--;
	c1.b--;

	return c1;
}

//���Ǻ�++��д��
const Complex operator++(Complex &c1, int)//��Ԫ   //ռλ����
{
	Complex temp(c1.a, c1.b);

	c1.a++;
	c1.b++;

	return temp;
}



#endif

//operator<<(cout, c);
ostream & operator<<(ostream & os, Complex &c)
{
	os << "( " << c.a << "+" << c.b << ")" << endl;

	return os;
}

istream & operator>>(istream &is, Complex & c)
{
	cout << "a : ";
	is >> c.a;
	cout << "b :";
	is >> c.b;

	return is;
}





/*
//������������� ������һ���Զ�������͡� ���ܹ�ȫ����ͨ����
int operator+(int a, int b)
{
	return a - b;
}
*/

int main(void)
{
	Complex c1(10, 20);
	Complex c2(1, 2);

	c1.print();
	c2.print();

	Complex c3 = addComplex(c1, c2); //ͨ��ȫ�ֺ������е���

	c3.print();

	//Complex c4 = c1 + c2;          //��ʽ�ĵ��� + 
	//Complex c4 = operator+(c1, c2);//��ʾ��ȫ�ֵ�����һ��+�����ز�����
	Complex c4 = c1.operator+(c2);   //��ʾ�ĵ��ñ��ط���
	c4.print();
	

	Complex c5 = c1 + c2; //operator+(c1, c2); //����һ�����������+  ֧�֣�ȫ�ֵĵ��÷�ʽ���� ��Ա�����ĵ��÷�ʽ��
	//���˵��ȫ�ֵ�operator+������ ��operator+(c1,c2)
	//���c1�г�Ա����operator+ , c1.operator+(c2);
	c5.print();

	cout << " ----" << endl;  //cout.operator<<(string str);
	Complex c6 = c1 - c2;
	c6.print();




	Complex c7 = c1;

	Complex *cp = &c1;



	int a = 10;
	int b = 20;
	int c = 30;

	a += b;

	a += (b += c);
	cout << "a =" << a << endl;
	cout << "b =" << b << endl;
	cout << "c =" << c << endl;

	Complex c8(5, 6); //c8���޲ҹ���

	c8 += c1 += c2; 


	c8.print();
	c1.print();
	c2.print();

	c8 += c1;//c8

	Complex c9(10, 20);

	c9 -= c2;

	c9.print();

	a = 10;

	++++++++a;
	cout << "a = " << a << endl;

	Complex c10(10, 20);
	++++++++c10;
	c10.print();

	Complex c11(10, 20);
	------c11;
	c11.print();

	a = 10;

	
	Complex c12(10, 20);
	c12++;
	c12.print();

	cout << "-----" << endl;
	//cout << c12 << c11 << c10 << endl;; // cout.operator<<(c12)
						//operator<<(cout, c12);

	//cout << c12; //cout .operator(c12)   c12.operaotr(cout)
	//c12 << cout;

	Complex c13;

	cin >> c13;

	cout << c13;

	return 0;
}