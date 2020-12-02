#include <iostream>
#include <string>
#include <thread>
#include <windows.h>

#include <thread>
#include <string>
#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <mutex>
#include <chrono>
#include <time.h>

#include "sdf_time.hpp"

#include "sdf_time.hpp"
#include "./sdf/SDF.h"
#include "./sdf/SDF_EX.h"
#include "gmjtest.h"



using namespace std;
using std::cout;
using std::endl;
using std::thread;
using std::vector;




float SYM_crypto_time_test(float secs)
{
    float speed = 0.0;
    speed = (float)(TEST_NUM * 1.0 * TESTLENTH * 8.0 * THREAD_NUM / (1000 * 1000 * secs));
    std::cout << " the ftime is " << secs << endl;
    std::cout << "ThreadNum:" << THREAD_NUM << " SendDatalenth:" << TESTLENTH << " Speed:" << speed << "Mbps" << endl;
    return speed;
}

float ASYM_crypto_time_test(float secs)
{
    float speed = 0.0;
    speed = (float)(TEST_NUM * 1.0 * THREAD_NUM / (secs));
    std::cout  << " the ftime is " << secs << endl;
    std::cout << "ThreadNum:" << THREAD_NUM << " SendDatalenth:" << TESTLENTH << " Speed:" << speed << "tps" << endl;
    return speed;
}







int main_test1()
{
    static HANDLE phDeviceHandle = nullptr;
#ifdef _WIN32
    extern BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
    DllMain(NULL, DLL_PROCESS_ATTACH, NULL);
#else
    extren void __attribute__((constructor)) sdf_lib_init();
    sdf_lib_init();
#endif

    unsigned char indata[4096] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                 };
    int ret;
    unsigned int inlenth = 0, outlenth = 0;
    unsigned char outdata[4096] = { 0 };
    unsigned char iv[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };
    unsigned char symkey[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };


    ret = SDF_OpenDevice(&phDeviceHandle);

    HANDLE phSesshandle[THREAD_NUM];
    HANDLE phkeyHandle[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM; i++) {
        ret = SDF_OpenSession(phDeviceHandle, &phSesshandle[i]);
    }
    for (int i = 0; i < THREAD_NUM; i++) {
        ret = SDF_ImportKey(phSesshandle[i], symkey, 16, &phkeyHandle[i]);
    }
    cout << "================= Time test start ============" << endl;

    vector<std::shared_ptr<thread>> g_pmthread;
    float ftime1 = 0, ftime2 = 0;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < THREAD_NUM; i++) {				  
        auto f = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_ENC, phSesshandle[i], phkeyHandle[i], SGD_SM4_CBC,  TEST_NUM);
        g_pmthread.push_back(std::make_shared<thread>(f));

    }

    for (auto &thread : g_pmthread) {
        thread->join();
    }

    end = clock();
    float dur = (float)(end - start - THREAD_NUM);

    ftime1 = (dur / CLOCKS_PER_SEC);
    float speed = 0.0;
    speed = (float)(TEST_NUM * 1.0 * TESTLENTH * 8.0 * THREAD_NUM / (1024 * 1024 * ftime1));
    cout << "ThreadNum:" << THREAD_NUM << " SendDatalenth:" << TESTLENTH << " Speed:" << speed << "Mbps" << endl;


    for (int i = 0; i < THREAD_NUM; i++) {
        ret = SDF_DestroyKey(phSesshandle[i],  phkeyHandle[i]);
    }
    for (int i = 0; i < THREAD_NUM; i++) {
        ret = SDF_CloseSession(phSesshandle[i]);
    }
    system("pause");
    ret = SDF_CloseDevice(phDeviceHandle);

    WSACleanup();

    return 0;
}




int main()
{
    //static HANDLE phDeviceHandle = nullptr;
#ifdef _WIN32
    extern BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
    DllMain(NULL, DLL_PROCESS_ATTACH, NULL);
#else
    extren void __attribute__((constructor)) sdf_lib_init();
    sdf_lib_init();
#endif

    std::cout << "****************Speed time start***********************" << endl;
    CalculateTime *pCalTime = new CalculateTime();


    // 	Menu *ptrMenu = Menu::getInstance();
    // 	int choice = ptrMenu->mainChoiceMenu();
    // 	while (1)
    // 	{
    // 		switch (choice)
    // 		{
    // 		case 0:
    // 			break;
    // 		case 1:
    // 			break;
    // 		case 2:
    // 			break;
    // 		default:
    // 			break;
    // 		}
    // 	}

    //测试ECB算法	   //测试通过 20201013
//     std::cout << "****SM4 ECB test*****" << endl;
//     std::function<int(void *, void *)> f0 = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_ENC, std::placeholders::_1, std::placeholders::_2, SGD_SM4_ECB, TEST_NUM);
//     pCalTime->runTime(f0);
//     std::cout << "****SM4 ECB finish*****" << endl;

		//测试通过 20201013
//     std::cout << "****SM4 CBC test*****" << endl;
//     std::function<int(void *, void *)> f_sm4 = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_ENC, std::placeholders::_1, std::placeholders::_2, SGD_SM4_CBC, TEST_NUM);
//     pCalTime->runTime(f_sm4);
//     std::cout << "****SM4 CBC finish*****" << endl;
	//测试通过 20201013
// 	std::cout << "****SM1 CBC test*****" << endl;
// 	std::function<int(void *, void *)> f_sm1_CBC = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_ENC, std::placeholders::_1, std::placeholders::_2, SGD_SM1_CBC, TEST_NUM);
// 	pCalTime->runTime(f_sm1_CBC);
// 	std::cout << "****SM1 CBC finish*****" << endl;
	//测试通过 20201013
// 	std::cout << "****hash test*****" << endl;
// 	std::function<int(void *, void *)> f1 = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_HASH, std::placeholders::_1, std::placeholders::_2, SGD_SM3, TEST_NUM);
// 	pCalTime->runTime(f1);
// 	std::cout << "****hash finish*****" << endl;

	//测试通过 20201013
//     std::cout << "****MAC test*****" << endl;
//     std::function<int(void *, void *)> f2 = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_MAC, std::placeholders::_1, std::placeholders::_2, SGD_SM4_MAC, TEST_NUM);
//     pCalTime->runTime(f2);
//     std::cout << "****MAC test finish*****" << endl;


    //非对称算法测试
    std::function<int(void *, void *)> f3 = std::bind(gmjSDF_ASYM_Speed_test, CRYPTO_ENC, std::placeholders::_1, std::placeholders::_2, SGD_SM2_3, TEST_NUM);
    pCalTime->runTime(f3);
    std::function<int(void *, void *)> f4 = std::bind(gmjSDF_ASYM_Speed_test, CRYPTO_GENKEY, std::placeholders::_1, std::placeholders::_2, SGD_SM2_1, TEST_NUM);
    pCalTime->runTime(f4, ASYM_crypto_time_test);

    delete pCalTime;

    system("pause");
    WSACleanup();

    return 0;
}





