#include <iostream>
#include <thread>

using namespace std;


//ʹ�ú������󴴽��߳�
class DisplayThread {
public:
	void operator ()() {
		for (int i = 0; i < 100; i++)
			std::cout << "Display Thread Excecuting" << std::endl;
	}
};

int test234() {
	std::thread threadObj((DisplayThread()));
	for (int i = 0; i < 100; i++)
		std::cout << "Display From Main Thread " << std::endl;
	std::cout << "Waiting For Thread to complete" << std::endl;
	threadObj.join();
	std::cout << "Exiting from Main Thread" << std::endl;

	return 0;
}