// SoftAlg.cpp : 定义控制台应用程序的入口点。
/**************************************
*	文件：SoftAlg.cpp
*	功能：封装软算法SM2/3/4
*	作者：Lewis
*	时间：2016-10-24
**************************************/

#include "stdafx.h"
#include <Windows.h>
#include ".\sm2\sm2.h"
#include ".\sm3\sm3.h"
#include ".\sm4\sm4.h"



#define ECCref_MAX_LEN 64

//
//JNIEXPORT void JNICALL Java_com_cist_SoftAlgNative_forTest
//(JNIEnv *, jobject)
//{
//	printf("Jni work well...\n");
//}

/*
*@功能：软库SM2加密解密检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM2Check();

/*
*@功能：软库SM2签名验签检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM2SignCheck();

/*
*@功能：软库SM3检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM3Check();

/*
*@功能：软库SM4检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM4Check();



int VerifySign(unsigned char *pSignMsg, unsigned long ulSignMsgLen,
	unsigned char *pSignature, unsigned long ulSignLen);

//16进制格式输出数据
void _PRINT_Message_Bin1(unsigned char *msgBin, unsigned int msgBinLen)
{
	unsigned int i, j;

	printf("            ");
	j = 0;
	for (i = 0; i < msgBinLen; i++) {
		printf("%02X ", msgBin[i]);
		j++;
		if (j >= 16) {
			printf("\n");
			printf("            ");
			j = 0;
		}
	}

	printf("\n");
	return;
}


int _tmain(int argc, _TCHAR* argv[])
{

	if (0 == SoftSM2SignCheck())
	{
		printf("SoftSM2 Sign and Verify check PASS...\n");
	}
	else
	{
		printf("SoftSM2 Sign and Verify check FAILED...\n");
	}
	if (0 == SoftSM2Check())
	{
		printf("SoftSM2 Encrypt and Decrypt check PASS...\n");
	}
	else
	{
		printf("SoftSM2 Encrypt and Decrypt check FAILED...\n");
	}
	if (0 == SoftSM3Check())
	{
		printf("SoftSM3 check PASS...\n");
	}
	else
	{
		printf("SoftSM3 check FAILED...\n");
	}
	if (0 == SoftSM4Check())
	{
		printf("SoftSM4 check PASS...\n");
	}
	else
	{
		printf("SoftSM4 check FAILED...\n");
	}
	system("pause");
	return 0;
}


/*
*@功能：软库SM2加密解密检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM2Check()
{
	/*软库SM2检测*/
	//检测软库SM2加解密算法
	sm2_keypair testKey;
	SM2_initKeyPair(&testKey);
	unsigned char pbEccPub_X[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x09,0xf9,0xdf,0x31 ,0x1e,0x54,0x21,0xa1, 0x50,0xdd,0x7d,0x16 ,0x1e,0x4b,0xc5,0xc6 ,
		0x72,0x17,0x9f,0xad ,0x18,0x33,0xfc,0x07,0x6b,0xb0,0x8f,0xf3 ,0x56,0xf3,0x50,0x20 };
	unsigned char pbEccPub_Y[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0xcc,0xea,0x49,0x0c ,0xe2,0x67,0x75,0xa5,  0x2d,0xc6,0xea,0x71 ,0x8c,0xc1,0xaa,0x60 ,
		0x0a,0xed,0x05,0xfb ,0xf3,0x5e,0x08,0x4a ,0x66,0x32,0xf6,0x07 ,0x2d,0xa9,0xad,0x13 };
	unsigned char pbEccPriv_D[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x39,0x45,0x20,0x8f,0x7b,0x21,0x44,0xb1,0x3f,0x36,0xe3,0x8a,0xc6,0xd3,0x9f,0x95,
		0x88,0x93,0x93,0x69,0x28,0x60,0xb5,0x1a,0x42,0xfb,0x81,0xef,0x4d,0xf7,0xc5,0xb8 };
	unsigned char endata[115] = {
		0x04, 0xeb, 0xfc, 0x71, 0x8e, 0x8d, 0x17, 0x98, 0x62, 0x04, 0x32, 0x26, 0x8e, 0x77, 0xfe, 0xb6,
		0x41, 0x5e, 0x2e, 0xde, 0x0e, 0x07, 0x3c, 0x0f, 0x4f, 0x64, 0x0e, 0xcd, 0x2e, 0x14, 0x9a, 0x73,
		0xe8, 0x58, 0xf9, 0xd8, 0x1e, 0x54, 0x30, 0xa5, 0x7b, 0x36, 0xda, 0xab, 0x8f, 0x95, 0x0a, 0x3c,
		0x64, 0xe6, 0xee, 0x6a, 0x63, 0x09, 0x4d, 0x99, 0x28, 0x3a, 0xff, 0x76, 0x7e, 0x12, 0x4d, 0xf0,
		0x59, 0x98, 0x3c, 0x18, 0xf8, 0x09, 0xe2, 0x62, 0x92, 0x3c, 0x53, 0xae, 0xc2, 0x95, 0xd3, 0x03,
		0x83, 0xb5, 0x4e, 0x39, 0xd6, 0x09, 0xd1, 0x60, 0xaf, 0xcb, 0x19, 0x08, 0xd0, 0xbd, 0x87, 0x66,
		0x21, 0x88, 0x6c, 0xa9, 0x89, 0xca, 0x9c, 0x7d, 0x58, 0x08, 0x73, 0x07, 0xca, 0x93, 0x09, 0x2d,
		0x65, 0x1e, 0xfa };
	unsigned char msg[19] = { 0x65, 0x6e, 0x63, 0x72, 0x79, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x72, 0x64 };
	//初始化SM2密钥对
	SM2_genKeyPair(&testKey);
	mpi_read_binary(&testKey.d, pbEccPriv_D + 32, 32);
	mpi_read_binary(&testKey.Q.X, pbEccPub_X + 32, 32);
	mpi_read_binary(&testKey.Q.Y, pbEccPub_Y + 32, 32);
	//SM2解密数据，并与预置数据对比，验证SM2解密算法正确性
	int nRet = SM2_decrypt_size(&testKey, sizeof(endata));
	//printf("nRet = %d\n", nRet);
	unsigned char *orgdata = (unsigned char *)malloc(nRet);
	unsigned int orglen = nRet;
	memset(orgdata, 0, orglen);
	SM2_decrypt(endata, sizeof(endata), orgdata, &orglen, &testKey, SM2_VER_2);
	if (orglen != sizeof(msg) || 0 != memcmp(orgdata, msg, sizeof(msg)))
	{
		printf("SM2_decrypt failed...\n");
		return -1;
	}

	//SM2加密数据
	nRet = SM2_encrypt_size(&testKey, sizeof(msg));
	unsigned char *pbCipherData = (unsigned char *)malloc(nRet);
	unsigned int uiCipherLen = nRet;
	SM2_encrypt(msg, sizeof(msg), pbCipherData, &uiCipherLen, &testKey, SM2_VER_2);
	//SM2解密数据，并与明文对比
	unsigned char *pbPlainData = NULL;
	unsigned int uiPlainLen = sizeof(msg);
	nRet = SM2_decrypt_size(&testKey, uiCipherLen);
	pbPlainData = (unsigned char *)malloc(nRet);
	uiPlainLen = nRet;
	SM2_decrypt(pbCipherData, uiCipherLen, pbPlainData, &uiPlainLen, &testKey, SM2_VER_2);
	if (uiPlainLen == sizeof(msg) && 0 == memcmp(pbPlainData, msg, sizeof(msg)))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*
*@功能：软库SM2签名验签检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM2SignCheck()
{
	/*软库SM2检测*/
	//检测软库SM2签名验签算法
	int iRet = 0;
	sm2_keypair testKey;
	SM2_initKeyPair(&testKey);
	//SM2 公钥X、Y，私钥D
	unsigned char pbEccPub_X[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x09,0xf9,0xdf,0x31 ,0x1e,0x54,0x21,0xa1, 0x50,0xdd,0x7d,0x16 ,0x1e,0x4b,0xc5,0xc6 ,
		0x72,0x17,0x9f,0xad ,0x18,0x33,0xfc,0x07 ,	0x6b,0xb0,0x8f,0xf3 ,0x56,0xf3,0x50,0x20 };
	unsigned char pbEccPub_Y[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0xcc,0xea,0x49,0x0c ,0xe2,0x67,0x75,0xa5,  0x2d,0xc6,0xea,0x71 ,0x8c,0xc1,0xaa,0x60 ,
		0x0a,0xed,0x05,0xfb ,0xf3,0x5e,0x08,0x4a ,0x66,0x32,0xf6,0x07 ,0x2d,0xa9,0xad,0x13 };
	unsigned char pbEccPriv_D[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x39,0x45,0x20,0x8f,0x7b,0x21,0x44,0xb1,0x3f,0x36,0xe3,0x8a,0xc6,0xd3,0x9f,0x95,
		0x88,0x93,0x93,0x69,0x28,0x60,0xb5,0x1a,0x42,0xfb,0x81,0xef,0x4d,0xf7,0xc5,0xb8 };
	//签名原文
	const char *msg = "message digest";
	//ID
	unsigned char pbID[16] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };

	/*unsigned char eccSign_R[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0xf5,0xa0,0x3b,0x06,  0x48,0xd2,0xc4,0x63,    0x0e,0xea,0xc5,0x13,   0xe1,0xbb,0x81,0xa1,
		0x59,0x44,0xda,0x38,  0x27,0xd5,0xb7,0x41,    0x43,0xac,0x7e,0xac,   0xee,0xe7,0x20,0xb3};
	unsigned char eccSign_S[ECCref_MAX_LEN] = {
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0xb1,0xb6,0xaa,0x29,  0xdf,0x21,0x2f,0xd8,   0x76,0x31,0x82,0xbc,  0x0d,0x42,0x1c,0xa1,
		0xbb,0x90,0x38,0xfd,  0x1f,0x7f,0x42,0xd4,   0x84,0x0b,0x69,0xc4,  0x85,0xbb,0xc1,0xaa};*/
		//签名值
	unsigned char eccSign[ECCref_MAX_LEN] = {
		0xf5,0xa0,0x3b,0x06,  0x48,0xd2,0xc4,0x63,    0x0e,0xea,0xc5,0x13,   0xe1,0xbb,0x81,0xa1,
		0x59,0x44,0xda,0x38,  0x27,0xd5,0xb7,0x41,    0x43,0xac,0x7e,0xac,   0xee,0xe7,0x20,0xb3,
		0xb1,0xb6,0xaa,0x29,  0xdf,0x21,0x2f,0xd8,   0x76,0x31,0x82,0xbc,  0x0d,0x42,0x1c,0xa1,
		0xbb,0x90,0x38,0xfd,  0x1f,0x7f,0x42,0xd4,   0x84,0x0b,0x69,0xc4,  0x85,0xbb,0xc1,0xaa };
	unsigned char pbECCSign[ECCref_MAX_LEN] = { 0 };
	unsigned int pbECCSignLen = sizeof(pbECCSign);
	//初始化SM2密钥对
	SM2_genKeyPair(&testKey);

	mpi_read_binary(&testKey.Q.X, pbEccPub_X + 32, 32);
	mpi_read_binary(&testKey.Q.Y, pbEccPub_Y + 32, 32);

	iRet = SM2_verify_ex(pbID, sizeof(pbID), (const unsigned char *)msg, strlen(msg), eccSign, sizeof(eccSign), &testKey);
	if (1 != iRet)
	{
		printf("SM2 SM2_verify_ex Verify failed...\n");
		return -1;
	}
	mpi_read_binary(&testKey.d, pbEccPriv_D + 32, 32);
	iRet = SM2_sign_ex(pbID, sizeof(pbID), (const unsigned char *)msg, strlen(msg), pbECCSign, &pbECCSignLen, &testKey);
	if (1 != iRet)
	{
		printf("SM2 SM2_sign_ex failed...\n");
		return -1;
	}
	iRet = SM2_verify_ex(pbID, sizeof(pbID), (const unsigned char *)msg, strlen(msg), pbECCSign, pbECCSignLen, &testKey);
	if (1 != iRet)
	{
		printf("SM2 SM2_verify_ex failed...\n");
		return -1;
	}


	return 0;
}


/*
*@功能：软库SM3检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM3Check()
{
	//待哈希数据：
	unsigned char bHashData[64] = { 0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64 };
	//哈希值：
	unsigned char bHashStdResult[32] = { 0xde,0xbe,0x9f,0xf9,0x22,0x75,0xb8,0xa1,0x38,0x60,0x48,0x89,0xc1,0x8e,0x5a,0x4d,
		0x6f,0xdb,0x70,0xe5,0x38,0x7e,0x57,0x65,0x29,0x3d,0xcb,0xa3,0x9c,0x0c,0x57,0x32 };
	unsigned char pbHashRet[32] = { 0 };
	int iRet = 0;
	SM3_CTX softSM3;
	memset(&softSM3, 0, sizeof(softSM3));
	SM3_HASH_INIT(&softSM3);

	SM3_HASH_UPDATE(&softSM3, bHashData, sizeof(bHashData));

	SM3_HASH_FINAL(pbHashRet, &softSM3);
	if (0 != memcmp(bHashStdResult, pbHashRet, sizeof(bHashStdResult)))
	{
		printf("SM3 hash failed...\n");
		return -1;
	}

	return 0;
}

/*
*@功能：软库SM4检测
*@参数：void
*@返回：int, 0 : SUCCESS; ~0 : FAILED
*/
int SoftSM4Check()
{
	//SGD_SMS4_ECB：
	//密钥：
	unsigned char pbKeyValue[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	//明文：
	unsigned char pbPlainText[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	//密文：
	unsigned char pbCipherText[16] = { 0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46 };

	//SGD_SMS4_CBC：
	//密钥：
	unsigned char pbCBCKeyValue[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	//初始化向量：
	unsigned char pbCBCIV[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 };
	//明文：
	unsigned char pbCBCPlainText[32] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0x29,0xbe,0xe1,0xd6,0x52,0x49,0xf1,0xe9,0xb3,0xdb,0x87,0x3e,0x24,0x0d,0x06,0x47 };
	//密文：
	unsigned char pbCBCCipherText[32] = { 0x3f,0x1e,0x73,0xc3,0xdf,0xd5,0xa1,0x32,0x88,0x2f,0xe6,0x9d,0x99,0x6c,0xde,0x93,0x54,0x99,0x09,0x5d,0xde,0x68,0x99,0x5b,0x4d,0x70,0xf2,0x30,0x9f,0x2e,0xf1,0xb7 };

	unsigned char szRet[128] = { 0 };
	unsigned int szRetLen = sizeof(szRet);
	unsigned long rk[32] = { 0 };
	//设置SM4加密密钥
	sm4_set_key(rk, pbKeyValue, 1);

	sm4_ecb_encrypt(pbPlainText, szRet, rk, SM4_ENCRYPT);
	if (0 != memcmp(pbCipherText, szRet, sizeof(pbCipherText)))
	{
		printf("SM4 encrypt failed...\n");
		return -1;
	}

	memset(rk, 0, sizeof(rk));
	memset(szRet, 0, sizeof(szRet));
	//设置SM4解密密钥
	sm4_set_key(rk, pbKeyValue, 0);

	sm4_ecb_encrypt(pbCipherText, szRet, rk, SM4_DECRYPT);
	if (0 != memcmp(pbPlainText, szRet, sizeof(pbCipherText)))
	{
		printf("SM4 decrypt failed...\n");
		return -1;
	}

	return 0;
}

///*
//*@功能：软库验证SM2签名
//*@参数：unsigned char *pSignMsg[in] : 证书内容
//*@参数：unsigned long ulSignMsgLen[in] : 证书长度
//*@参数：unsigned char *pSignature[in] : 签名值
//*@参数：unsigned long ulSignLen[in] : 签名值长度
//*@返回：int, 0 : SUCCESS; ~0 : FAILED
//*/
//int VerifySign(unsigned char *pSignMsg, unsigned long ulSignMsgLen,
//			   unsigned char *pSignature, unsigned long ulSignLen)
//{
//	
//	ULONG ulRetLen = 1024;
//	unsigned char szCert[4096] = {0}, szRet[1024] = {0}, szPubX[32] = {0}, szPubY[32] = {0};
//
//	unsigned char pbID[16] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
//
//	int iRet = 0;
//	/*x509_crt cert;
//	x509_crt_init(&cert);
//	iRet = x509_crt_parse_der(&cert, szSignMsg, ulSignMsgLen);
//	if (iRet != 0)
//	{
//		printf("x509_crt_parse_der failed, 0x%0x\n", iRet);
//		return -1;
//	}*/
//	const unsigned char * tmp = pSignMsg;
//	X509 * pcert = NULL;
//	printf("len = %d\n", ulSignMsgLen);
//	pcert = d2i_X509(NULL, &tmp, ulSignMsgLen);
//	//判断公钥是否存在
//	if (NULL == pcert)
//	{
//		printf("[ %s ]:[ %d ]证书无效...\n", __FILE__, __LINE__);
//		return -1;
//	}
//	if (NULL == pcert->cert_info->key)
//	{
//		printf("[ %s ]:[ %d ]证书中无公钥...\n", __FILE__, __LINE__);
//		return -1;
//	}
//	if (NULL == pcert->cert_info->key->public_key)
//	{
//		printf("[ %s ]:[ %d ]证书中无公钥...\n", __FILE__, __LINE__);
//		return -1;
//	}
//	if (NULL == pcert->cert_info->key->public_key->data)
//	{
//		printf("[ %s ]:[ %d ]证书中无公钥...\n", __FILE__, __LINE__);
//		return -1;
//	}
//	//printf("[ %s ]:[ %d ]证书中有公钥...\n", __FILE__, __LINE__);
//
//	//读取公钥类型
//	iRet = OBJ_obj2txt((char *)szRet, sizeof(szRet), pcert->cert_info->key->algor->algorithm, 1);
//	if (iRet < 1)
//	{
//		printf("不能判断证书类型\n");
//		return -1;
//	}
//	const char *pOID = "1.2.840.10045.2.1";
//	if (0 != strcmp((const char *)szRet, pOID))
//	{
//		printf("该X509证书公钥非SM2公钥\n");
//		return -1;
//	}
//	iRet = pcert->cert_info->key->public_key->length;
//	unsigned char *pKey = pcert->cert_info->key->public_key->data;
//	if (iRet == 65)
//	{
//		memcpy(szPubX, pKey + 1, 32);
//		memcpy(szPubY, pKey + 33, 32);
//	}
//	else
//	{
//		printf("该X509证书公钥非SM2公钥\n");
//		return -1;
//	}
//	_PRINT_Message_Bin1(szPubX, sizeof(szPubX));
//	_PRINT_Message_Bin1(szPubY, sizeof(szPubY));
//
//	//初始化SM2密钥对
//	sm2_keypair verifyKey;
//	SM2_initKeyPair(&verifyKey);
//	SM2_genKeyPair(&verifyKey);
//	//导入SM2公钥
//	mpi_read_binary(&verifyKey.Q.X, szPubX, 32);
//	mpi_read_binary(&verifyKey.Q.Y, szPubY, 32);
//
//	iRet = SM2_verify_ex(pbID, sizeof(pbID), pSignMsg, ulSignMsgLen, pSignature, ulSignLen, &verifyKey);
//	if (1 != iRet)
//	{
//		printf("SM2_verify_ex failed.\n");
//		return -1;
//	}
//	
//	return 0;
//}
//
//
//JNIEXPORT jint JNICALL Java_com_cist_SoftAlgNative_VerifySM2Sign
//(JNIEnv *env, jobject, jbyteArray byteCert, jbyteArray byteSignature)
//{
//	jbyte * jbyteCert = NULL, *jbyteSign = NULL;
//	int iCertLen = 0, iSignLen = 0, iRet = 1;
//	jbyteCert = env->GetByteArrayElements(byteCert, 0);
//	iCertLen = env->GetArrayLength(byteCert);
//	if (jbyteCert == NULL || iCertLen == 0)
//	{
//		printf("Input cert is empyty...\n");
//		goto END;
//	}
//	jbyteSign = env->GetByteArrayElements(byteSignature, 0);
//	iSignLen = env->GetArrayLength(byteSignature);
//	if (NULL == jbyteSign || 0 == iSignLen)
//	{
//		printf("Input sign is empyty...\n");
//		goto END;
//	}
//	iRet = VerifySign((unsigned char *)jbyteCert, iCertLen,
//				(unsigned char *)jbyteSign, iSignLen);
//	if (0 != iRet)
//	{
//		printf("Verify SM2 Sign Failed...\n");
//	}
//
//END:
//
//	return iRet;
//}