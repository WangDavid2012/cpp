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
	auto f1 = std::bind(fun, 1, 2, 3); //表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
	f1(); //print:1  2  3

	auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
	//表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
	f2(1, 2);//print:1  2  3

	auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
	//表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别有调用 f3 的第二，一个参数指定
	//注意： f2  和  f3 的区别。
	f3(1, 2);          //print:2  1  3

	int n = 2;
	int m = 3;

	auto f4 = std::bind(fun_2, n, placeholders::_1);
	f4(m); //print:3  4

	cout << m << endl;//print:4  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的
	cout << n << endl;//print:2  说明：bind对于预先绑定的函数参数是通过值传递的

	A a;
	auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
	f5(10, 20);//print:10 20
			   //定义了一个函数指针 fc，返回值是void，参数 int int
	std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
	fc(10, 20);//print:10 20

	return 0;
}



//less()是一个二元函数，less(a, b)表示判断a<b是否成立。

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
锘�#include <iostream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

//std::bind()鐨勮繑鍥炲�兼槸涓�涓嚱鏁版寚閽�

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
    auto f1 = std::bind(fun, 1, 2, 3); //琛ㄧず缁戝畾鍑芥暟 fun 鐨勭涓�锛屼簩锛屼笁涓弬鏁板�间负锛� 1 2 3
    f1(); //print:1  2  3

    auto f2 = std::bind(fun, placeholders::_1, placeholders::_2, 3);
    //琛ㄧず缁戝畾鍑芥暟 fun 鐨勭涓変釜鍙傛暟涓� 3锛岃�宖un 鐨勭涓�锛屼簩涓弬鏁板垎鍒敱璋冪敤 f2 鐨勭涓�锛屼簩涓弬鏁版寚瀹�
    f2(1, 2);//print:1  2  3

    auto f3 = std::bind(fun, placeholders::_2, placeholders::_1, 3);
    //琛ㄧず缁戝畾鍑芥暟 fun 鐨勭涓変釜鍙傛暟涓� 3锛岃�宖un 鐨勭涓�锛屼簩涓弬鏁板垎鍒湁璋冪敤 f3 鐨勭浜岋紝涓�涓弬鏁版寚瀹�
    //娉ㄦ剰锛� f2  鍜�  f3 鐨勫尯鍒��
    f3(1, 2);          //print:2  1  3

    int n = 2;
    int m = 3;

    auto f4 = std::bind(fun_2, n, placeholders::_1);
    f4(m); //print:3  4

    cout << m << endl;//print:4  璇存槑锛歜ind瀵逛簬涓嶄簨鍏堢粦瀹氱殑鍙傛暟锛岄�氳繃std::placeholders浼犻�掔殑鍙傛暟鏄�氳繃寮曠敤浼犻�掔殑
    cout << n << endl;//print:2  璇存槑锛歜ind瀵逛簬棰勫厛缁戝畾鐨勫嚱鏁板弬鏁版槸閫氳繃鍊间紶閫掔殑

    A a;
    auto f5 = std::bind(&A::fun_3, a, placeholders::_1, placeholders::_2);
    f5(10, 20);//print:10 20
    //瀹氫箟浜嗕竴涓嚱鏁版寚閽� fc锛岃繑鍥炲�兼槸void锛屽弬鏁� int int
    std::function<void(int, int)> fc = std::bind(&A::fun_3, a, std::placeholders::_1, std::placeholders::_2);
    fc(10, 20);//print:10 20

    return 0;
}

//less()鏄竴涓簩鍏冨嚱鏁帮紝less(a, b)琛ㄧず鍒ゆ柇a<b鏄惁鎴愮珛銆�

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
