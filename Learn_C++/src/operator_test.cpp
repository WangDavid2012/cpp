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

	//Ìá¹©Ò»¸ö´òÓ¡ĞéÊıµÄ·½·¨
	void print()
	{
		cout << "(" << a << "+ " << b << " i )" << endl;
	}

	friend Complex addComplex(Complex &c1, Complex &c2);
	//ÉùÃ÷Íâ²¿µÄÈ«¾Öº¯ÊıÎªÓÑÔª
#if 0
	friend Complex operator+(Complex &c1, Complex &c2);
	friend Complex operator-(Complex &c1, Complex &c2);
	friend Complex& operator+=(Complex &c1, Complex &c2);
	friend Complex & operator-=(Complex &c1, Complex &c2);
	//È«¾ÖÇ°++Ğ´·¨
	friend Complex & operator++(Complex &c1);
	friend Complex &operator--(Complex &c1);
	friend const Complex operator++(Complex &c1, int);


#endif

	friend ostream &  operator<<(ostream & os, Complex &c);
	friend istream &  operator >> (istream &is, Complex & c);

	/*
	//<<ÔËËã·û£¬ ÖØÔØ Ö»ÄÜĞ´ÔÚÈ«¾ÖÖĞ£¬ Èç¹ûĞ´ÔÚ×Ô¼ºµÄComplexÖĞ µ÷ÓÃË³Ğò¾Í·´ÁË
	//³ı·ÇĞŞ¸ÄostreamÀàµÄÔ´Âë ÔÚÄÇÀïÃæĞ´Ò»¸ö ostream & operator<<(Complex &c);
	ostream & operator<<(ostream &os) //c1.operator<<(cout) ---> c1 <<cout;
	{
		os << "( " << this->a << "+" << this->b << ")" << endl;

		return os;
	}
	*/

	//ºó++³ÉÔ±º¯Êı
	const Complex operator++(int)
	{
		Complex temp(this->a, this->b);

		a++;
		b++;
		return temp;
	}

	//Ç°--µÄ³ÉÔ±º¯Êı
	Complex &operator--()
	{
		this->a--;
		this->b--;

		return *this;
	}

	//Ç°++µÄ³ÉÔ±º¯Êı
	Complex & operator++() // c1.operator++()
	{
		this->a++;
		this->b++;
		return *this;
	}

	//²Ù×÷·ûÖØÔØµÄ³ÉÔ±º¯Êı
	Complex operator+(Complex &another)
	{
		Complex temp(this->a + another.a, this->b + another.b);
		return temp;
	}

	//³ÉÔ±º¯ÊıÖØÔØ-²Ù×÷·û
	Complex operator-(Complex &another)
	{
		Complex temp(this->a - another.a, this->b - another.b);
		return temp;
	}


	//ÊµÏÖ+= ²Ù×÷·û
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
	int a; //ÊµÊı²¿·Ö
	int b;//ĞéÊı²¿·Ö
};

//Ğ´Ò»¸öÈ«¾Öº¯Êı
Complex addComplex(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);

	return temp;
}

#if 0
//È«¾ÖÌá¹©Ò»¸ö+ºÅ²Ù×÷·ûÖØÔØ
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

//È«¾ÖÇ°++Ğ´·¨
Complex & operator++(Complex &c1)
{
	c1.a++;
	c1.b++;

	return c1;
}

//È«¾Ö·½·¨ÊµÏÖÇ°--
Complex &operator--(Complex &c1)
{
	c1.a--;
	c1.b--;

	return c1;
}

//¾ÍÊÇºó++µÄĞ´·¨
const Complex operator++(Complex &c1, int)//ÑÇÔª   //Õ¼Î»²ÎÊı
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






//ËùÓĞÖØÔØÔËËã·û ±ØĞëÓĞÒ»¸ö×Ô¶¨ÒåµÄÀàĞÍ¡£ ²»ÄÜ¹»È«ÓÃÆÕÍ¨ÀàĞÍ
//int operator+(int a, int b)
//{
//	return a - b;
//}

//ÏÔÊ½µ÷ÓÃºÍÒşÊ½µ÷ÓÃ
int operator_test()
{
	Complex c1(10, 20);
	Complex c2(1, 2);

	c1.print();
	c2.print();

	Complex c3 = addComplex(c1, c2); //Í¨¹ıÈ«¾Öº¯Êı½øĞĞµ÷ÓÃ

	c3.print();

	//Complex c4 = c1 + c2;          //ÒşÊ½µÄµ÷ÓÃ + 
	//Complex c4 = operator+(c1, c2);//ÏÔÊ¾µÄÈ«¾Öµ÷ÓÃÁËÒ»¸ö+ºÅÖØÔØ²Ù×÷·û
	Complex c4 = c1.operator+(c2);   //ÏÔÊ¾µÄµ÷ÓÃ±¾µØ·½·¨
	c4.print();


	Complex c5 = c1 + c2; //operator+(c1, c2); //Õı³£Ò»°ã²Ù×÷·ûÔËËã+  Ö§³Ö£¬È«¾ÖµÄµ÷ÓÃ·½Ê½£¬ºÍ ³ÉÔ±º¯ÊıµÄµ÷ÓÃ·½Ê½¡£
						  //Èç¹ûËµÓĞÈ«¾ÖµÄoperator+º¯Êı£¬ »áoperator+(c1,c2)
						  //Èç¹ûc1ÓĞ³ÉÔ±º¯Êıoperator+ , c1.operator+(c2);
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

	Complex c8(5, 6); //c8µÄÎŞ²Ò¹¹Ôì

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
ï»¿#define  _CRT_SECURE_NO_WARNINGS
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

	//æä¾›ä¸€ä¸ªæ‰“å°è™šæ•°çš„æ–¹æ³•
	void print()
	{
		cout << "(" << a << "+ " << b << " i )" << endl;
	}

	friend Complex addComplex(Complex &c1, Complex &c2);
	//å£°æ˜å¤–éƒ¨çš„å…¨å±€å‡½æ•°ä¸ºå‹å…ƒ
#if 0
	friend Complex operator+(Complex &c1, Complex &c2);
	friend Complex operator-(Complex &c1, Complex &c2);
	friend Complex& operator+=(Complex &c1, Complex &c2);
	friend Complex & operator-=(Complex &c1, Complex &c2);
	//å…¨å±€å‰++å†™æ³•
	friend Complex & operator++(Complex &c1);
	friend Complex &operator--(Complex &c1);
	friend const Complex operator++(Complex &c1, int);

#endif

	friend ostream &  operator<<(ostream & os, Complex &c);
	friend istream &  operator >> (istream &is, Complex & c);

	/*
	//<<è¿ç®—ç¬¦ï¼Œ é‡è½½ åªèƒ½å†™åœ¨å…¨å±€ä¸­ï¼Œ å¦‚æœå†™åœ¨è‡ªå·±çš„Complexä¸­ è°ƒç”¨é¡ºåºå°±åäº†
	//é™¤éä¿®æ”¹ostreamç±»çš„æºç  åœ¨é‚£é‡Œé¢å†™ä¸€ä¸ª ostream & operator<<(Complex &c);
	ostream & operator<<(ostream &os) //c1.operator<<(cout) ---> c1 <<cout;
	{
		os << "( " << this->a << "+" << this->b << ")" << endl;

		return os;
	}
	*/

	//å++æˆå‘˜å‡½æ•°
	const Complex operator++(int)
	{
		Complex temp(this->a, this->b);

		a++;
		b++;
		return temp;
	}

	//å‰--çš„æˆå‘˜å‡½æ•°
	Complex &operator--()
	{
		this->a--;
		this->b--;

		return *this;
	}

	//å‰++çš„æˆå‘˜å‡½æ•°
	Complex & operator++() // c1.operator++()
	{
		this->a++;
		this->b++;
		return *this;
	}

	//æ“ä½œç¬¦é‡è½½çš„æˆå‘˜å‡½æ•°
	Complex operator+(Complex &another)
	{
		Complex temp(this->a + another.a, this->b + another.b);
		return temp;
	}

	//æˆå‘˜å‡½æ•°é‡è½½-æ“ä½œç¬¦
	Complex operator-(Complex &another)
	{
		Complex temp(this->a - another.a, this->b - another.b);
		return temp;
	}

	//å®ç°+= æ“ä½œç¬¦
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
	int a; //å®æ•°éƒ¨åˆ†
	int b;//è™šæ•°éƒ¨åˆ†
};

//å†™ä¸€ä¸ªå…¨å±€å‡½æ•°
Complex addComplex(Complex &c1, Complex &c2)
{
	Complex temp(c1.a + c2.a, c1.b + c2.b);

	return temp;
}

#if 0
//å…¨å±€æä¾›ä¸€ä¸ª+å·æ“ä½œç¬¦é‡è½½
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

//å…¨å±€å‰++å†™æ³•
Complex & operator++(Complex &c1)
{
	c1.a++;
	c1.b++;

	return c1;
}

//å…¨å±€æ–¹æ³•å®ç°å‰--
Complex &operator--(Complex &c1)
{
	c1.a--;
	c1.b--;

	return c1;
}

//å°±æ˜¯å++çš„å†™æ³•
const Complex operator++(Complex &c1, int)//äºšå…ƒ   //å ä½å‚æ•°
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

//æ‰€æœ‰é‡è½½è¿ç®—ç¬¦ å¿…é¡»æœ‰ä¸€ä¸ªè‡ªå®šä¹‰çš„ç±»å‹ã€‚ ä¸èƒ½å¤Ÿå…¨ç”¨æ™®é€šç±»å‹
//int operator+(int a, int b)
//{
//	return a - b;
//}

//æ˜¾å¼è°ƒç”¨å’Œéšå¼è°ƒç”¨
int operator_test()
{
	Complex c1(10, 20);
	Complex c2(1, 2);

	c1.print();
	c2.print();

	Complex c3 = addComplex(c1, c2); //é€šè¿‡å…¨å±€å‡½æ•°è¿›è¡Œè°ƒç”¨

	c3.print();

	//Complex c4 = c1 + c2;          //éšå¼çš„è°ƒç”¨ +
	//Complex c4 = operator+(c1, c2);//æ˜¾ç¤ºçš„å…¨å±€è°ƒç”¨äº†ä¸€ä¸ª+å·é‡è½½æ“ä½œç¬¦
	Complex c4 = c1.operator+(c2);   //æ˜¾ç¤ºçš„è°ƒç”¨æœ¬åœ°æ–¹æ³•
	c4.print();

	Complex c5 = c1 + c2; //operator+(c1, c2); //æ­£å¸¸ä¸€èˆ¬æ“ä½œç¬¦è¿ç®—+  æ”¯æŒï¼Œå…¨å±€çš„è°ƒç”¨æ–¹å¼ï¼Œå’Œ æˆå‘˜å‡½æ•°çš„è°ƒç”¨æ–¹å¼ã€‚
						  //å¦‚æœè¯´æœ‰å…¨å±€çš„operator+å‡½æ•°ï¼Œ ä¼šoperator+(c1,c2)
						  //å¦‚æœc1æœ‰æˆå‘˜å‡½æ•°operator+ , c1.operator+(c2);
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

	Complex c8(5, 6); //c8çš„æ— æƒ¨æ„é€ 

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
