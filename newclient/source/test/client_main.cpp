/************************************************
*********主要进行SDF接口测试
*********************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#include "SDF_Test.hpp"
#include "./sdf/SDF.h"
#include "config.h"
#include "debug.h"


#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

using std::cout;
using std::endl;


HANDLE phDeviceHandle = nullptr;
HANDLE phSessionHandle = nullptr;


int main(int argc, char **argv)
{
	//在动态库加载之前需要执行的部分
#ifdef _WIN32
	extern BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
	DllMain(NULL, DLL_PROCESS_ATTACH, NULL);
#else
	extren void __attribute__((constructor)) sdf_lib_init();
	sdf_lib_init();
#endif

	u32 ret = 0;
	ret = SDF_OpenDevice(&phDeviceHandle);
	mydebug << "SDF_OpenDevice " << endl;
	ret = SDF_OpenSession(phDeviceHandle, &phSessionHandle);
	SDFtest *sdftest = new SDFtest(phDeviceHandle, phSessionHandle);



//  	while (1){
//  		//sdftest->hmacTest();  
//  		sdftest->calculateMacTest();          //测试通过SM1/4 MAC 测试完成
//  		Sleep(10);
//  	}


	while (1)
	{
		sdftest->correct_SM2PreSign();
		sdftest->correct_SM2PreVerify();
		sdftest->randTest();
		sdftest->hashWithPubTest();           //测试通过
		sdftest->SM4_test();                  //测试通过
		sdftest->internalEccSignVerifyTest(); //测试通过
		sdftest->internalEccTest();           //测试通过
		sdftest->kekTest();                   //测试通过
		sdftest->externEccPubKeyTest();       //测试通过
		sdftest->aggrementEccTest();          //测试通过
		sdftest->hashTest();                  //测试通过
		sdftest->pubkeyVerify();              //测试通过
		//sdftest->externalSignTest();          //测试通过
		sdftest->hmacTest();                  //测试通过
		sdftest->sm1sm4Test();                //测试通过	
		sdftest->calculateMacTest();          //测试通过SM1/4 MAC 测试完成
	    //while (1);
	}


	delete sdftest;
	ret = SDF_CloseSession(phSessionHandle);
	ret = SDF_CloseDevice(phDeviceHandle);
	return 0;

	//sdftest->externalEccSignVerifyTest(); //新的接口不支持
}