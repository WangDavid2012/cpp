#pragma  once
#include <iostream>
#include <string>

#include <functional>
#include <thread>
#include <time.h>
#include "gmjtest.h"

typedef std::function<unsigned int()> pFunction;

typedef std::function<unsigned int(void *, void *)> pSdfFun;

typedef std::function<float(float)> pSpeedFunc;

class Menu
{
private:
    Menu() {};
public:
    int mainChoiceMenu();
    int gmgChoiceMenu();

    //�ӿڲ��Բ˵�
    int Menu::gmjInterfaceTestMenu();
    int Menu::gmjInterfacDevManageTestMenu();
    int Menu::gmjInterfacKeyManageTestMenu();
    int Menu::gmjInterfaceSymAlgTestMenu();
    int Menu::gmjInterfaceAsymAlgTestMenu();
    int Menu::gmjInterfaceHashAlgTestMenu();
    int Menu::gmjInterfaceFileManageMenu();

    //�㷨��ȷ�Բ��Բ˵�
    int Menu::gmjAlgCorrectTestMenu();
    int Menu::gmjSM1AlgCorrectTestMenu();
    int Menu::gmjSM2AlgCorrectTestMenu();
    int Menu::gmjSM3AlgCorrectTestMenu();
    int Menu::gmjSM4AlgCorrectTestMenu();


    //�ٶȲ��Բ˵�
    int gmjAlgSpeedTestMenu();
    int gmjSM1AlgSpeedTestMenu();
    int gmjSM2AlgSpeedTestMenu();
    //int gmjSM3AlgSpeedTestMenu();
    int gmjSM4AlgSpeedTestMenu();
    static Menu *getInstance();
private:
    static Menu *pMenu;
};



//ʱ����Ժ���
class CalculateTime
{
public:
    CalculateTime();
    ~CalculateTime();
    float runTime(int threadnum, pFunction pfunc);
    float runTime(pSdfFun pfunc);
    float runTime(pSdfFun pfunc, pSpeedFunc f);


private:
    void *m_phDeviceHandle;
    void *m_phSesshandle[THREAD_NUM];
    void *m_phkeyHandle[THREAD_NUM];
    unsigned char m_symkey[16];

};

