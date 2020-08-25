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
	shared_ptr<A> sp1(new A(2));	//A(2)由sp1托管，
	shared_ptr<A> sp2(sp1);			//A(2)同时交由sp2托管
	shared_ptr<A> sp3;
	sp3 = sp2;						//A(2)同时交由sp3托管
	cout << sp1->i << "," << sp2->i << "," << sp3->i << endl;
	A * p = sp3.get();				// get返回托管的指针，p 指向 A(2)
	cout << p->i << endl;			//输出 2
	sp1.reset(new A(3));			// reset导致托管新的指针, 此时sp1托管A(3)
	sp2.reset(new A(4));			// sp2托管A(4)
	cout << sp1->i << endl;			//输出 3
	sp3.reset(new A(5));			// sp3托管A(5),A(2)无人托管，被delete
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