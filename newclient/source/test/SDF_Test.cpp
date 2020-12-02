#include "SDF_Test.hpp"
#include <iostream>

#include <string.h>
#include "../common/debug.h"

using namespace std;

#define MAXLENTH (10240)

static void prvKeyTochar(const ECCrefPrivateKey prv, unsigned char *data)
{
	memcpy(data, &(prv.D[32]), 32);
}
static void charToprvKey(const unsigned char *data, ECCrefPrivateKey *prv)
{
	prv->bits = 256;
	memcpy(&(prv->D[32]), data, 32);
}
static void pucKeyTochar(const ECCrefPublicKey puc, unsigned char *data)
{
	memcpy(data, &puc.x[32], 32);
	memcpy(data + 32, &puc.y[32], 32);
}
static void charTopucKey(const unsigned char *data, ECCrefPublicKey *puc)
{
	puc->bits = 256;
	memcpy(&(puc->x[32]), data, 32);
	memcpy(&(puc->y[32]), data + 32, 32);
}
static void signatureTochar(const ECCSignature sign, unsigned char *data)
{
	memcpy(data, &(sign.r[32]), 32);
	memcpy(data + 32, &(sign.s[32]), 32);
}
static void charTosignature(const unsigned char *data, ECCSignature *sign)
{
	memcpy(&(sign->r[32]), data, 32);
	memcpy(&(sign->s[32]), data + 32, 32);
}
static void ecccipherTochar(const ECCCipher enc, unsigned char *data)
{
	memcpy(data, &(enc.x[32]), 32);
	memcpy(data + 32, &(enc.y[32]), 32);
	memcpy(data + 64, &(enc.M), 32);
	memcpy(data + 64 + 32, &(enc.L), 4);
	memcpy(data + 64 + 32 + 4, enc.C, enc.L);
}
static void charToecccipher(const unsigned char *data, ECCCipher *enc)
{
	memcpy(&(enc->x[32]), data, 32);
	memcpy(&(enc->y[32]), data + 32, 32);
	memcpy(&(enc->M), data + 64, 32);
	memcpy(&(enc->L), data + 64 + 32, 4);
	memcpy(enc->C, data + 64 + 32 + 4, enc->L);
}


SDFtest::SDFtest(void * phDeviceHandle, void * phSessionHandle)
{
	this->m_phDeviceHandle = phDeviceHandle;
	this->m_phSessionHandle = phSessionHandle;
}

int SDFtest::hashTest()
{
	unsigned char data[8192] = { 0 };
	unsigned char digest[32] = { 0 };
	unsigned int outlenth = 32;
	unsigned char inbuf[4096] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};

	for (int i = 0; i < 8192; i++)
	{
		data[i] = i % 255;
	}

	int rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, NULL, NULL, 0);
	if (rv != SDR_OK)
	{
		while (1);
	}
	rv = SDF_HashUpdate(m_phSessionHandle, data, 8192);
	if (rv != SDR_OK)
	{
		while (1);
	}
	rv = SDF_HashFinal(m_phSessionHandle, digest, &outlenth);
	if (rv != SDR_OK)
	{
		while (1);
	}
	cout << endl;
	cout << "[" << __LINE__ << "]" << "hash test without pubkey" << endl;
	for (int i = 0; i < 32; i++)
	{
		printf("0x%02x  ", digest[i]);
	}
	cout << endl;
	//if (digest[0] != 0xda)
	//{
	//	cout << "[" << __LINE__ << "]" << "hash test without pubkey error!" << endl;
	//}
	// 结果：0xda 0x1d 0xae-------------
	return rv;
}

int SDFtest::hashWithPubTest()
{
	unsigned char internal_user_pk[64] = { 0xe8,0x7a,0xaf,0x73,0x8e,0x6a,0x4d,0x5f,
							   0x0b,0x77,0xda,0x3c,0xf8,0x5f,0xe0,0xf7,
							   0xb2,0x09,0x08,0x2f,0xc5,0xb9,0x1c,0x7d,
							   0xd4,0x6f,0x81,0xe0,0xe1,0x7c,0x0f,0xb9,
							   0xec,0xc5,0xdf,0xfc,0x8c,0x44,0x57,0x80,
							   0xa9,0x44,0x9f,0x8f,0xdd,0xc6,0xca,0xdd,
							   0x23,0xc3,0xfe,0x6b,0x1d,0x3f,0xd9,0x9c,
							   0x7a,0xd2,0xec,0xcd,0x65,0x61,0x0c,0x18 };
	unsigned char internal_user_pri[32] = { 0xd5,0x78,0x18,0xec,0xd4,0x0c,0xfc,0x9e,
								0x74,0x98,0x70,0x1e,0x91,0x67,0x85,0x54,
								0x28,0x5d,0xfe,0xff,0xe7,0x5b,0x84,0x82,
								0x04,0x4e,0x99,0x0f,0x10,0x36,0x56,0x6b };



	int rv = 0;
	unsigned char inputdata[5943];
	// rv = SDF_ExportSignPublicKey_ECC(m_phSessionHandle, 1, &m_eccpubkey);
	// if (rv != SDR_OK)
	// {
	// 	cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
	// 	while (1);
	// }

	charTopucKey(internal_user_pk, &m_eccpubkey);
	unsigned char pucSignId[16];     //
	for (int i = 0; i < 16; i++)
		pucSignId[i] = 0x31 + i % 8;
	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, &m_eccpubkey, pucSignId, 16);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	for (int i = 0; i < 10; i++)
		inputdata[i] = i % 255;
	rv = SDF_HashUpdate(m_phSessionHandle, inputdata, 10);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	unsigned int outlenth = 0;
	rv = SDF_HashFinal(m_phSessionHandle, m_outputdata, &outlenth);
	//0xc1,0x4c,0xb3
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "Hamc test" << endl;
	for (int i = 0; i < 32; i++)
	{
		printf("0x%02x  ", m_outputdata[i]);
	}
	cout << endl;
	return rv;

}
int SDFtest::hmacTest()
{
	unsigned char symkey[16] = "Passw0rd";
	int rv = 0;
	m_inputdata[0] = 'a';
	m_inputdata[1] = 'b';
	m_inputdata[2] = 'c';
	rv = SDF_ImportKey(m_phSessionHandle, symkey, 16, &m_phKeyHandle);
	// m_phKeyHandle = 0x00007ff60285a6c0 
	// *m_phKeyHandle = 0x01
	// m_phSessionHandle = 0x00007ff6028586c0
	// *m_phSessionHandle = 0x10080002  -------实质是2
	rv = SDF_MacInit(m_phSessionHandle, m_phKeyHandle, SGD_SM3);
	rv = SDF_MacUpdate(m_phSessionHandle, m_inputdata, 3);
	unsigned int outlenth = 0;
	rv = SDF_MacFinal(m_phSessionHandle, m_outputdata, &outlenth);  //0xdb
	rv = SDF_DestroyKey(m_phSessionHandle, m_phKeyHandle);
	return rv;
}


int SDFtest::kekTest()
{
	//1、产生一个会话密钥，并用内部对称密钥加密输出，同事产生一个句柄1
	//2、导入会话密钥，并用KEK解密，同事返回会话密钥的句柄2
	//3、使用句柄1对应的会话密钥加密一个明文，得到密文
	//4、使用句柄2对应的会话密钥解密3得到的密文
	//5、比较加解密结果
	//6、销毁句柄2
	//7、销毁句柄1
	unsigned int outlenth = 32;
	void * phKeyHandle2;

	int rv = SDF_GenerateKeyWithKEK(m_phSessionHandle, 128, SGD_SM4_ECB, 1, m_outputdata, &outlenth, &m_phKeyHandle);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}

	rv = SDF_ImportKeyWithKEK(m_phSessionHandle, SGD_SM4_ECB, 1, m_outputdata, outlenth, &phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	unsigned char plain[16];
	unsigned char iv[16];
	for (int i = 0; i < 16; i++)
	{
		plain[i] = i;
		iv[i] = i;
	}
	unsigned int plainlenth = 16;
	unsigned char tmpout[64] = { 0 };
	unsigned int tmplenth = 0;
	rv = SDF_Encrypt(m_phSessionHandle, m_phKeyHandle, SGD_SM4_ECB, iv, plain, plainlenth, tmpout, &tmplenth);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	rv = SDF_Decrypt(m_phSessionHandle, phKeyHandle2, SGD_SM4_ECB, iv, tmpout, tmplenth, m_outputdata, &outlenth);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	//比较结果是否一致
	//销毁密钥
	rv = SDF_DestroyKey(m_phSessionHandle, m_phKeyHandle);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	rv = SDF_DestroyKey(m_phSessionHandle, phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	return rv;
}


int SDFtest::SocketConnectTest()
{
	return 0;
}
int SDFtest::calculateMacTest()
{
	unsigned char pucSessionKey[16];
	unsigned char iv[16] = { 0 };
	for (int i = 0; i < 16; i++)
		pucSessionKey[i] = 0x31 + i % 8;
	this->m_phKeyHandle = NULL;
	int rv = SDF_ImportKey(m_phSessionHandle, pucSessionKey, 16, &m_phKeyHandle);
	unsigned int outlenth = 32;
	for (int i = 0; i < 1024; i++)
		m_inputdata[i] = i;
	//注意，输入数据必须是16的倍数--------------待查原因
	rv = SDF_CalculateMAC(m_phSessionHandle, m_phKeyHandle, SGD_SM4_MAC, iv, m_inputdata, 1024, m_outputdata, &outlenth);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "SDF_CalculateMac   ErrorCode:" << rv << endl;
		while (1);
	}
	rv = SDF_DestroyKey(m_phSessionHandle, m_phKeyHandle);
	if (rv != 0)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}

	return rv;
}

int SDFtest::randTest()
{
	unsigned char outdata[8192];
	int rv = SDF_GenerateRandom(m_phSessionHandle, 100, outdata);
	if (rv != 0)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_GenerateRandom success" << endl;
	return rv;
}


int SDFtest::sm1sm4Test()
{

	//SM4 ECB/CBC 10K 大数据测试通过
	void * tmp_phKeyHandle = nullptr;
	unsigned char symkey[16];
	int ulAlgId = SGD_SM4_CBC;
	int rv = 0;
	cout << "**************SM4 ECB test start *********************" << endl;
	cout << "The Key is :" << endl;
	for (int i = 0; i < 16; i++)
	{
		symkey[i] = i;
		printf("0x%02X,", i);
	}
	cout << endl;
	rv = SDF_ImportKey(m_phSessionHandle, symkey, 16, &tmp_phKeyHandle);
	if (rv != SDR_OK)
	{
		while (1);
	}

	unsigned char pucIV[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 };
	unsigned char pucData[MAXLENTH] = {0};
	for (int i = 0; i < MAXLENTH; i++)
	{
		pucData[i] = i % 256;
	}
	int uiDataLength = MAXLENTH;
	unsigned char  pucEncData[MAXLENTH] = { 0 };
	unsigned int puiEncDataLength = MAXLENTH;
	rv = SDF_Encrypt(m_phSessionHandle, tmp_phKeyHandle, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
		&puiEncDataLength);

	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char plain[MAXLENTH] = { 0 };
	unsigned int plainLength = MAXLENTH;
	rv = SDF_Decrypt(m_phSessionHandle, tmp_phKeyHandle, ulAlgId, pucIV, pucEncData, puiEncDataLength,
		plain, &plainLength);
	//if (memcmp(pucData, plain, plainLength))
	//{
	//	cout << "[" << __LINE__ << "]" << "symEncDecTest SM4 ECB mode test error" << endl;
	//}

	cout << "**************SM4 ECB test success*********************" << endl << endl;

	/**************************************** SM1 测试 *******************************************************/
	cout << "SM1CBC test" << endl;
	ulAlgId = SGD_SM1_ECB;
	uiDataLength = MAXLENTH;
	memset(pucEncData, 0, MAXLENTH);
	rv = SDF_Encrypt(m_phSessionHandle, tmp_phKeyHandle, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
		&puiEncDataLength);

	cout << "the encdata is " << endl;
	for (int i = 0; i < 32; i++)
	{
		printf("0x%02X,", pucEncData[i]);
	}
	cout << endl;


	ulAlgId = SGD_SM1_CBC;
	uiDataLength = MAXLENTH;
	memset(pucEncData, 0, MAXLENTH);
	rv = SDF_Encrypt(m_phSessionHandle, tmp_phKeyHandle, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
		&puiEncDataLength);

	cout << "the ECBdata is " << endl;
	for (int i = 0; i < 32; i++)
	{
		printf("0x%02X,", pucEncData[i]);
	}
	cout << endl;



	rv = SDF_DestroyKey(m_phSessionHandle, tmp_phKeyHandle);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "SDF_DestroyKey error" << endl;
		while (1);
	}
	return rv;
}



/**********************************************
测试过程描述：
	1、获取内部私钥使用权限
	2、导出内部1号公钥
	3、关闭内部私钥使用权限
	4、使用导出的内部1号公钥加密一组数据得到一个密文
	5、获取内部1号私钥使用权限
	6、使用内部1号私钥解密 密文
	7、得到明文-----------比较
	8、关闭内部1号私钥使用权限
	9、测试完成
*/
int SDFtest::internalEccTest()
{
	static int rv = 0;
	// 使用内部公钥加密生成的会话密钥
	rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, 1, (unsigned char*)"12345678", 8);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_GetPrivateKeyAccessRight return " << rv << endl;

	rv = SDF_ExportEncPublicKey_ECC(m_phSessionHandle, 1, &m_eccpubkey);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, 1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_ReleasePrivateKeyAccessRight return " << rv << endl;

	for (int i = 0; i < 32; i++)
		m_inputdata[i] = 0x30 + i;
	
	rv = SDF_ExternalEncrypt_ECC(m_phSessionHandle, SGD_SM2_3, &m_eccpubkey, m_inputdata, 32, &m_Cipher);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "SDF_ExternalEncrypt  ErrorCode:" << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_ExternalEncrypt_ECC return " << rv << endl;


	// 使用内部私钥解密会话密钥  ------------测试出现问题
	rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, 1, (unsigned char*)"12345678", 8);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_GetPrivateKeyAccessRight return " << rv << endl;

	unsigned int lenth = 0;
	//  没有内部解密接口
	//	rv = SDF_InternalDecrypt_ECC(m_phSessionHandle, SGD_SM2_3, 1, &m_Cipher, m_outputdata, &lenth);
	//	if (rv != SDR_OK)
	//	{
	//		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
	//		while (1);
	//	}
	//	cout << "[" << __LINE__ << "]" << "SDF_InternalDecrypt_ECC return " << rv << endl;

	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, 1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "ErrorCode:" << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_ReleasePrivateKeyAccessRight return " << rv << endl;

	return rv;
}


int SDFtest::aggrementEccTest()
{
	ECCrefPublicKey A_SponsorpubKey, A_SponsorTmppubKey;
	unsigned char A_SponsorID[17] = "1111111111111111";     //发起者ID

	ECCrefPublicKey B_ResponsepubKey, B_ResponseTmppubKey;
	unsigned char B_ResponseID[17] = "2222222222222222";

	void * AgreementHandle = NULL;
	void * phKeyHandle1 = NULL;
	void * phKeyHandle2 = NULL;
	int uiISKIndex = 1;
	int uiKeyBits = 16 * 8;

	int rv = 0;
	rv = SDF_GenerateAgreementDataWithECC(m_phSessionHandle, uiISKIndex, uiKeyBits, A_SponsorID, 16, \
		&A_SponsorpubKey, &A_SponsorTmppubKey, &AgreementHandle);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}

	// B ------------------> 响应方
	// B 使用A的公钥，临时公钥，及其他的一些参数，协商得到 一个句柄，指向协商得到的会话密钥，同时输出A需要的公钥，临时公钥
	rv = SDF_GenerateAgreementDataAndKeyWithECC(m_phSessionHandle, uiISKIndex, uiKeyBits, B_ResponseID, 16, \
		A_SponsorID, 16, &A_SponsorpubKey, &A_SponsorTmppubKey,
		&B_ResponsepubKey, &B_ResponseTmppubKey, &phKeyHandle1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	//	printf("@@@@@@@@@@@@@aggrementEccTest--->AgreementHandle:0x%08x\r\n", AgreementHandle);

	// A 运算得到会话句柄--------------------报错  20200702
	rv = SDF_GenerateKeyWithECC(m_phSessionHandle, B_ResponseID, 16, &B_ResponsepubKey, \
		&B_ResponseTmppubKey, AgreementHandle, &phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char inputdata[16], pucIV[16];
	for (int i = 0; i < 16; i++)
	{
		inputdata[i] = i;
		pucIV[i] = i;
	}
	unsigned char outputdata1[16] = { 0 };
	unsigned char outputdata2[16] = { 0 };
	unsigned int outputlenth1 = 0, outputlenth2 = 0;

	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle1, SGD_SM4_ECB, pucIV, inputdata, 16, outputdata1, &outputlenth1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	for (int i = 0; i < 16; i++)
	{
		inputdata[i] = i;
		pucIV[i] = i;
	}

	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle2, SGD_SM4_ECB, pucIV, inputdata, 16, outputdata2, &outputlenth2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	//比较两个结果是否一致，如果不一致，报错
	if (memcmp(outputdata1, outputdata2, outputlenth1))
	{
		cout << "[" << __LINE__ << "]" << "aggrementEccTest() error!" << endl;
	}
	rv = SDF_DestroyKey(m_phSessionHandle, phKeyHandle1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_DestroyKey(m_phSessionHandle, phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}

	return rv;
}


int SDFtest::externEccPubKeyTest()
{
	int uiKeyId = 1;
	int rv = SDF_ExportEncPublicKey_ECC(m_phSessionHandle, uiKeyId, &m_eccpubkey);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	int uiKeyBits = 32 * 8;
	int ulAlgId = SGD_SM2_3;

	void * pKeyHandle1;
	rv = SDF_GenerateKeyWithEPK_ECC(m_phSessionHandle, uiKeyBits, ulAlgId, &m_eccpubkey, &m_Cipher, &pKeyHandle1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "The SDF_GenerateKeyWithEPK_ECC result:" << rv << endl;
	void * pKeyHandle2;
	rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, uiKeyId, (unsigned char*)"12345678", 8);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}
	rv = SDF_ImportKeyWithISK_ECC(m_phSessionHandle, uiKeyId, &m_Cipher, &pKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;       //此处出错     
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "The SDF_ImportKeyWithISK_ECC result:" << rv << endl;
	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, uiKeyId);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << rv << endl;
		while (1);
	}


	rv = SDF_DestroyKey(m_phSessionHandle, pKeyHandle1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "SDF_DestroyKey ErrorCode: rv = " << rv << endl;
		while (1);
	}
	rv = SDF_DestroyKey(m_phSessionHandle, pKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << "SDF_DestroyKey ErrorCode: rv = " << rv << endl;
		while (1);
	}
	return rv;

}

int SDFtest::externalSignTest()
{

	int rv;
	unsigned char pucData[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	unsigned char ID[16] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
	unsigned char pubKey[64] = {
		0x62, 0xB3, 0xAA, 0xF8, 0xBE, 0x65, 0xC2, 0x6A, 0xC4, 0x15, 0xE0, 0xA3, 0x5F, 0xA7, 0xB2, 0xA9,
		0x40, 0x2D, 0xCB, 0x42, 0xBE, 0x9C, 0x55, 0x0D, 0x93, 0xC8, 0x17, 0xE2, 0x77, 0x2A, 0x2A, 0x8B,
		0x2A, 0xEF, 0x29, 0x62, 0xF1, 0x4A, 0x7B, 0x55, 0x89, 0xC6, 0x91, 0x3A, 0x73, 0xD8, 0x8F, 0x87,
		0x9F, 0xA2, 0x1C, 0xA3, 0x4D, 0x2F, 0xFF, 0xB3, 0x11, 0xE4, 0x89, 0x1D, 0x21, 0xD1, 0x3B, 0x26
	};
	unsigned char sign_value[64] = {
		0x47, 0xC0, 0x6D, 0xE0, 0x1C, 0xF7, 0x1C, 0x59, 0x6B, 0xA0, 0x55, 0x19, 0x00, 0x65, 0x27, 0xDD,
		0x78, 0xB9, 0x80, 0x6C, 0xEB, 0x1C, 0xFC, 0x3B, 0xE6, 0xEE, 0x51, 0x62, 0x3F, 0x21, 0x0C, 0x9E,
		0xCD, 0x5A, 0xF1, 0xBC, 0x9B, 0x03, 0xCF, 0xA0, 0x96, 0x2E, 0x25, 0x2C, 0xFA, 0x33, 0x2D, 0x8A,
		0xC0, 0x60, 0x6E, 0x23, 0xBE, 0x70, 0x18, 0xE7, 0xEF, 0xAD, 0xFF, 0xE0, 0xD1, 0xC2, 0x21, 0xE5
	};


	ECCrefPublicKey tmppubkey;
	ECCSignature signdata;

	memset(&tmppubkey, 0, sizeof(ECCrefPublicKey));
	memset(&signdata, 0, sizeof(ECCSignature));

	charTopucKey(pubKey, &tmppubkey);
	charTosignature(sign_value, &signdata);

	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, &tmppubkey, ID, 16);
	if (rv != SDR_OK) {
		while (1);
	}
	rv = SDF_HashUpdate(m_phSessionHandle, pucData, 6);
	if (rv != SDR_OK) {
		while (1);
	}
	unsigned char digest[32] = { 0 };
	unsigned int outlenth = 32;
	rv = SDF_HashFinal(m_phSessionHandle, digest, &outlenth);
	if (rv != SDR_OK) {
		while (1);
	}
	cout << endl;

	int rrr = SDF_ExternalVerify_ECC(m_phSessionHandle, SGD_SM2_1, &tmppubkey, digest, 32, &signdata);
	if (rrr != SDR_OK) {
		printf("SDF_ExternalVerify_ECC test error,errorcode:0x%08x\n", rrr);
	}
	else {
		printf("SDF_ExternalVerify_ECC success\r\n");
	}

	
	return 0;
}











//使用内部私钥签名，导入公钥，使用公钥验签
int SDFtest::pubkeyVerify()
{
	int uiISKIndex = 1;
	unsigned char  pucData[16] = "abc";
	int uiDataLength = 3;
	ECCSignature pucSignature;
	int rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, uiISKIndex, (unsigned char*)"12345678", 8);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, NULL, NULL, 0);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_HashUpdate(m_phSessionHandle, pucData, uiDataLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char pucHash[32] = { 0 };
	unsigned int hashLenth = 0;
	rv = SDF_HashFinal(m_phSessionHandle, pucHash, &hashLenth);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_InternalSign_ECC(m_phSessionHandle, uiISKIndex, pucHash, hashLenth, &pucSignature);

	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, uiISKIndex);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	ECCrefPublicKey pucPublicKey;
	rv = SDF_ExportSignPublicKey_ECC(m_phSessionHandle, uiISKIndex, &pucPublicKey);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	int ulAlgId = SGD_SM2_1;
	//测试失败 王占备 20191220
	rv = SDF_ExternalVerify_ECC(m_phSessionHandle, ulAlgId, &pucPublicKey, pucHash, hashLenth, &pucSignature);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_ExternalVerify_ECC result is " << rv << endl;
	return rv;
}


/*
 流程如下：
	1、生成ECC密钥对
	2、计算hash值
	3、使用ECC私钥签名hash值
	4、使用ECC公钥验签，判断是否正确
*/
int SDFtest::externalEccSignVerifyTest()
{
	int ulAlgId = SGD_SM2;
	int ulAlgSignId = SGD_SM2_1;
	int uiKeyBits = 32 * 8;
	ECCrefPublicKey pucPublicKey;
	ECCrefPrivateKey pucPrivateKey;
	int rv = SDF_GenerateKeyPair_ECC(m_phSessionHandle, ulAlgId, uiKeyBits, &pucPublicKey, &pucPrivateKey);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char pucData[16] = { 0 };
	int uiDataLength = 16;
	ECCSignature pucSignature;
	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, NULL, NULL, 0);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_HashUpdate(m_phSessionHandle, pucData, uiDataLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char pucHash[32] = { 0 };
	unsigned int hashLenth;
	rv = SDF_HashFinal(m_phSessionHandle, pucHash, &hashLenth);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	//使用私钥签名   确认接口函数SDF_ExternalSign_ECC   此接口不支持
//	rv = SDF_ExternalSign_ECC(m_phSessionHandle, ulAlgSignId, &pucPrivateKey, pucHash, hashLenth,
//		&pucSignature);
//	if (rv != SDR_OK)
//	{
//		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
//		while (1);
//	}
//	cout << "[" << __LINE__ << "]" << "SDF_ExternalSign_ECC result is " << rv << endl;
	//使用公钥验签
	rv = SDF_ExternalVerify_ECC(m_phSessionHandle, ulAlgSignId, &pucPublicKey, pucHash, hashLenth,
		&pucSignature);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "SDF_ExternalVerify_ECC result is " << rv << endl;
	return rv;
}
// 使用内部的私钥进行签名验签运算
int SDFtest::internalEccSignVerifyTest()
{
	int uiISKIndex = 1;
	unsigned char pucData[16];
	int uiDataLength = 16;
	ECCSignature pucSignature;
	int rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, uiISKIndex, (unsigned char*)"12345678", 8);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	// rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, NULL, NULL, 0);
	// if (rv != SDR_OK)
	// {
	// 	cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
	// 	while (1);
	// }
	// rv = SDF_HashUpdate(m_phSessionHandle, pucData, uiDataLength);
	// if (rv != SDR_OK)
	// {
	// 	cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
	// 	while (1);
	// }
	// unsigned char pucHash[32] = { 0 };
	// unsigned int hashLenth;
	// rv = SDF_HashFinal(m_phSessionHandle, pucHash, &hashLenth);
	// if (rv != SDR_OK)
	// {
	// 	cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
	// 	while (1);
	// }

	memset(&pucSignature, 0, sizeof(ECCSignature));
	unsigned char digest[32] = { 0x1d,0x5b,0xb4,0x69,0x4d,0x55,0xaa,0x39,
				 0x8b,0xaf,0xed,0x8b,0x7d,0xc7,0x13,0x05,
				 0x79,0x1b,0x2e,0x83,0x13,0xb8,0x26,0x23,
				 0x2d,0xb7,0x57,0x0f,0x84,0x52,0x1d,0x84 };
	rv = SDF_InternalSign_ECC(m_phSessionHandle, uiISKIndex, digest, 32, &pucSignature);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "内部私钥签名的结果：" << rv << endl;
	rv = SDF_InternalVerify_ECC(m_phSessionHandle, uiISKIndex, digest, 32, &pucSignature);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	cout << "[" << __LINE__ << "]" << "使用内部公钥验签的结果是：" << rv << endl;
	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, uiISKIndex);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	return rv;
}

// #define  MAXLENTH  (2*4096)   //长度太长的话，会有错误 20191028


int SDFtest::symEncDecTest() {
	int uiKeyBits = 16 * 8;
	int ulAlgId = SGD_SM4_ECB;
	int uiKEKIndex = 1;
	unsigned char pucKey[32] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	unsigned int puiKeyLength = 0;
	void * phKeyHandle1;
	//生成一个会话密钥，并加密输出
	// 返回0x01000003 20191025
	int rv = SDF_GenerateKeyWithKEK(m_phSessionHandle, uiKeyBits, ulAlgId, uiKEKIndex, pucKey, &puiKeyLength,
		&phKeyHandle1);

	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	void * phKeyHandle2;
	//导入会话密钥，并用加密密钥解密
	rv = SDF_ImportKeyWithKEK(m_phSessionHandle, ulAlgId, uiKEKIndex, pucKey, puiKeyLength, &phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}

	unsigned char pucIV[16] = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6 };
	unsigned char pucData[MAXLENTH] = { 0 };
	for (int i = 0; i < MAXLENTH; i++)
		pucData[i] = i % 255;
	int uiDataLength = MAXLENTH;
	unsigned char  pucEncData[MAXLENTH] = { 0 };
	unsigned int puiEncDataLength = MAXLENTH;
	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle1, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
		&puiEncDataLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	unsigned char plain[MAXLENTH] = { 0 };
	unsigned int plainLength = MAXLENTH;
	unsigned char pucIV1[16] = { 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6 };
	rv = SDF_Decrypt(m_phSessionHandle, phKeyHandle2, ulAlgId, pucIV1, pucEncData, puiEncDataLength,
		plain, &plainLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	if (memcmp(pucData, plain, plainLength))
	{
		cout << "[" << __LINE__ << "]" << "symEncDecTest SM4 ECB mode test error" << endl;
	}
	ulAlgId = SGD_SM4_CBC;
	memset(pucEncData, 0, 16);
	memset(plain, 0, 16);
	uiDataLength = 32;
	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle1, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
		&puiEncDataLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_Decrypt(m_phSessionHandle, phKeyHandle2, ulAlgId, pucIV1, pucEncData, puiEncDataLength,
		plain, &plainLength);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	if (memcmp(pucData, plain, 16))
	{
		cout << "[" << __LINE__ << "]" << "symEncDecTest SM4 SGD_SM4_CBC mode test error" << endl;
	}

	//不支持CFB 算法调用
// 	ulAlgId = SGD_SM4_CFB;
// 	memset(pucEncData, 0, 16);
// 	memset(plain, 0, 16);
// 	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle1, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
// 		&puiEncDataLength);
// 	if (rv != SDR_OK)
// 	{
// 		cout << "[" << __LINE__ << "]" <<" ErrorCode: rv = " << hex << rv << endl;
// 		while (1);
// 	}
// 	rv = SDF_Decrypt(m_phSessionHandle, phKeyHandle2, ulAlgId, pucIV, pucEncData, puiEncDataLength,
// 		plain, &plainLength);
// 	if (rv != SDR_OK)
// 	{
// 		cout << "[" << __LINE__ << "]" <<" ErrorCode: rv = " << hex << rv << endl;
// 		while (1);
// 	}
// 	if (memcmp(pucData, plain, plainLength))
// 	{
// 		cout << "[" << __LINE__ << "]" <<"symEncDecTest SM4 SGD_SM4_CFB mode test error" << endl;
// 		while (1);
// 	}
	//不支持OFB算法调用
// 	ulAlgId = SGD_SM4_OFB;
// 	memset(pucEncData, 0, 16);
// 	memset(plain, 0, 16);
// 	rv = SDF_Encrypt(m_phSessionHandle, phKeyHandle1, ulAlgId, pucIV, pucData, uiDataLength, pucEncData,
// 		&puiEncDataLength);
// 	if (rv != SDR_OK)
// 	{
// 		cout << "[" << __LINE__ << "]" <<" ErrorCode: rv = " << hex << rv << endl;
// 		while (1);
// 	}
// 	rv = SDF_Decrypt(m_phSessionHandle, phKeyHandle2, ulAlgId, pucIV, pucEncData, puiEncDataLength,
// 		plain, &plainLength);
// 	if (rv != SDR_OK)
// 	{
// 		cout << "[" << __LINE__ << "]" <<" ErrorCode: rv = " << hex << rv << endl;
// 		while (1);
// 	}
// 	if (memcmp(pucData, plain, plainLength))
// 	{
// 		cout << "[" << __LINE__ << "]" <<"symEncDecTest SM4 SGD_SM4_OFB mode test error" << endl;
// 		while (1);
// 	}
	rv = SDF_DestroyKey(m_phSessionHandle, phKeyHandle1);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	rv = SDF_DestroyKey(m_phSessionHandle, phKeyHandle2);
	if (rv != SDR_OK)
	{
		cout << "[" << __LINE__ << "]" << " ErrorCode: rv = " << hex << rv << endl;
		while (1);
	}
	return rv;
}







int SDFtest::Demo_GenerateRSA()
{

	int rv = 0, rv2 = 0, loop = 1, i;
	//	unsigned long dwStart, dwEnd;
	//	int timeDel = 1;
	//	RSArefPublicKey     rsapuk;
	//	RSArefPublicKey     rsapukSign;
	//	RSArefPrivateKey    rsaprk;
	//	int bit = 2048;
	//	int keyIndx = 1;
	//	void *key[7];
	//	unsigned char pubKey[20480];
	//	unsigned int pubKeyLen;
	//	unsigned char pubKeyKEK[20480];
	//	unsigned int pubKeyLenKEK;
	//	CK_CHAR deIn[1024], deTmp[1024];
	//	CK_CHAR deOut[1024];
	//	unsigned int deLen = sizeof(deOut), deLenTmp;
	//
	//	memset(key, NULL, 5 * sizeof(key[0]));
	//
	//
	//	do
	//	{
	//#ifndef UNIX
	//		dwStart = timeGetTime();
	//#else
	//		dwStart = time(NULL);
	//#endif
	//		for (i = 0; i < loop; i++)
	//		{
	//			rv = SDF_GenerateKeyPair_RSA(m_phSessionHandle, 2048, &rsapuk, &rsaprk);
	//			if (rv != SDR_OK) {
	//				printf("SDF_GenerateKeyPair_RSA is error 0x%x\n", rv);
	//				break;
	//			}
	//		}
	//		if (i != loop)
	//			break;
	//#ifndef UNIX
	//		dwEnd = timeGetTime();
	//		timeDel = 1000;
	//#else
	//		dwEnd = time(NULL);
	//#endif
	//		printf("SDF_GenerateKeyPair_RSA: %d bit, %d time(s), %.2f tps.\n", bit, loop, 1.0*loop*timeDel / (dwEnd - dwStart));
	//
	//		memset(deIn, 'c', sizeof(deIn));
	//		deLenTmp = 1024;
	//		rv = SDF_ExternalPublicKeyOperation_RSA(m_phSessionHandle, &rsapuk, deIn, bit / 8, deOut, &deLen);
	//		rv = SDF_ExternalPrivateKeyOperation_RSA(m_phSessionHandle, &rsaprk, deOut, deLen, deTmp, &deLenTmp);
	//		if ((rv != SDR_OK) || 0 == deLenTmp || 0 != memcmp(deIn, deTmp, deLenTmp))
	//		{
	//			printf("SDF_ExternalPrivateKeyOperation_RSA result is error 0x%x\n", rv);
	//			break;
	//		}
	//
	//
	//		rv = SDF_ExportEncPublicKey_RSA(m_phSessionHandle, keyIndx, &rsapuk);
	//		rv = SDF_ExportSignPublicKey_RSA(m_phSessionHandle, keyIndx, &rsapukSign);
	//		if (0 != memcmp(&rsapuk, &rsapukSign, sizeof(rsapuk)))
	//		{
	//			printf("SDF_ExportSignPublicKey_RSA sign/enc is different\r\n");
	//		}
	//
	//		unsigned char keypin[9] = "12345678";
	//		rv = SDF_GetPrivateKeyAccessRight(m_phSessionHandle, keyIndx, keypin, 8);
	//		if (rv != SDR_OK) {
	//			printf("SDF_GetPrivateKeyAccessRight is error 0x%x\n", rv);
	//			break;
	//		}
	//
	//		deLenTmp = 256;
	//		rv = SDF_InternalPrivateKeyOperation_RSA(m_phSessionHandle, keyIndx, deIn, bit / 8, deOut, &deLen);
	//		rv = SDF_InternalPublicKeyOperation_RSA(m_phSessionHandle, keyIndx, deOut, deLen, deTmp, &deLenTmp);
	//		if ((rv != SDR_OK) || 0 == deLenTmp || 0 != memcmp(deIn, deTmp, deLenTmp))
	//		{
	//			printf("SDF_InternalPublicKeyOperation_RSA result is error 0x%x\n", rv);
	//			break;
	//		}
	//		rv = SDF_ExternalPublicKeyOperation_RSA(m_phSessionHandle, &rsapukSign, deOut, deLen, deTmp, &deLenTmp);
	//		if ((rv != SDR_OK) || 0 == deLenTmp || 0 != memcmp(deIn, deTmp, deLenTmp))
	//		{
	//			printf("SDF_InternalPublicKeyOperation_RSA result is error 0x%x\n", rv);
	//			break;
	//		}


			/*******************************************************/
			// 		pubKeyLenKEK = sizeof(pubKeyKEK);
			// 		rv = SDF_GenerateKeyWithKEK(m_phSessionHandle, 16 * 8, SGD_SM4_ECB, keyIndx, pubKeyKEK, &pubKeyLenKEK, &key[0]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_GenerateKeyWithKEK SGD_SM4_ECB is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 		rv = SDF_ImportKeyWithKEK(m_phSessionHandle, SGD_SM4_ECB, keyIndx, pubKeyKEK, 16, &key[2]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_ImportKeyWithKEK SGD_SM4_ECB is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 		pubKeyLenKEK = sizeof(pubKeyKEK);
			// 		rv = SDF_GenerateKeyWithKEK(m_phSessionHandle, 16 * 8, SGD_SM1_ECB, keyIndx, pubKeyKEK, &pubKeyLenKEK, &key[1]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_GenerateKeyWithKEK SGD_SM1_ECB is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		rv = SDF_ImportKeyWithKEK(m_phSessionHandle, SGD_SM1_ECB, keyIndx, pubKeyKEK, 16, &key[3]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_ImportKeyWithKEK SGD_SM1_ECB is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		pubKeyLen = sizeof(pubKey);
			// 		rv = SDF_GenerateKeyWithEPK_RSA(m_phSessionHandle, bit, &rsapuk, pubKey, &pubKeyLen, &key[4]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_GenerateKeyWithEPK_RSA is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		pubKeyLen = sizeof(pubKey);
			// 		rv = SDF_GenerateKeyWithIPK_RSA(m_phSessionHandle, keyIndx, bit, pubKey, &pubKeyLen, &key[5]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_GenerateKeyWithIPK_RSA is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		rv = SDF_ImportKeyWithISK_RSA(m_phSessionHandle, keyIndx, pubKey, pubKeyLen, &key[6]);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_ImportKeyWithISK_RSA is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		rv = SDF_ExchangeDigitEnvelopeBaseOnRSA(m_phSessionHandle, keyIndx, &rsapuk, deIn, sizeof(deIn) / 8, deOut, &deLen);
			// 		if (rv != SDR_OK) {
			// 			printf("SDF_ExchangeDigitEnvelopeBaseOnRSA is error 0x%x\n", rv);
			// 			break;
			// 		}
			// 
			// 		for (i = 0; i < 7; i++)
			// 		{
			// 			memset(deIn, 'd', sizeof(deIn));
			// 			rv = SDF_Encrypt(m_phSessionHandle, key[i], SGD_SM4_ECB, NULL, deIn, bit / 8, deOut, &deLen);
			// 			rv = SDF_Decrypt(m_phSessionHandle, key[i], SGD_SM4_ECB, NULL, deOut, deLen, deTmp, &deLenTmp);
			// 			if (0 != rv || bit / 8 != deLenTmp || 0 != memcmp(deIn, deTmp, 32))
			// 			{
			// 				printf("SDF_Decrypt Import is error 0x%x %d\n", rv, i);
			// 
			// 			}
			// 		}
			// 		if (i != 5)
			// 			break;
	//	} while (0);

	//	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, keyIndx);



	return rv;
}


int SDFtest::SM4_test()
{
	int i;
	int flag = 0;
	int rv = 0;
	unsigned char inData[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 }; //sm4
	unsigned char Key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char result[16] = { 0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46 };
	unsigned char pIv[16], pIndata[16], pEncdata[16], pOutdata[16];
	void *hKeyHandle = NULL;
	unsigned int nEnclen, nOutlen;
	unsigned int puiAlg = SGD_SM4_ECB;
	int nInlen = sizeof(inData);
	memcpy(pIndata, inData, nInlen);

	rv = SDF_ImportKey(m_phSessionHandle, Key, nInlen, &hKeyHandle);
	if (rv != SDR_OK) {

		return 0xFFFFFFFF;
	}
	/************************************  SM4 ECB 测试 *****************************************/
	//加密测试
	memset(pIv, 0, 16);
	rv = SDF_Encrypt(m_phSessionHandle, hKeyHandle, puiAlg, pIv, pIndata, nInlen, pEncdata, &nEnclen);
	if ((rv != SDR_OK) || (memcmp(pEncdata, result, nEnclen) != 0)) {
		//加密失败
		SDF_DestroyKey(m_phSessionHandle, hKeyHandle);
		return 0xFFFFFFFF;
	}
	//解密测试
	memset(pIv, 0, 16);
	rv = SDF_Decrypt(m_phSessionHandle, hKeyHandle, (unsigned int)puiAlg, pIv, pEncdata, nEnclen, pOutdata, &nOutlen);
	if ((rv != SDR_OK) || (memcmp(pOutdata, inData, nOutlen) != 0)) {
		//解密失败
		SDF_DestroyKey(m_phSessionHandle, hKeyHandle);
		return 0xFFFFFFFF;
	}
	rv = SDF_DestroyKey(m_phSessionHandle, hKeyHandle);
	if (rv != SDR_OK)
	{
		return 0xFFFFFFFF;
	}
	return 0;
}


void  SDFtest::TEST_ECC()
{
	//	int rv = -1;
	//	int keyIndex = 1;
	//	CK_VOID_PTR  hkey[128];
	//	ECCrefPublicKey		eccpuk;
	//	ECCrefPrivateKey	eccprk;
	//	ECCrefPublicKey pubkey;
	//	ECCrefPublicKey pubSigKey;
	//	ECCCipher		sm2cipherIPK, sm2cipherEPK, sesscipher;
	//
	//	ECCSignature		signstruct;
	//	ECCCipher		encrystruct;
	//	char inbuf[4096], outbuf[4096];
	//	int inlen = 128, outlen;
	//	memset(inbuf, 0x5a, 1024);
	//
	//
	//#if 1
	//	//导出ECC签名公钥
	//	rv = SDF_ExportSignPublicKey_ECC(m_phSessionHandle, keyIndex, &pubSigKey);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_ExportSignPublicKey_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_ExportSignPublicKey_ECC OK!\n");
	//
	//	//导出ECC加密公钥
	//	rv = SDF_ExportEncPublicKey_ECC(m_phSessionHandle, keyIndex, &pubkey);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_ExportEncPublicKey_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_ExportEncPublicKey_ECC OK!\n");
	//
	//	//产生ECC秘钥对并输出
	//	rv = SDF_GenerateKeyPair_ECC(m_phSessionHandle, SGD_SM2_1, 256, &eccpuk, &eccprk);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_GenerateKeyPair_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_GenerateKeyPair_ECC OK!\n");
	//#endif
	//	//生成会话秘钥并用内部ECC公钥加密输出
	//	rv = SDF_GenerateKeyWithIPK_ECC(m_phSessionHandle,
	//		1,
	//		128,
	//		&sm2cipherIPK,
	//		&hkey[0]);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_GenerateKeyWithIPK_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_GenerateKeyWithIPK_ECC OK!\n");
	//#if 0
	//	//生成会话秘钥并用外部ECC公钥加密输出
	//	rv = SDF_GenerateKeyWithEPK_ECC(m_phSessionHandle,
	//		128,
	//		SGD_SM2_3,
	//		&pubkey,
	//		&sm2cipherEPK,
	//		&hkey[1]);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_GenerateKeyWithEPK_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//	printf("=== SDF_GenerateKeyWithEPK_ECC OK!\n");
	//#endif
	//
	//	//导入会话密钥并用内部ECC私钥解密
	//	unsigned char kinpin[] = "12345678";
	//	if (SDF_GetPrivateKeyAccessRight(m_phSessionHandle, keyIndex, kinpin, 8) != SDR_OK) {
	//		printf("SDF_GetPrivateKeyAccessRight error! SM2 index:1 pas:12345678 \n");
	//		exit(-1);
	//	}
	//	rv = SDF_ImportKeyWithISK_ECC(m_phSessionHandle,
	//		keyIndex,
	//		&sm2cipherIPK,
	//		&hkey[2]);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_ImportKeyWithISK_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_ImportKeyWithISK_ECC OK!\n");
	//#if 0
	//	printf("\n\n========================== ECC算法运算 =======================\n");
	//
	//	//外部公钥加密
	//	rv = SDF_ExternalEncrypt_ECC(m_phSessionHandle, SGD_SM2_3, &pubkey, (CK_CHAR_PTR)inbuf, inlen, &encrystruct);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_ExternalEncrypt_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_ExternalEncrypt_ECC OK!\n");
	//	//内部私钥解密
	//	rv = SDF_InternalDecrypt_ECC(m_phSessionHandle, SGD_SM2_3, keyIndex, &encrystruct, (CK_CHAR_PTR)outbuf, (CK_UINT32_PTR)&outlen);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_InternalDecrypt_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_ExternalDecrypt_ECC OK!\n");
	//
	//	if (memcmp(inbuf, outbuf, outlen) != 0) {
	//		printf("error!\n");
	//		exit(-1);
	//	}
	//	else {
	//		printf("=== SDF_ExternalEncrypt_ECC -> SDF_InternalDecrypt_ECC ok!\n");
	//	}
	//
	//	//内部签名
	//	inlen = 32;
	//	rv = SDF_InternalSign_ECC(m_phSessionHandle, keyIndex, (CK_CHAR_PTR)inbuf, inlen, &signstruct);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_InternalSign_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_InternalSign_ECC OK!\n");
	//	//内部验签
	//	rv = SDF_InternalVerify_ECC(m_phSessionHandle, keyIndex, (CK_CHAR_PTR)inbuf, inlen, &signstruct);
	//
	//	if (rv != SDR_OK) {
	//		printf("SDF_InternalVerify_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//
	//	printf("=== SDF_InternalVerify_ECC OK!\n");
	//	//外部验签
	//
	//	rv = SDF_ExternalVerify_ECC(m_phSessionHandle, SGD_SM2_1, &pubSigKey, (CK_CHAR_PTR)inbuf, inlen, &signstruct);
	//	if (rv != SDR_OK)
	//	{
	//		printf("SDF_ExternalVerify_ECC error! rv = 0x%x\n", rv);
	//		exit(-1);
	//	}
	//	printf("=== SDF_ExternalVerify_ECC OK!\n");
	//
	//	rv = SDF_ReleasePrivateKeyAccessRight(m_phSessionHandle, keyIndex);
	//
	//	if (rv) {
	//		printf("SDF_ReleasePrivateKeyAccessRight is error 0x%x\n", rv);
	//		SDF_CloseSession(m_phSessionHandle);
	//		return;
	//	}
	//#endif
	//	// SDF_CloseSession(phSessionHandle);
}




int  SDFtest::correct_SM2PreSign()
{
	int rv;
	unsigned char in[32], hash[32];
	unsigned int inlen = 32, hashlen;
	ECCrefPublicKey eccpuk;
	ECCrefPrivateKey eccprk;
	ECCSignature signstruct;
	unsigned char id[] = "1234567812345678";

	memset(in, 0xa, 32);

	rv = SDF_GenerateKeyPair_ECC(m_phSessionHandle, SGD_SM2_3, 256, &eccpuk, &eccprk);
	if (rv != 0) {
		return rv;
	}

	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, &eccpuk, id, 16);
	if (rv != 0) {
		return rv;
	}

	rv = SDF_HashUpdate(m_phSessionHandle, in, inlen);
	if (rv != 0) {

		return rv;
	}

	rv = SDF_HashFinal(m_phSessionHandle, hash, &hashlen);
	if (rv != 0) {

		return rv;
	}

	return 0;
}

int SDFtest::correct_SM2PreVerify()
{
// 	int rv;
// 	unsigned char in[32], hash[32], r[32], s[32];
// 	unsigned int inlen = 32, hashlen, rlen, slen;
// 	ECCrefPublicKey eccpuk;
// 	ECCrefPrivateKey eccprk;
// 	ECCSignature signstruct;
// 	unsigned char id[] = "1234567812345678";
// 
// 	memset(in, 0xa, 32);
// 
// 	rv = SDF_GenerateKeyPair_ECC(m_phSessionHandle, SGD_SM2_3, 256, &eccpuk, &eccprk);
// 	if (rv != 0) {
// 		
// 		return rv;
// 	}
// 
// 	rv = SDF_HashInit(m_phSessionHandle, SGD_SM3, &eccpuk, id, 16);
// 	if (rv != 0) {
// 		return rv;
// 	}
// 
// 	rv = SDF_HashUpdate(m_phSessionHandle, in, inlen);
// 	if (rv != 0) {
// 
// 		return rv;
// 	}
// 
// 	rv = SDF_HashFinal(m_phSessionHandle, hash, &hashlen);
// 	if (rv != 0) {
// 
// 		return rv;
// 	}

// 	sm2_sign(hash, hashlen, eccprk.D + 32, 32, r, &rlen, s, &slen);
// 
// 	rv = sm2_sign_strcat(r, rlen, s, slen, &signstruct);
// 	if (rv != 0) {
// 		RTE_LOG(CORRECT_TEST, "sm2_sign_strcat failed!rv = 0x%08x\n", rv);
// 		return rv;
// 	}

// 	rv = SDF_ExternalVerify_ECC(m_phSessionHandle, SGD_SM2_1, &eccpuk, hash, hashlen, &signstruct);
// 	if (rv != 0) {
// 		
// 		return rv;
// 	}
	return 0;
}







































