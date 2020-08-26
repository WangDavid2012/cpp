// duration constructor
#include <iostream>
#include <ratio>
#include <chrono>

int test3()
{
	typedef std::chrono::duration<int> seconds_type;
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;

	hours_type h_oneday(24);                  // 24h
	seconds_type s_oneday(60 * 60 * 24);      // 86400s
	milliseconds_type ms_oneday(s_oneday);    // 86400000ms

	seconds_type s_onehour(60 * 60);            // 3600s
												//hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
	hours_type h_onehour(std::chrono::duration_cast<hours_type>(s_onehour));
	milliseconds_type ms_onehour(s_onehour);    // 3600000ms (ok, no type truncation)

	std::cout << ms_onehour.count() << "ms in 1h" << std::endl;

	return 0;
}

//duration����һ����Ա����count()����Rep���͵�Period�����������룺

// duration::count
//#include <iostream>     // std::cout
//#include <chrono>       // std::chrono::seconds, std::chrono::milliseconds
// std::chrono::duration_cast

int test2()
{
	using namespace std::chrono;
	// std::chrono::milliseconds is an instatiation of std::chrono::duration:
	milliseconds foo(1000); // 1 second
	foo *= 60;

	std::cout << "duration (in periods): ";
	std::cout << foo.count() << " milliseconds.\n";

	std::cout << "duration (in seconds): ";
	std::cout << foo.count() * milliseconds::period::num / milliseconds::period::den;
	std::cout << " seconds.\n";

	return 0;
}