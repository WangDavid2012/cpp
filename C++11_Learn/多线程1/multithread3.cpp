#if 0
//linux版本多线程

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <string>
#include <unistd.h>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
struct info
{
	string name;
	unsigned s_time;//sleep时间
};
void *start_routine(void *arg)
{
	info *t_arg = (info *)arg;
	for (unsigned i = 0; i != 5U; ++i)
	{
		cout << t_arg->name << endl;
		sleep(t_arg->s_time);
	}
	return (void *)t_arg;
}
constexpr unsigned THREAD_N = 2;//线程的数量
int main()
{
	pthread_t tid[THREAD_N];
	//pthread_attr_t *attr1 = nullptr, *attr2 = nullptr;
	int ret[THREAD_N];
	info args[THREAD_N] = { "Win", 1U, "Unix", 2U };
	for (unsigned i = 0; i != THREAD_N; ++i)
	{
	
// 		pthread_attr_t attr;
// 		ret[i] = pthread_create(&tid[i], &attr, &start_routine, &args[i]);
// 		attr需由pthread_attr_init()进行初始化，此处产生了EAGAIN错误
	
		ret[i] = pthread_create(&tid[i], nullptr, &start_routine, &args[i]);
		if (ret[i] != 0)
		{
			if (ret[i] == EAGAIN)
			{
				cerr << args[i].name << " : 超出系统限制" << endl;
			}
			else if (ret[i] == EINVAL)
			{
				cerr << args[i].name << " : pthread_attr_t设置无效" << endl;
			}
			else
			{
				cerr << args[i].name << ": unkown error" << endl;
			}
			exit(-1);
		}
	}

// 	对于pthread_join(),如果线程tid的start_routine已经执行完毕，
// 	pthrea_join仍能正常返回，这说明start_routine执行完毕后线程
// 	资源并没有被收回

	void *status[THREAD_N];
	for (unsigned i = 0; i != THREAD_N; ++i)
	{
		ret[i] = pthread_join(tid[i], &status[i]);
		if (ret[i] != 0)
		{
			if (ret[i] == ESRCH)
			{
				cerr << "pthread_join():ESRCH 没有找到与给定线程ID相对应的线程" << endl;
			}
			else if (ret[i] == EDEADLK)
			{
				cerr << "pthread_join():EDEADLKI 产生死锁" << endl;
			}
			else if (ret[i] == EINVAL)
			{
				cerr << "pthread_join():EINVAL 与给定的县城ID相对应的线程是分离线程" << endl;
			}
			else
			{
				cerr << "pthread_join():unknow error" << endl;
			}
			exit(-1);
		}
	}

// 	ret[0] = pthread_join(tid[0], &status[0]);
// 	cerr << (ret[0] == ESRCH);
// 	由于线程tid[0]的资源已被收回，所以此处产生ESRCH

	return 0;
}

#endif
