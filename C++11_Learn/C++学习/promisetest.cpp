#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <chrono>
#include <iostream>

void accumulate(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int> accumulate_promise)
{
	int sum = std::accumulate(first, last, 0);
	accumulate_promise.set_value(sum);  // ���� future
}

void do_work(std::promise<void> barrier)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	barrier.set_value();
}

int test9()
{
	// ��ʾ�� promise<int> ���̼߳䴫�ݽ����
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
		std::move(accumulate_promise));

	// future::get() ���ȴ�ֱ���� future ӵ�кϷ������ȡ����
	// ������ get() ǰ���� wait()
	//accumulate_future.wait();  // �ȴ����
	std::cout << "result=" << accumulate_future.get() << '\n';
	work_thread.join();  // wait for thread completion

						 // ��ʾ�� promise<void> ���̼߳��״̬���ź�
	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	barrier_future.wait();
	new_work_thread.join();
	return 0;
}

void initiazer(std::promise<int>* promObj) {
	std::cout << "Inside Thread" << std::endl;
	promObj->set_value(35);
}

int test10() {
	std::promise<int> promiseObj;
	std::future<int> futureObj = promiseObj.get_future();
	std::thread th(initiazer, &promiseObj);
	std::cout << futureObj.get() << std::endl;
	th.join();

	return 0;
}