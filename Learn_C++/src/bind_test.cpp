<<<<<<< HEAD
#include <iostream>
#include <iostream>
#include <algorithm>
#include <functional>


using namespace std;
class A
{
public:
	void fun_3(int k, int m)
	{
		cout << k << " " << m << endl;
	}
};

void fun(int x, int y, int z)
{
	cout << x << "  " << y << "  " << z << endl;
}

void fun_2(int &a, int &b)
{
	a++;
	b++;
	cout << a << "  " << b << endl;
}

int bind_test1()
{
	auto f1 = std::bind(fun, 1, 2, 3); //±íÊ¾°ó¶¨º¯Êý fun µÄµÚÒ»£¬¶þ£¬Èý¸ö²ÎÊýÖµÎª£º 1 2 3
	f1(); //print:1  2  3

	auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
	//±íÊ¾°ó¶¨º¯Êý fun µÄµÚÈý¸ö²ÎÊýÎª 3£¬¶øfun µÄµÚÒ»£¬¶þ¸ö²ÎÊý·Ö±ðÓÉµ÷ÓÃ f2 µÄµÚÒ»£¬¶þ¸ö²ÎÊýÖ¸¶¨
	f2(1, 2);//print:1  2  3

	auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
	//±íÊ¾°ó¶¨º¯Êý fun µÄµÚÈý¸ö²ÎÊýÎª 3£¬¶øfun µÄµÚÒ»£¬¶þ¸ö²ÎÊý·Ö±ðÓÐµ÷ÓÃ f3 µÄµÚ¶þ£¬Ò»¸ö²ÎÊýÖ¸¶¨
	//×¢Òâ£º f2  ºÍ  f3 µÄÇø±ð¡£
	f3(1, 2);          //print:2  1  3

	int n = 2;
	int m = 3;

	auto f4 = std::bind(fun_2, n, placeholders::_1);
	f4(m); //print:3  4

	cout << m << endl;//print:4  ËµÃ÷£ºbind¶ÔÓÚ²»ÊÂÏÈ°ó¶¨µÄ²ÎÊý£¬Í¨¹ýstd::placeholders´«µÝµÄ²ÎÊýÊÇÍ¨¹ýÒýÓÃ´«µÝµÄ
	cout << n << endl;//print:2  ËµÃ÷£ºbind¶ÔÓÚÔ¤ÏÈ°ó¶¨µÄº¯Êý²ÎÊýÊÇÍ¨¹ýÖµ´«µÝµÄ

	A a;
	auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
	f5(10, 20);//print:10 20
			   //¶¨ÒåÁËÒ»¸öº¯ÊýÖ¸Õë fc£¬·µ»ØÖµÊÇvoid£¬²ÎÊý int int
	std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
	fc(10, 20);//print:10 20

	return 0;
}



//less()ÊÇÒ»¸ö¶þÔªº¯Êý£¬less(a, b)±íÊ¾ÅÐ¶Ïa<bÊÇ·ñ³ÉÁ¢¡£

int bind_test2()
{
	int numbers[] = { 10,20,30,40,50,10 };
	int cx;
	cx = count_if(numbers, numbers + 6, bind(less<int>(), std::placeholders::_1, 40));
	cout << "There are " << cx << " elements that are less than 40.\n";

	cx = count_if(numbers, numbers + 6, bind(less<int>(), 40, std::placeholders::_1));
	cout << "There are " << cx << " elements that are not less than 40.\n";

	system("pause");
	return 0;
}
=======
ï»¿#include <iostream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

//std::bind()çš„è¿”å›žå€¼æ˜¯ä¸€ä¸ªå‡½æ•°æŒ‡é’ˆ

class A {
public:
    void fun_3(int k, int m) {
        cout << k << " " << m << endl;
    }
};

void fun(int x, int y, int z) {
    cout << x << "  " << y << "  " << z << endl;
}

void fun_2(int &a, int &b) {
    a++;
    b++;
    cout << a << "  " << b << endl;
}

int bind_test1() {
    auto f1 = std::bind(fun, 1, 2, 3); //è¡¨ç¤ºç»‘å®šå‡½æ•° fun çš„ç¬¬ä¸€ï¼ŒäºŒï¼Œä¸‰ä¸ªå‚æ•°å€¼ä¸ºï¼š 1 2 3
    f1(); //print:1  2  3

    auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
    //è¡¨ç¤ºç»‘å®šå‡½æ•° fun çš„ç¬¬ä¸‰ä¸ªå‚æ•°ä¸º 3ï¼Œè€Œfun çš„ç¬¬ä¸€ï¼ŒäºŒä¸ªå‚æ•°åˆ†åˆ«ç”±è°ƒç”¨ f2 çš„ç¬¬ä¸€ï¼ŒäºŒä¸ªå‚æ•°æŒ‡å®š
    f2(1, 2);//print:1  2  3

    auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
    //è¡¨ç¤ºç»‘å®šå‡½æ•° fun çš„ç¬¬ä¸‰ä¸ªå‚æ•°ä¸º 3ï¼Œè€Œfun çš„ç¬¬ä¸€ï¼ŒäºŒä¸ªå‚æ•°åˆ†åˆ«æœ‰è°ƒç”¨ f3 çš„ç¬¬äºŒï¼Œä¸€ä¸ªå‚æ•°æŒ‡å®š
    //æ³¨æ„ï¼š f2  å’Œ  f3 çš„åŒºåˆ«ã€‚
    f3(1, 2);          //print:2  1  3

    int n = 2;
    int m = 3;

    auto f4 = std::bind(fun_2, n, placeholders::_1);
    f4(m); //print:3  4

    cout << m << endl;//print:4  è¯´æ˜Žï¼šbindå¯¹äºŽä¸äº‹å…ˆç»‘å®šçš„å‚æ•°ï¼Œé€šè¿‡std::placeholdersä¼ é€’çš„å‚æ•°æ˜¯é€šè¿‡å¼•ç”¨ä¼ é€’çš„
    cout << n << endl;//print:2  è¯´æ˜Žï¼šbindå¯¹äºŽé¢„å…ˆç»‘å®šçš„å‡½æ•°å‚æ•°æ˜¯é€šè¿‡å€¼ä¼ é€’çš„

    A a;
    auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
    f5(10, 20);//print:10 20
    //å®šä¹‰äº†ä¸€ä¸ªå‡½æ•°æŒ‡é’ˆ fcï¼Œè¿”å›žå€¼æ˜¯voidï¼Œå‚æ•° int int
    std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
    fc(10, 20);//print:10 20

    return 0;
}

//less()æ˜¯ä¸€ä¸ªäºŒå…ƒå‡½æ•°ï¼Œless(a, b)è¡¨ç¤ºåˆ¤æ–­a<bæ˜¯å¦æˆç«‹ã€‚

int bind_test2() {
    int numbers[] = { 10, 20, 30, 40, 50, 10 };
    int cx;
    cx = count_if(numbers, numbers + 6, bind(less<int>(), std::placeholders::_1, 40));
    cout << "There are " << cx << " elements that are less than 40.\n";

    cx = count_if(numbers, numbers + 6, bind(less<int>(), 40, std::placeholders::_1));
    cout << "There are " << cx << " elements that are not less than 40.\n";

    system("pause");
    return 0;
}
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
