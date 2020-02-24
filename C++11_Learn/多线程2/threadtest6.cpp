#include <iostream>
#include <thread>
#include <mutex>

class Application
{
	std::mutex m_mutex;
	bool m_bDataLoaded;
public:
	Application() {
		m_bDataLoaded = false;
	}

	void loadData() {
		//使该线程sleep 1秒
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Load Dada from Xml" << std::endl;

		//锁定数据
		std::lock_guard<std::mutex> guard(m_mutex);

		//flag设为true，表明数据已加载
		m_bDataLoaded = true;
	}

	void mainTask() {
		std::cout << "Do some Handshaking" << std::endl;

		//获得锁
		m_mutex.lock();
		//检测flag是否设为true
		while (m_bDataLoaded != true) {
			//释放锁
			m_mutex.unlock();
			//sleep 100ms
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//获取锁
			m_mutex.lock();
		}
		m_mutex.unlock();
		//处理加载的数据
		std::cout << "Do Processing On loaded Data" << std::endl;
	}
};

int test6() {
	Application app;

	std::thread thread_1(&Application::mainTask, &app);
	std::thread thread_2(&Application::loadData, &app);

	thread_2.join();
	thread_1.join();

	return 0;
}