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
		//ʹ���߳�sleep 1��
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Load Dada from Xml" << std::endl;

		//��������
		std::lock_guard<std::mutex> guard(m_mutex);

		//flag��Ϊtrue�����������Ѽ���
		m_bDataLoaded = true;
	}

	void mainTask() {
		std::cout << "Do some Handshaking" << std::endl;

		//�����
		m_mutex.lock();
		//���flag�Ƿ���Ϊtrue
		while (m_bDataLoaded != true) {
			//�ͷ���
			m_mutex.unlock();
			//sleep 100ms
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//��ȡ��
			m_mutex.lock();
		}
		m_mutex.unlock();
		//������ص�����
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