#include <iostream>
#include <chrono>

constexpr auto year = 31556952ll; // ������������ƽ������

int test4()
{
	using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;
	using jiffies = std::chrono::duration<int, std::centi>;
	using microfortnights = std::chrono::duration<float, std::ratio<14 * 24 * 60 * 60, 1000000>>;
	using nanocenturies = std::chrono::duration<float, std::ratio<100 * year, 1000000000>>;

	std::chrono::seconds sec(1);

	std::cout << "1 second is:\n";

	// �޾�����ʧ�������߶�ת������ת��
	std::cout << std::chrono::microseconds(sec).count() << " microseconds\n"
		<< shakes(sec).count() << " shakes\n"
		<< jiffies(sec).count() << " jiffies\n";

	// �о�����ʧ�������߶�ת������Ҫת��
	std::cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count()
		<< " minutes\n";

	// ����߶�ת������ת��
	std::cout << microfortnights(sec).count() << " microfortnights\n"
		<< nanocenturies(sec).count() << " nanocenturies\n";
	return 0;
}