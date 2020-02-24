#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

//�̺߳���
void func(int a, int b, int c)
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	cout << a << " " << b << " " << c << endl;
}

int test321()
{
	//�����̶߳���t1,���̺߳���Ϊfunc
	std::thread t1(func, 1, 2, 3);
	//���t1���߳�ID
	std::cout << "ID:" << t1.get_id() << std::endl;
	//�ȴ�t1�̺߳���ִ�н���
	t1.join();
	std::thread t2(func, 2, 3, 4);
	//��ִ̨��t2���̺߳���,���Ҳ�����Ϊmain��������ʱ,�̺߳���δִ����������쳣
	t2.detach();
	cout << "after t2 ,main is runing" << endl;
	//��lambda���ʽ��Ϊ���ﶥ���̺߳���
	std::thread t4([](int a, int b, int c)
	{
		//�߳�����5��
		std::this_thread::sleep_for(std::chrono::seconds(5));
		cout << a << " " << b << " " << c << endl;
	}, 4, 5, 6);
	t4.join();

	//��ȡCPU�ĺ���
	cout << "CPU: " << thread::hardware_concurrency() << endl;
	//���������ע�͵��������׳��쳣,��Ϊ�̶߳��������̺߳���������,Ӧ�ñ�֤�̶߳���������������̺߳���ִ����ʱ��Ȼ����.
	//std::thread t3(func, 3, 4, 5);
	getchar();

	return 0;
}