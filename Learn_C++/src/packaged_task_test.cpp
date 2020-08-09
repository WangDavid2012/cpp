#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>
#include <future>
#include <functional>
/********************************************************
packaged_task��ģ��Ҳ�Ƕ�����futureͷ�ļ��У�
����װ�κοɵ��� (Callable) Ŀ�꣬
���������� lambda ���ʽ�� bind ���ʽ��������������ʹ�����첽��������
�䷵��ֵ�������쳣���洢����ͨ�� std::future ������ʵĹ���״̬�С�
����֮����һ����ͨ�Ŀɵ��ú�������ת��Ϊ�첽ִ�е�����ģ���������£�
template< class R, class ...Args >
class packaged_task< fn(Args...)>;
���У�

fn �ǿ��Ե���Ŀ��
Args �������

ͨ��packaged_task��װ�󣬿���ͨ��thread�������߷º�����ʽ������
��ִ�н������ֵ�������쳣���洢����ͨ�� std::future ������ʵĹ���״̬�С�



��ʵstd::packaged_task��std::promise�ǳ����ƣ�
����˵std::packaged_task<F>�Ƕ�
std::promise<T= std::function<F>>��
T= std::function<F>��һ�ɵ�����(�纯����lambda���ʽ��)�����˰�װ������ʹ�÷�����
������һ�ɵ�����ķ��ؽ�����ݸ�������std::future����

ע�⣺ʹ��std::packaged_task������std::future���󱣴�����������ǿɵ�����ķ��ؽ�����ͣ�
��ʾ�������ķ��ؽ��������int����ô����Ϊstd::future<int>��
������std::future<int(int)>
**********************************************************/



using namespace std;
//��ͨ����
int Add(int x, int y)
{
	return x + y;
}


void task_lambda()
{
	//��װ�ɵ���Ŀ��ʱlambda
	packaged_task<int(int, int)> task([](int a, int b) { return a + b; });

	//�º�����ʽ����������
	task(2, 10);

	//��ȡ����״̬�е�ֵ,ֱ��ready���ܷ��ؽ�������쳣
	future<int> result = task.get_future();
	cout << "task_lambda :" << result.get() << "\n";
}

void task_thread()
{
	//��װ��ͨ����
	std::packaged_task<int(int, int)> task(Add);
	future<int> result = task.get_future();
	//�������񣬷��첽
	task(4, 8);
	cout << "task_thread :" << result.get() << "\n";

	//���ù���״̬
	task.reset();
	result = task.get_future();

	//ͨ���߳����������첽����
	thread td(move(task), 2, 10);
	td.join();
	//��ȡִ�н��
	cout << "task_thread :" << result.get() << "\n";
}

int packaged_task_test0()
{
	task_lambda();
	task_thread();

	return 0;
}



int Test_Fun(int a, int b, int &c)
{
	//a=1,b=2,c=0

	//ͻ��Ч��������5s
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//c=233
	c = a + b + 230;

	return c;
}


//�μ�promise�÷���Ƚϼȿ�������÷�
int packaged_task_test1()
{
	//����һ��std::packaged_task����pt1����װ����Test_Fun
	std::packaged_task<int(int, int, int&)> pt1(Test_Fun);
	//����һ��std::future����fu1����װTest_Fun�ķ��ؽ�����ͣ�����pt1����
	std::future<int> fu1 = pt1.get_future();

	//����һ������
	int c = 0;

	//����һ���߳�t1����pt1����Ӧ�Ĳ����ŵ��߳�����ִ��
	std::thread t1(std::move(pt1), 1, 2, std::ref(c));

	//�������߳�t1����(����Test_Fun���ؽ��)
	int iResult = fu1.get();

	std::cout << "ִ�н����" << iResult << std::endl;	//ִ�н����233
	std::cout << "c��" << c << std::endl;				//c��233

	return 1;
}