#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>    //ʹ��������������Ҫ����ͷ�ļ�
using namespace std::placeholders;

class Application {
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	bool m_bDataLoaded;
public:
	Application() {
		m_bDataLoaded = false;
	}

	void loadData() {
		//ʹ���߳�sleep 1��
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Loading Data from XML" << std::endl;

		//��������
		std::lock_guard<std::mutex> guard(m_mutex);

		//flag��Ϊtrue�����������Ѽ���
		m_bDataLoaded = true;

		//֪ͨ��������
		m_condVar.notify_one();
	}

	bool isDataLoaded() {
		return m_bDataLoaded;
	}

	void mainTask() {
		std::cout << "Do some handshaking" << std::endl;

		//��ȡ��
		std::unique_lock<std::mutex> mlock(m_mutex);

		//��ʼ�ȴ����������õ��ź�
		//wait()�����ڲ��ͷ�������ʹ�߳�����---------ע��˴�
		//һ���������������źţ���ָ��̲߳��ٴλ�ȡ��
		//Ȼ���������Ƿ����㣬����������㣬������������ٴν���wait
		//�൱�� auto fun = std::bind(&Application::isDataLoaded, this)
		//���bind���÷�������1 &Application::isDataLoaded��ʾ��Ӧ�İ󶨺���
		//����2�����ڲ���1ʹ�õ���ķ������˲�����ʾ������Ǹ��࣬û�в���3����ʾvoid
		//m_condVar.wait(mlock, fun());
		m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
		std::cout << "Do Processing On loaded Data" << std::endl;
	}
};

int test7() {
	Application app;
	std::thread thread_1(&Application::mainTask, &app);
	std::thread thread_2(&Application::loadData, &app);
	thread_2.join();
	thread_1.join();

	return 0;
}