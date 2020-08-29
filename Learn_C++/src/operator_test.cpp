<<<<<<< HEAD
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

	//提供一个打印虚数的方法
	void print()
	{
		cout << "(" << a << "+ " << b << " i )" << endl;
	}

	friend Complex addComplex(Complex &c1, Complex &c2);
	//声明外部的全局函数为友元
#if 0
	friend Complex operator+(Complex &c1, Complex &c2);
	friend Complex operator-(Complex &c1, Complex &c2);
	friend Complex& operator+=(Complex &c1, Complex &c2);
	friend Complex & operator-=(Complex &c1, Complex &c2);
	//全局前++写法
	friend Complex & operator++(Complex &c1);
	friend Complex &operator--(Complex &c1);
	friend const Complex operator++(Complex &c1, int);


#endif

	friend ostream &  operator<<(ostream & os, Complex &c);
	friend istream &  operator >> (istream &is, Complex & c);

	/*
	//<<运算符， 重载 只能写在全局中， 如果写在自己的Complex中 调用顺序就反了
	//除非修改ostream类的源码 在那里面写一个 ostream & operator<<(Complex &c);
	ostream & operator<<(ostream &os) //c1.operator<<(cout) ---> c1 <<cout;
	{
		os << "( " << this->a << "+" << this->b << ")" << endl;

		return os;
	}
	*/

	//后++成员函数
	const Complex operator++(int)
	{
		Complex temp(this->a, this->b);

		a++;
		b++;
		return temp;
	}

	//前--的成员函数
	Complex &operator--()
	{
		this->a--;
		this->b--;

		return *this;
	}

	//前++的成员函数
	Complex & operator++() // c1.operator++()
	{
		this->a++;
		this->b++;
		return *this;
	}

	//操作符重载的成员函数
	Complex operator+(Complex &another)
	{
		Complex temp(this->a + another.a, this->b + another.b);
		return temp;
	}

	//成员函数重载-操作符
	Complex operator-(Complex &another)
	{
		Complex temp(this->a - another.a, this->b - another.b);
		return temp;
	}


	//实现+= 操作符
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
	int a; //实数部分
	int b;//虚数部分
};

//写一个全局函数
Complex addComplex(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);

	return temp;
}

#if 0
//全局提供一个+号操作符重载
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

//全局前++写法
Complex & operator++(Complex &c1)
{
	c1.a++;
	c1.b++;

	return c1;
}

//全局方法实现前--
Complex &operator--(Complex &c1)
{
	c1.a--;
	c1.b--;

	return c1;
}

//就是后++的写法
const Complex operator++(Complex &c1, int)//亚元   //占位参数
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

istream & operator >> (istream &is, Complex & c)
{
	cout << "a : ";
	is >> c.a;
	cout << "b :";
	is >> c.b;
	return is;
}






//所有重载运算符 必须有一个自定义的类型。 不能够全用普通类型
//int operator+(int a, int b)
//{
//	return a - b;
//}

//显式调用和隐式调用
int operator_test()
{
	Complex c1(10, 20);
	Complex c2(1, 2);

	c1.print();
	c2.print();

	Complex c3 = addComplex(c1, c2); //通过全局函数进行调用

	c3.print();

	//Complex c4 = c1 + c2;          //隐式的调用 + 
	//Complex c4 = operator+(c1, c2);//显示的全局调用了一个+号重载操作符
	Complex c4 = c1.operator+(c2);   //显示的调用本地方法
	c4.print();


	Complex c5 = c1 + c2; //operator+(c1, c2); //正常一般操作符运算+  支持，全局的调用方式，和 成员函数的调用方式。
						  //如果说有全局的operator+函数， 会operator+(c1,c2)
						  //如果c1有成员函数operator+ , c1.operator+(c2);
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

	Complex c8(5, 6); //c8的无惨构造

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
=======
锘�#define  _CRT_SECURE_NO_WARNINGS
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

	//鎻愪緵涓�涓墦鍗拌櫄鏁扮殑鏂规硶
	void print()
	{
		cout << "(" << a << "+ " << b << " i )" << endl;
	}

	friend Complex addComplex(Complex &c1, Complex &c2);
	//澹版槑澶栭儴鐨勫叏灞�鍑芥暟涓哄弸鍏�
#if 0
	friend Complex operator+(Complex &c1, Complex &c2);
	friend Complex operator-(Complex &c1, Complex &c2);
	friend Complex& operator+=(Complex &c1, Complex &c2);
	friend Complex & operator-=(Complex &c1, Complex &c2);
	//鍏ㄥ眬鍓�++鍐欐硶
	friend Complex & operator++(Complex &c1);
	friend Complex &operator--(Complex &c1);
	friend const Complex operator++(Complex &c1, int);

#endif

	friend ostream &  operator<<(ostream & os, Complex &c);
	friend istream &  operator >> (istream &is, Complex & c);

	/*
	//<<杩愮畻绗︼紝 閲嶈浇 鍙兘鍐欏湪鍏ㄥ眬涓紝 濡傛灉鍐欏湪鑷繁鐨凜omplex涓� 璋冪敤椤哄簭灏卞弽浜�
	//闄ら潪淇敼ostream绫荤殑婧愮爜 鍦ㄩ偅閲岄潰鍐欎竴涓� ostream & operator<<(Complex &c);
	ostream & operator<<(ostream &os) //c1.operator<<(cout) ---> c1 <<cout;
	{
		os << "( " << this->a << "+" << this->b << ")" << endl;

		return os;
	}
	*/

	//鍚�++鎴愬憳鍑芥暟
	const Complex operator++(int)
	{
		Complex temp(this->a, this->b);

		a++;
		b++;
		return temp;
	}

	//鍓�--鐨勬垚鍛樺嚱鏁�
	Complex &operator--()
	{
		this->a--;
		this->b--;

		return *this;
	}

	//鍓�++鐨勬垚鍛樺嚱鏁�
	Complex & operator++() // c1.operator++()
	{
		this->a++;
		this->b++;
		return *this;
	}

	//鎿嶄綔绗﹂噸杞界殑鎴愬憳鍑芥暟
	Complex operator+(Complex &another)
	{
		Complex temp(this->a + another.a, this->b + another.b);
		return temp;
	}

	//鎴愬憳鍑芥暟閲嶈浇-鎿嶄綔绗�
	Complex operator-(Complex &another)
	{
		Complex temp(this->a - another.a, this->b - another.b);
		return temp;
	}

	//瀹炵幇+= 鎿嶄綔绗�
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
	int a; //瀹炴暟閮ㄥ垎
	int b;//铏氭暟閮ㄥ垎
};

//鍐欎竴涓叏灞�鍑芥暟
Complex addComplex(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);

	return temp;
}

#if 0
//鍏ㄥ眬鎻愪緵涓�涓�+鍙锋搷浣滅閲嶈浇
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

//鍏ㄥ眬鍓�++鍐欐硶
Complex & operator++(Complex &c1)
{
	c1.a++;
	c1.b++;

	return c1;
}

//鍏ㄥ眬鏂规硶瀹炵幇鍓�--
Complex &operator--(Complex &c1)
{
	c1.a--;
	c1.b--;

	return c1;
}

//灏辨槸鍚�++鐨勫啓娉�
const Complex operator++(Complex &c1, int)//浜氬厓   //鍗犱綅鍙傛暟
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

istream & operator >> (istream &is, Complex & c)
{
	cout << "a : ";
	is >> c.a;
	cout << "b :";
	is >> c.b;
	return is;
}

//鎵�鏈夐噸杞借繍绠楃 蹇呴』鏈変竴涓嚜瀹氫箟鐨勭被鍨嬨�� 涓嶈兘澶熷叏鐢ㄦ櫘閫氱被鍨�
//int operator+(int a, int b)
//{
//	return a - b;
//}

//鏄惧紡璋冪敤鍜岄殣寮忚皟鐢�
int operator_test()
{
	Complex c1(10, 20);
	Complex c2(1, 2);

	c1.print();
	c2.print();

	Complex c3 = addComplex(c1, c2); //閫氳繃鍏ㄥ眬鍑芥暟杩涜璋冪敤

	c3.print();

	//Complex c4 = c1 + c2;          //闅愬紡鐨勮皟鐢� +
	//Complex c4 = operator+(c1, c2);//鏄剧ず鐨勫叏灞�璋冪敤浜嗕竴涓�+鍙烽噸杞芥搷浣滅
	Complex c4 = c1.operator+(c2);   //鏄剧ず鐨勮皟鐢ㄦ湰鍦版柟娉�
	c4.print();

	Complex c5 = c1 + c2; //operator+(c1, c2); //姝ｅ父涓�鑸搷浣滅杩愮畻+  鏀寔锛屽叏灞�鐨勮皟鐢ㄦ柟寮忥紝鍜� 鎴愬憳鍑芥暟鐨勮皟鐢ㄦ柟寮忋��
						  //濡傛灉璇存湁鍏ㄥ眬鐨刼perator+鍑芥暟锛� 浼歰perator+(c1,c2)
						  //濡傛灉c1鏈夋垚鍛樺嚱鏁皁perator+ , c1.operator+(c2);
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

	Complex c8(5, 6); //c8鐨勬棤鎯ㄦ瀯閫�

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
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
