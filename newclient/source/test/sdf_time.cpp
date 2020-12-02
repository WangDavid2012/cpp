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
#include "gmjtest.h"

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using namespace std;



Menu  *Menu::pMenu = new Menu();

int Menu::mainChoiceMenu()
{
    cout << endl << endl;
    cout << "============================== 测试用例 ================================" << endl;
    cout << "\t\t\t1. 国密局测试" << endl;
    cout << "\t\t\t2. 自测试" << endl;
    cout << "\t\t\t3. 稳定性测试" << endl;
    cout << "\t\t\t4. 退出" << endl;
    cout << "========================================================================" << endl;
    cout << "请输入您的选择:" << endl;
    int choice = 0;
    cin >> choice;
    return choice;
}

int Menu::gmgChoiceMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================== 测试用例 ================================\n\n");
    printf("                           1. 密码接口测试\n\n");
    printf("                           2. 算法正确性测试\n\n");
    printf("                           3. 算法性能测试 \n\n");
    printf("                           4. 互操作性测试\n\n");
    printf("                           5. 全部测试\n\n");
    printf("                           0. 退出\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 5) || (choice < 0)) {
        goto choice_loop;
    }

    return choice;
}

/*******************************************************************************************/
int Menu::gmjInterfaceTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================= 密码接口测试 =============================\n\n");
    printf(" 1. 设备管理类函数测试                        2. 密钥管理类函数测试\n\n");
    printf(" 3. 对称算法运算类函数测试                     4. 非对称算法运算类函数测试\n\n");
    printf(" 5. 杂凑算法运算类函数测试                     6. 文件管理类函数测试\n\n");
    printf(" 7. 全部测试                                 8. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 8) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}



int Menu::gmjInterfacDevManageTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("========================== 设备管理接口测试 ============================\n\n");
    printf(" 1. 打开关闭密码设备                          2. 打开关闭会话\n\n");
    printf(" 3. 获取设备信息                              4. 随机数产生\n\n");
    printf(" 5. 获取释放私钥使用权限(正确私钥授权码)      6. 获取释放私钥权限(错误私钥码)\n\n");
    printf(" 7. 全部测试                                  8. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 8) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjInterfacKeyManageTestMenu()
{
    int choice = 0;
choice_loop:

    printf("\n\n");
    printf("========================== 密钥管理接口测试 ============================\n\n");
    printf(" 1. 导出SM2加密/签名公钥                      2. 产生SM2密钥对\n\n");
    printf(" 3. 会话密钥测试                              4. 密钥协商\n\n");
    printf(" 5. 全部测试                                  6. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;




    if ((choice > 6) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjInterfaceSymAlgTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("========================== 对称算法接口测试 ============================\n\n");
    printf(" 1. SM1_ECB对称运算                           2. SM1_CBC对称运算\n\n");
    printf(" 3. SM1_CFB对称运算                           4. SM1_OFB对称运算\n\n");
    printf(" 5. SM4_ECB对称运算                           6. SM4_CBC对称运算\n\n");
    printf(" 7. SM4_CFB对称运算                           8. SM4_CBC对称运算\n\n");
    printf(" 9. SM1_MAC对称运算                           10.SM4_MAC对称运算\n\n");
    printf(" 11.全部测试                                  12.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 12) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjInterfaceAsymAlgTestMenu()
{
    int choice = 0;
choice_loop:


    printf("\n\n");
    printf("========================== 非对称算法接口测试 ==========================\n\n");
    printf(" 1. 外部密钥SM2签名验签                       2. 内部密钥SM2签名验签\n\n");
    printf(" 3. 外部密钥SM2加密解密                       4. 全部测试\n\n");
    printf(" 5. 返回 \n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;



    if ((choice > 5) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjInterfaceHashAlgTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("=========================== 杂凑算法接口测试 ==========================\n\n");
    printf(" 1. SM3运算(带公钥和ID)                       2. SM3运算(不带公钥和ID)\n\n");
    printf(" 3. 全部测试                                  4. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 4) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjInterfaceFileManageMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("=========================== 文件管理接口测试 ==========================\n\n");
    printf(" 1. 创建文件                                  2. 写入文件\n\n");
    printf(" 3. 读取文件                                  4. 删除文件\n\n");
    printf(" 5. 全部测试                                  6. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 6) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}







/*******************************************************************************************/
int Menu::gmjAlgCorrectTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ 算法正确性测试 ============================\n\n");
    printf(" 1. SM1算法正确性检测                         2. SM2算法正确性检测\n\n");
    printf(" 3. SM3算法正确性检测                         4. SM4算法正确性检测\n\n");
    printf(" 5. 全部测试                                  6. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 6) || (choice < 1)) {
        goto choice_loop;
    }
    return choice;
}
int Menu::gmjSM1AlgCorrectTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ SM1算法正确性测试 =========================\n\n");
    printf(" 1. SM1_ECB加密算法正确性                     2. SM1_CBC加密算法正确性\n\n");
    printf(" 3. SM1_CFB加密算法正确性                     4. SM1_OFB加密算法正确性\n\n");
    printf(" 5. SM1_ECB解密算法正确性                     6. SM1_CBC解密算法正确性\n\n");
    printf(" 7. SM1_CFB解密算法正确性                     8. SM1_OFB解密算法正确性\n\n");
    printf(" 9. SM1_MAC算法正确性                         10.全部测试\n\n");
    printf(" 11.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 11) || (choice < 1)) {
        goto choice_loop;
    }

    return 0;
}

int Menu::gmjSM2AlgCorrectTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ SM2算法正确性测试 =========================\n\n");
    printf(" 1. SM2加密算法正确性                         2. SM2解密算法正确性\n\n");
    printf(" 3. SM2签名预处理正确性                       4. SM2签名无预处理正确性\n\n");
    printf(" 5. SM2验签预处理正确性                       6. SM2验签无预处理正确性\n\n");
    printf(" 7. SM2密钥对生成正确性                       8. SM2密钥协商发起方正确性\n\n");
    printf(" 9. SM2密钥协商响应方正确性                   10.全部测试\n\n");
    printf(" 11.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 11) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}

int Menu::gmjSM3AlgCorrectTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("=========================== SM3算正确性测试 ============================\n\n");
    printf(" 1. SM3运算(不带公钥和ID)                       2. SM3运算(带公钥和ID)\n\n");
    printf(" 3. 全部测试                                   4. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 4) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}


int Menu::gmjSM4AlgCorrectTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ SM4算法正确性测试 =========================\n\n");
    printf(" 1. SM4_ECB加密算法正确性                     2. SM4_CBC加密算法正确性\n\n");
    printf(" 3. SM4_CFB加密算法正确性                     4. SM4_OFB加密算法正确性\n\n");
    printf(" 5. SM4_ECB解密算法正确性                     6. SM4_CBC解密算法正确性\n\n");
    printf(" 7. SM4_CFB解密算法正确性                     8. SM4_OFB解密算法正确性\n\n");
    printf(" 9. SM4_MAC算法正确性                         10.全部测试\n\n");
    printf(" 11.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 11) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}

int Menu::gmjAlgSpeedTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("================================ 性能测试 ==============================\n\n");
    printf(" 1. SM1算法性能                               2. SM2算法性能\n\n");
    printf(" 3. SM3算法性能                               4. SM4算法性能\n\n");
    printf(" 5. 随机数性能                                6. ECC密钥对产生性能 \n\n");
    printf(" 7. 全部测试　                                8. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 8) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}

int Menu::gmjSM1AlgSpeedTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ SM1算法性能测试 ===========================\n\n");
    printf(" 1. SM1_ECB加密性能                           2. SM1_CBC加密性能\n\n");
    printf(" 3. SM1_CFB加密性能                           4. SM1_OFB加密性能\n\n");
    printf(" 5. SM1_ECB解密性能                           6. SM1_CBC解密性能\n\n");
    printf(" 7. SM1_CFB解密性能                           8. SM1_OFB解密性能\n\n");
    printf(" 9. SM1_MAC性能                               10.全部测试\n\n");
    printf(" 11.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 11) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}

int Menu::gmjSM2AlgSpeedTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================= SM2算法性能测试 ==========================\n\n");
    printf(" 1. SM2加密性能                               2. SM2解密性能\n\n");
    printf(" 3. SM2签名性能                               4. SM2验签性能\n\n");
    printf(" 5. SM2密钥对产生性能                         6. 全部测试\n\n");
    printf(" 7. 返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 7) || (choice < 1)) {
        goto choice_loop;
    }

    return choice;
}

int Menu::gmjSM4AlgSpeedTestMenu()
{
    int choice = 0;
choice_loop:
    printf("\n\n");
    printf("============================ SM4算法性能测试 ===========================\n\n");
    printf(" 1. SM4_ECB加密性能                           2. SM4_CBC加密性能\n\n");
    printf(" 3. SM4_CFB加密性能                           4. SM4_OFB加密性能\n\n");
    printf(" 5. SM4_ECB解密性能                           6. SM4_CBC解密性能\n\n");
    printf(" 7. SM4_CFB解密性能                           8. SM4_OFB解密性能\n\n");
    printf(" 9. SM4_MAC性能                               10.全部测试\n\n");
    printf(" 11.返回\n\n");
    printf("========================================================================\n");
    printf("Select:");
    cin >> choice;

    if ((choice > 11) || (choice < 1)) {
        goto choice_loop;
    }
    return choice;
}




Menu *Menu::getInstance()
{
    if (pMenu == nullptr) {
        pMenu = new Menu();
    }
    return pMenu;
}


/************************************ 计算时间相关的类 *********************************/
CalculateTime::CalculateTime()

{

    int ret = 0;

    for (int i = 0; i < 16; i++)

    {

        m_symkey[i] = i;

    }

    ret = SDF_OpenDevice(&m_phDeviceHandle);

    for (int i = 0; i < THREAD_NUM; i++) {

        ret = SDF_OpenSession(m_phDeviceHandle, &m_phSesshandle[i]);

    }

    for (int i = 0; i < THREAD_NUM; i++) {

        ret = SDF_ImportKey(m_phSesshandle[i], m_symkey, 16, &m_phkeyHandle[i]);

    }



}





CalculateTime::~CalculateTime()

{

    int ret = 0;

    for (int i = 0; i < THREAD_NUM; i++) {

        ret = SDF_DestroyKey(m_phSesshandle[i], m_phkeyHandle[i]);

    }

    for (int i = 0; i < THREAD_NUM; i++) {

        ret = SDF_CloseSession(m_phSesshandle[i]);

    }

    ret = SDF_CloseDevice(m_phDeviceHandle);

}







extern int gmjSDF_SYM_Speed_test(int choice, HANDLE phSessionHandle, HANDLE phKeyHandle0, \

                                 unsigned int uiAlgID, unsigned int count);





auto f = std::bind(gmjSDF_SYM_Speed_test, CRYPTO_ENC, placeholders::_1, placeholders::_2, SGD_SM4_ECB, THREAD_NUM);



float CalculateTime::runTime(int threadnum, pFunction pfunc)
{
    vector<std::shared_ptr<thread>> g_pmthread;

    clock_t start, end;
    start = clock();
    for (int i = 0; i < threadnum; i++) {
        g_pmthread.push_back(std::make_shared<thread>(pfunc));
    }
    for (auto &thread : g_pmthread) {
        thread->join();
    }
    end = clock();
    float dur = (float)(end - start - threadnum);
    return (dur / CLOCKS_PER_SEC);
}





float CalculateTime::runTime(pSdfFun pfunc)
{
    vector<std::shared_ptr<thread>> g_pmthread;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < THREAD_NUM; i++) {
        g_pmthread.push_back(std::make_shared<thread>(pfunc, m_phSesshandle[i], m_phkeyHandle[i]));
    }
    for (auto &thread : g_pmthread) {
        thread->join();
		std::cout << "****************** finish a therad *********** " << std::endl;
    }
    end = clock();
    float dur = (float)(end - start - THREAD_NUM);

    float ftime1 = (dur / CLOCKS_PER_SEC);

    float speed = 0.0;

    speed = (float)(TEST_NUM * 1.0 * TESTLENTH * 8.0 * THREAD_NUM / (1000 * 1000 * ftime1));

    std::cout << "The dur is " << dur << " the ftime is " << ftime1 << endl;
    std::cout << "ThreadNum:" << THREAD_NUM << " SendDatalenth:" << TESTLENTH << " Speed:" << speed << "Mbps" << endl;
    return speed;
}




float CalculateTime::runTime(pSdfFun pfunc, pSpeedFunc f)
{
    vector<std::shared_ptr<thread>> g_pmthread;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < THREAD_NUM; i++) {
        g_pmthread.push_back(std::make_shared<thread>(pfunc, m_phSesshandle[i], m_phkeyHandle[i]));
    }
    for (auto &thread : g_pmthread) {
        thread->join();
    }
    end = clock();
    float dur = (float)(end - start - THREAD_NUM);

    float ftime1 = (dur / CLOCKS_PER_SEC);





    return f(ftime1);

    //float speed = 0.0;
    //speed = (float)(TEST_NUM * 1.0 * TESTLENTH * 8.0 * THREAD_NUM / (1000 * 1000 * ftime1));
    //std::cout << "The dur is " << dur << " the ftime is " << ftime1 << endl;
    //std::cout << "ThreadNum:" << THREAD_NUM << " SendDatalenth:" << TESTLENTH << " Speed:" << speed << "Mbps" << endl;
    //return speed;
}



