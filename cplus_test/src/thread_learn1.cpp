// project4.cpp: �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>

using namespace std;
//int mythread(int mypar)
//{
//	cout << "mythread() start" << " threadid = " << std::this_thread::get_id() << endl;
//	std::chrono::milliseconds dura(5000); //1�� = 1000���룬����5000���� = 5��
//	std::this_thread::sleep_for(dura); //��Ϣһ����ʱ��
//	return 5;
//}
//
////void mythread2(std::future<int> &tmpf) //ע�����
//void mythread2(std::shared_future<int> &tmpf) //ע�����
//{
//	cout << "mythread2() start" << " threadid = " << std::this_thread::get_id() << endl;
//	auto result = tmpf.get(); //��ȡֵ��ֻ��getһ�η���ᱨ�쳣
//	                           //Ϊʲô�ڶ���get���future���ǻ�õ�һ���쳣����Ҫ����Ϊget��������ƣ���һ���ƶ�����
//	cout << "mythread2 result = " << result << endl;
//	return;
//}

//int g_mycout = 0; //����һ��ȫ����
//std::atomic<int> g_mycout = 0; //���Ƿ�װ��һ������Ϊint�� ����ֵ�������ǿ��������һ��int���ͱ���һ�����������g_mycout

//std::mutex g_my_mutex; //������
//
//void mythread() //�߳���ں���
//{
//
//	for (int i = 0; i < 10000000; i++)
//	{
//		//g_my_mutex.lock(); //7����ʵ����2000��μ����ͽ�����
//		//g_mycout++;
//		//...
//		//...
//		//g_my_mutex.unlock();
//		g_mycout++; //��Ӧ�ĵĲ�����ԭ�Ӳ��������ᱻ��ϣ�
//	}
//
//	return;
//}

std::atomic<bool> g_ifend = false;  //�߳��˳���ǣ�������ԭ�Ӳ�������ֹ����д���ף�

void mythread()
{
	std::chrono::milliseconds dura(1000); //1����
	while (g_ifend == false) {
		//ϵͳûҪ���߳��˳������Ա��߳̿��Ը��Լ���ɵ�����
		cout << "thread id = " << std::this_thread::get_id() << " ������...." << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "thread id = " << std::this_thread::get_id() << " ���н���...." << endl;
	return;
}

int thread_test20()
{
	//һ��std::future��������Ա����,get()����ת������
	//����std::shared_future��Ҳ�Ǹ���ģ��,get()������������

	//cout << "main" << " threadid = " << std::this_thread::get_id() << endl;
	//std::packaged_task<int(int)> mypt(mythread);  //���ǰѺ���mythreadͨ��packaged_task��װ������
	//std::thread t1(std::ref(mypt), 1);  //�߳�ֱ�ӿ�ʼִ�У��ڶ���������Ϊ�߳���ں����Ĳ�����
	//t1.join(); //���ǿ��Ե�������ȴ��߳�ִ�����,�����������̫�У������

	////std::future<int> result = mypt.get_future();  //std::future��Ҳ�İ���ˣ���������ﺬ���߳���ں�
	////std::shared_future<int> result_s(std::move(result));
	////bool ifcanget = result.valid();
	////std::shared_future<int> result_s(result.share()); //ִ����Ϻ�result_s����ֵ����result�����
	////ifcanget = result.valid();
	//std::shared_future<int> result_s(mypt.get_future()); //ͨ��get_future����ֱֵ�ӹ�����һ��shared_future����
	//auto mythreadresult = result_s.get();
	//mythreadresult = result_s.get();
	//
	////std::thread t2(mythread2, std::ref(result));
	//std::thread t2(mythread2, std::ref(result_s));
	//t2.join(); //���߳�ִ�����
	//cout << "I Love China!" << endl;

	//����ԭ�Ӳ���std::atomic
	//��3.1��ԭ�Ӳ���������������
	//�����������̱߳���� �����������ݣ�  ���������������ݣ�����
	//�������̣߳���һ���������в���������̶߳��ñ���ֵ����һ���߳������������дֵ��
	//int atomvalue = 5;
	////���߳�A
	//int tmpvalue = atomvalue;  //�������atoomvalue������Ƕ���߳�֮��Ҫ����ı�����
	////д�߳�B
	//atomvalue = 6; //������Ļ���

	//��ҿ��԰�ԭ�Ӳ�������һ�֣�����Ҫ�õ������������������������Ķ��̲߳�����̷�ʽ
	//ԭ�Ӳ���: ���ڶ��߳��� ���ᱻ��ϵ� ����ִ��Ƭ�Σ�ԭ�Ӳ������Ȼ�����Ч���ϸ�ʤһ�
	//�������ļ���һ�������һ������Σ����д��룩����ԭ�Ӳ�����Ե�һ�㶼��һ��������������һ������Σ�

	//ԭ�Ӳ�����һ�㶼��ָ�����ɷָ�Ĳ�������Ҳ����˵���ֲ���״̬Ҫô����ɵģ�Ҫô��û��ɵģ������ܳ��ְ����״̬��
	//std::atomic������ԭ�Ӳ��� ,std::atomic�Ǹ���ģ�塣��ʵstd::atomic���������������װĳ�����͵�ֵ�ģ�

	//��3.2��������std::atomic�÷�����
	//��3.3����ʦ���ĵã�һ�����ڼ�������ͳ�ƣ��ۼƷ��ͳ�ȥ�˶��ٸ����ݰ����ۼƽ��յ��˶��ٸ����ݰ�����

	/*thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();

	cout << "�����߳�ִ����ϣ����յ�g_mycount�Ľ���ǣ�" << g_mycout << endl;

	*/
	thread mytobj1(mythread);
	thread mytobj2(mythread);
	std::chrono::milliseconds dura(5000); //5����
	std::this_thread::sleep_for(dura);
	g_ifend = true; //��ԭ�Ӷ����д���������߳��������н�����
	mytobj1.join();
	mytobj2.join();
	cout << "����ִ����ϣ��˳�" << endl;
	return 0;
}