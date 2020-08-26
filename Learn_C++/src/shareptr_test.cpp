<<<<<<< HEAD
#include <iostream>
#include <memory>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;


class A
{
public:
	int i;
	A(int n) :i(n) { };
	~A() { cout << i << " " << "destructed" << endl; }
};


struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the
								  // shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}



int shareptr_test()
{
	shared_ptr<A> sp1(new A(2));	//A(2)ÓÉsp1ÍĞ¹Ü£¬
	shared_ptr<A> sp2(sp1);			//A(2)Í¬Ê±½»ÓÉsp2ÍĞ¹Ü
	shared_ptr<A> sp3;
	sp3 = sp2;						//A(2)Í¬Ê±½»ÓÉsp3ÍĞ¹Ü
	cout << sp1->i << "," << sp2->i << "," << sp3->i << endl;
	A * p = sp3.get();				// get·µ»ØÍĞ¹ÜµÄÖ¸Õë£¬p Ö¸Ïò A(2)
	cout << p->i << endl;			//Êä³ö 2
	sp1.reset(new A(3));			// resetµ¼ÖÂÍĞ¹ÜĞÂµÄÖ¸Õë, ´ËÊ±sp1ÍĞ¹ÜA(3)
	sp2.reset(new A(4));			// sp2ÍĞ¹ÜA(4)
	cout << sp1->i << endl;			//Êä³ö 3
	sp3.reset(new A(5));			// sp3ÍĞ¹ÜA(5),A(2)ÎŞÈËÍĞ¹Ü£¬±»delete
	cout << "end" << endl;
	return 0;
}

void shareptr_test1()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
}


//Base::Base()
//Derived::Derived()
//Created a shared Derived(as a pointer to Base)
//p.get() = 0xc99028, p.use_count() = 1
//Shared ownership between 3 threads and released
//ownership from main :
//p.get() = (nil), p.use_count() = 0
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 3
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 4
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 2
//Derived::~Derived()
//Base::~Base()
//All threads completed, the last one deleted Derived
=======
ï»¿#include <iostream>
#include <memory>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

class A
{
public:
	int i;
	A(int n) :i(n) { };
	~A() { cout << i << " " << "destructed" << endl; }
};

struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the
								  // shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

int shareptr_test()
{
	shared_ptr<A> sp1(new A(2));	//A(2)ç”±sp1æ‰˜ç®¡ï¼Œ
	shared_ptr<A> sp2(sp1);			//A(2)åŒæ—¶äº¤ç”±sp2æ‰˜ç®¡
	shared_ptr<A> sp3;
	sp3 = sp2;						//A(2)åŒæ—¶äº¤ç”±sp3æ‰˜ç®¡
	cout << sp1->i << "," << sp2->i << "," << sp3->i << endl;
	A * p = sp3.get();				// getè¿”å›æ‰˜ç®¡çš„æŒ‡é’ˆï¼Œp æŒ‡å‘ A(2)
	cout << p->i << endl;			//è¾“å‡º 2
	sp1.reset(new A(3));			// resetå¯¼è‡´æ‰˜ç®¡æ–°çš„æŒ‡é’ˆ, æ­¤æ—¶sp1æ‰˜ç®¡A(3)
	sp2.reset(new A(4));			// sp2æ‰˜ç®¡A(4)
	cout << sp1->i << endl;			//è¾“å‡º 3
	sp3.reset(new A(5));			// sp3æ‰˜ç®¡A(5),A(2)æ— äººæ‰˜ç®¡ï¼Œè¢«delete
	cout << "end" << endl;
	return 0;
}

void shareptr_test1()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join();
	t2.join();
	t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
}

//Base::Base()
//Derived::Derived()
//Created a shared Derived(as a pointer to Base)
//p.get() = 0xc99028, p.use_count() = 1
//Shared ownership between 3 threads and released
//ownership from main :
//p.get() = (nil), p.use_count() = 0
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 3
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 4
//local pointer in a thread :
//lp.get() = 0xc99028, lp.use_count() = 2
//Derived::~Derived()
//Base::~Base()
//All threads completed, the last one deleted Derived
>>>>>>> 2a8dddf120c2aaa302c7f817dba894da97e11960
