#pragma once
#include "./sdf/SDF.h"
#include "./sdf/SDF_EX.h"


// #define TESTLENTH (3936)
// #define TESTLENTH (64)
#define TESTLENTH (1984*8)
#define TEST_NUM	 64
#define THREAD_NUM	 32

#define CRYPTO_ENC		0
#define CRYPTO_DEC		1
#define CRYPTO_MAC		2
#define CRYPTO_HASH		3
#define CRYPTO_SIGN		4
#define CRYPTO_VER		5
#define CRYPTO_GENKEY	6
#define CRYPTO_RAND		7

int gmjSDF_SYM_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count);
int gmjSDF_ASYM_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count);
int gmjSDF_Hash_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count);
int gmjSDF_NetTest_Speed(HANDLE phDeviceHandle, unsigned int choice, unsigned int uiAlgID, unsigned int count);

//ÀŸ∂»≤‚ ‘
int gmjSDF_SYM_Speed_test(int choice,void* phSessionHandle, void* phKeyHandle0, unsigned int uiAlgID, unsigned int count);
int gmjSDF_ASYM_Speed_test(int choice, HANDLE phSessionHandle, HANDLE phkeyHandle, unsigned int uiAlgID, unsigned int count);