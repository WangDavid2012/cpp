#include "SDF.h"
#include "SDF_EX.h"
#include "../base/SDFLog.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "debug.h"





//#define DEBUG_SM2
#if 1
void print_rsa_puc_key(const RSArefPublicKey *puc_key)
{
	int i = 0;
	printf("bits:0x%x.", puc_key->bits);
	for (i = 0; i < RSAref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", puc_key->m[i]);
	}
	for (i = 0; i < RSAref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", puc_key->e[i]);
	}
	printf("\n");
}
void print_rsa_pri_key(const RSArefPrivateKey *pri_key)
{
	int i = 0;
	printf("bits:0x%x.", pri_key->bits);
	for (i = 0; i < RSAref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", pri_key->m[i]);
	}
	for (i = 0; i < RSAref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", pri_key->e[i]);
	}
	for (i = 0; i < RSAref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", pri_key->d[i]);
	}
	//    for(i = 0; i < RSAref_MAX_PLEN * 2; i++)
	//    {
	//        if(i % 16 == 0)
	//            printf("\n");
	//        printf("%02x ",pri_key->prime[i]);
	//    }
	//    for(i = 0; i < RSAref_MAX_PLEN * 2; i++)
	//    {
	//        if(i % 16 == 0)
	//            printf("\n");
	//        printf("%02x ",pri_key->pexp[i]);
	//    }
	for (i = 0; i < RSAref_MAX_PLEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", pri_key->coef[i]);
	}

	printf("\n");
}

void print_ecc_puc_key(const ECCrefPublicKey *puc_key)
{
	int i = 0;
	printf("bits:0x%x.", puc_key->bits);
	for (i = 0; i < ECCref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", puc_key->x[i]);
	}
	for (i = 0; i < ECCref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", puc_key->y[i]);
	}
	printf("\n");
}
void print_ecc_pri_key(const ECCrefPrivateKey *pri_key)
{
	int i = 0;
	printf("bits:0x%x.", pri_key->bits);
	for (i = 0; i < ECCref_MAX_LEN; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", pri_key->D[i]);
	}
	printf("\n");
}
#endif

/*
描述：		导出密码设备内部存储的指定索引位置的签名公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的RSA密钥对索引值
			pucPublicKey[out]	RSA公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
u32 SDF_ExportSignPublicKey_RSA(HANDLE hSessionHandle,
	u32  uiKeyIndex,
	RSArefPublicKey *pucPublicKey)
{
	u32 ret = 0;

	//     if(NULL == pucPublicKey)
	//         return SDR_INARGERR;

	//     if(uiKeyIndex >= 1024 || uiKeyIndex <= 0)
	//     {
	//         return SDR_KEYERR;
	//     }

	//     sis_session* session = NULL;
	//     // ret = LIB_GetSession(hSessionHandle,&session);
	//     if(ret == SDR_OK)
	//     {
	//         u32 pPubKeyLengthDer = RSAref_PublicKey_SIZE;
	//         ret = C_GetPubSignKey_RSA(session,
	//                                   uiKeyIndex,
	//                                   pucPublicKey,
	//                                   &pPubKeyLengthDer);
	//         if (ret != SDR_OK)
	//         {
	//             // _SDF_Log(SDF_ERR, "------>C_GetPubSignKey_RSA,uiKeyIndex=%d,", uiKeyIndex);
	//             return ret;
	//         }
	// #ifdef DEBUG_SM2
	//         print_rsa_puc_key(pucPublicKey);
	// #endif
	//     }

	return ret;
}

/*
描述：		导出密码设备内部存储的指定索引位置的加密公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的RSA密钥对索引值
			pucPublicKey[out]	RSA公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
u32 SDF_ExportEncPublicKey_RSA(HANDLE hSessionHandle,
	u32  uiKeyIndex,
	RSArefPublicKey *pucPublicKey)
{
	u32 ret = 0;

	//     if(NULL == pucPublicKey)
	//         return SDR_INARGERR;

	//     if(uiKeyIndex >= context->ecckey_count || uiKeyIndex <= 0)
	//     {
	//         return SDR_KEYERR;
	//     }

	//     sis_session* session = NULL;
	//     // ret = LIB_GetSession(hSessionHandle,&session);
	//     if(ret == SDR_OK)
	//     {
	//         u32 pPubKeyLengthDer = RSAref_PublicKey_SIZE;
	//         ret = C_GetPubEncKey_RSA(session,
	//                                  uiKeyIndex,
	//                                  pucPublicKey,
	//                                  &pPubKeyLengthDer);
	//         if (ret != SDR_OK)
	//         {
	//             // _SDF_Log(SDF_ERR, "------>C_GetPubSignKey_RSA,uiKeyIndex=%d,", uiKeyIndex);
	//             return ret;
	//         }
	// #ifdef DEBUG_SM2
	//         print_rsa_puc_key(pucPublicKey);
	// #endif
	//     }

	return ret;
}


/*
描述：		请求密码设备产生指定模长的RSA密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits [in]	    指定密钥模长
			pucPublicKey[out]	RSA公钥结构
			pucPrivateKey[out]	RSA私钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
u32 SDF_GenerateKeyPair_RSA(HANDLE hSessionHandle,
	u32  uiKeyBits,
	RSArefPublicKey *pucPublicKey,
	RSArefPrivateKey *pucPrivateKey)
{
	u32 ret = 0;
	//     if(NULL == pucPublicKey || NULL == pucPrivateKey)
	//     {
	//         return SDR_INARGERR;
	//     }

	//     if(1024 != uiKeyBits && 2048 != uiKeyBits && 4096 != uiKeyBits)
	//         return SDR_INARGERR;

	//     sis_session* session = NULL;
	//     // ret = LIB_GetSession(hSessionHandle,&session);
	//     if(ret == SDR_OK)
	//     {
	//         ret = C_GenKeyPair_RSA(session,
	//                                uiKeyBits,
	//                                pucPublicKey,
	//                                pucPrivateKey);
	//         if (ret != SDR_OK)
	//         {
	//             // _SDF_Log(SDF_ERR,"------>C_GenKeyPair_RSA,uiKeyBits=%d",uiKeyBits);
	//             return ret;
	//         }
	// #ifdef DEBUG_SM2
	//         print_rsa_puc_key(pucPublicKey);
	//         print_rsa_pri_key(pucPrivateKey);
	// #endif
	//     }

	return ret;
}

/*
描述：		生成会话密钥并用指定索引的内部加密公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiIPKIndex[in]	    密码设备内部存储公钥的索引值
			uiKeyBits[in]	    指定产生的会话密钥长度
			pucKey[out]	        缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		公钥加密数据时填充方式按照PKCS#1 v1.5的要求进行；返回的密钥不包含IV部分.
*/
u32 SDF_GenerateKeyWithIPK_RSA(HANDLE hSessionHandle,
	u32 uiIPKIndex,
	u32 uiKeyBits,
	u8* pucKey,
	u32* puiKeyLength,
	HANDLE* phKeyHandle)
{
	u32 ret = 0;
	// if(NULL == puiKeyLength || NULL == pucKey)
	// {
	//     return SDR_INARGERR;
	// }

	// if (uiIPKIndex >= context->rsakey_count || uiIPKIndex <= 0)
	// {
	//     return SDR_KEYERR;
	// }

	// sis_session* session = NULL;
	// // ret = LIB_GetSession(hSessionHandle,&session);
	// if(ret == SDR_OK)
	// {
	//     ret = C_GenKeyWithIPK_RSA(session,
	//                               uiIPKIndex,
	//                               uiKeyBits,
	//                               SGD_RSA,
	//                               pucKey,
	//                               puiKeyLength,
	//                               phKeyHandle);

	//     if (ret != SDR_OK)
	//     {
	//         // _SDF_Log(SDF_ERR,"------>C_GenKeyWithIPK_RSA,uiIPKIndex=%d",uiIPKIndex);
	//         return ret;
	//     }
	// }

	return ret;
}

/*
描述：		生成会话密钥并用外部公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	    指定产生的会话密钥长度
			pucPublicKey[in]	输入的外部RSA公钥结构
			pucKey[out]	        缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		公钥加密数据时填充方式按照PKCS#1 v1.5的要求进行；返回的密钥不包含IV部分.
*/
u32 SDF_GenerateKeyWithEPK_RSA(HANDLE hSessionHandle,
	u32 uiKeyBits,
	RSArefPublicKey *pucPublicKey,
	u8* pucKey,
	u32* puiKeyLength,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	// sis_session* session = NULL;

	// if (NULL == pucPublicKey || NULL == pucKey)
	//     return SDR_INARGERR;

	// // ret = LIB_GetSession(hSessionHandle,&session);
	// if(SDR_OK == ret)
	// {
	//     ret = C_GenKeyWithEPK_RSA(session,
	//                               uiKeyBits,
	//                               SGD_RSA,
	//                               pucPublicKey,
	//                               pucKey,
	//                               puiKeyLength,
	//                               phKeyHandle);
	//     if(SDR_OK != ret)
	//     {
	//         // _SDF_Log(SDF_ERR, "------>SDF_GenerateKeyWithIPK_ECC failed.ret(0x%x).",ret);
	//     }
	// }

	return ret;
}

/*
描述：		导入会话密钥并用内部私钥解密，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex[in]	    密码设备内部存储加密私钥的索引值，对应于加密时的公钥
			pucKey[in]	        缓冲区指针，用于存放输入的密钥密文
			puiKeyLength[in]	输入的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		填充方式与公钥加密时相同.
*/
u32 SDF_ImportKeyWithISK_RSA(HANDLE hSessionHandle,
	u32 uiISKIndex,
	u8* pucKey,
	u32 uiKeyLength,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	// sis_session* session = NULL;

	// if (uiISKIndex >= context->rsakey_count || uiISKIndex <= 0)
	//     return SDR_KEYERR;

	// if ((pucKey == NULL) || (uiKeyLength > 512))
	//     return SDR_INARGERR;

	// // ret = LIB_GetSession(hSessionHandle,&session);
	// if(SDR_OK == ret)
	// {
	//     ret = C_ImportKeyWithISK_RSA(session,
	//                                  uiISKIndex,
	//                                  pucKey,
	//                                  uiKeyLength,
	//                                  phKeyHandle);
	//     if(SDR_OK != ret)
	//     {
	//         // _SDF_Log(SDF_ERR, "------>C_ImportKeyWithISK_RSA failed.ret(0x%x),uiIPKIndex(%d).", ret,uiISKIndex);
	//     }
	// }

	return ret;
}


/*
描述：		将由内部加密公钥加密的会话密钥转换为由外部指定的公钥加密，可用于数字信封转换.
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的内部RSA密钥对索引值
			pucPublicKey [in]	外部RSA公钥结构
			pucDEInput [in]	    缓冲区指针，用于存放输入的会话密钥密文
			uiDELength[in]	    输入的会话密钥密文长度
			pucDEOutput[out]	缓冲区指针，用于存放输出的会话密钥密文
			puiDELength[out]	输出的会话密钥密文长度
返回值：	0	成功
			非0	失败，返回错误代码
*/
u32 SDF_ExchangeDigitEnvelopeBaseOnRSA(HANDLE hSessionHandle,
	u32  uiKeyIndex,
	RSArefPublicKey *pucPublicKey,
	u8* pucDEInput,
	u32  uiDELength,
	u8* pucDEOutput,
	u32* puiDELength)
{
	u32 ret = SDR_OK;
	// sis_session* session = NULL;

	// if(uiKeyIndex >= context->rsakey_count || uiKeyIndex <= 0)
	// {
	//     return SDR_KEYERR;
	// }

	// if ((pucPublicKey == NULL) || (pucDEInput == NULL) || (uiDELength == 0))
	// {
	//     return SDR_INARGERR;
	// }

	// if(pucDEOutput == NULL )
	// {
	//     *puiDELength = (pucPublicKey->bits + 7) / 8;
	//     return SDR_INARGERR;
	// }

	// // ret = LIB_GetSession(hSessionHandle,&session);
	// if(SDR_OK == ret)
	// {
	//     ret = C_ExchangeEnvelope_RSA(session,
	//                                  uiKeyIndex,
	//                                  *pucPublicKey,
	//                                  pucDEInput,
	//                                  uiDELength,
	//                                  pucDEOutput,
	//                                  puiDELength);
	//     if(SDR_OK != ret)
	//     {
	//         // _SDF_Log(SDF_ERR, "------>C_ExchangeEnvelope_RSA failed,ret(0x%x)uiIPKIndex(%d)", ret,uiKeyIndex);
	//     }
	// }

	return ret;
}

/*
描述：		导出密码设备内部存储的指定索引位置的签名公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的ECC密钥对索引值
			pucPublicKey[out]	ECC公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_ExportSignPublicKey_ECC(HANDLE hSessionHandle,
	u32  uiKeyIndex,
	ECCrefPublicKey *pucPublicKey)
{
	u32 ret = 0;

	if (uiKeyIndex >= 1024 || uiKeyIndex <= 0)
	{
		return SDR_KEYERR;
	}

	sis_session *session = NULL;
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		u32 pPubKeyLengthDer = ECCref_PublicKey_SIZE;
		ret = C_GetPubSignKey_ECC(session,
			uiKeyIndex,
			pucPublicKey,
			&pPubKeyLengthDer);
		if (ret != SDR_OK)
		{
			// _SDF_Log(SDF_ERR, "------>C_GetPubSignKey_ECC,uiKeyId=%d,", uiKeyIndex);
			return ret;
		}
#ifdef DEBUG_SM2
		print_ecc_puc_key(pucPublicKey);
#endif
	}

	return ret;
}

/*
描述：		导出密码设备内部存储的指定索引位置的加密公钥
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的ECC密钥对索引值
			pucPublicKey[out]	ECC公钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_ExportEncPublicKey_ECC(HANDLE hSessionHandle,
	u32  uiKeyId,
	ECCrefPublicKey *pucPublicKey)
{
	u32 ret = 0;

	if (uiKeyId >= 1024 || uiKeyId <= 0) {
		return SDR_KEYERR;
	}

	sis_session* session = NULL;
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK) {
		u32 pPubKeyLengthDer = ECCref_PublicKey_SIZE;
		ret = C_GetPubEncKey_ECC(session,
			uiKeyId,
			pucPublicKey,
			&pPubKeyLengthDer);
		if (ret != SDR_OK) {
			//_SDF_Log(SDF_ERR, "------>C_GetPubEncKey_ECC,ErrorCode:0x%02x,", ret);
			return ret;
		}
#ifdef DEBUG_SM2
		print_ecc_puc_key(pucPublicKey);
#endif
	}

	return ret;
}
/*
描述：		请求密码设备产生指定类型和模长的ECC密钥对
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	        指定算法标识
			uiKeyBits [in]	    指定密钥长度
			pucPublicKey[out]	ECC公钥结构
			pucPrivateKey[out]	ECC私钥结构
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_GenerateKeyPair_ECC(HANDLE hSessionHandle,
	u32  uiAlgID, u32  uiKeyBits,
	ECCrefPublicKey *pucPublicKey,
	ECCrefPrivateKey *pucPrivateKey)
{
	u32 ret = 0;
	if (NULL == pucPublicKey || NULL == pucPrivateKey)
	{
		return SDR_INARGERR;
	}

	if (256 != uiKeyBits && 512 != uiKeyBits)
		return SDR_INARGERR;

	if (SGD_SM2_1 != uiAlgID && SGD_SM2_2 != uiAlgID && SGD_SM2_3 != uiAlgID && SGD_SM2 != uiAlgID)
		return SDR_INARGERR;

	sis_session* session = NULL;
	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret == SDR_OK)
	{
		ret = C_GenKeyPair_ECC(session,
			SGD_SM2,
			uiKeyBits,
			pucPublicKey,
			pucPrivateKey);
		if (ret != SDR_OK)
		{
			debug_printf("ErrorCode:0x%02x\n",ret);
			return ret;
		}
#ifdef DEBUG_SM2
		print_ecc_puc_key(pucPublicKey);
		print_ecc_pri_key(pucPrivateKey);
#endif
	}

	return ret;
}

/*
描述：		生成会话密钥并用指定索引的内部ECC加密公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiIPKIndex[in]	    密码设备内部存储公钥的索引值
			uiKeyBits[in]	    指定产生的会话密钥长度
			pucKey[out]	        缓冲区指针，用于存放返回的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		返回的密钥不包含IV部分.
*/
DLL u32 SDF_GenerateKeyWithIPK_ECC(HANDLE hSessionHandle,
	u32 uiIPKIndex,
	u32 uiKeyBits,
	ECCCipher *pucKey,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;
	//u32 pucKeyLen;

	// _SDF_Log(SDF_INFO,"SDF_GenerateKeyWithIPK_ECC starting......");

	if (uiIPKIndex >= 1024 || uiIPKIndex <= 0)
	{
		return SDR_KEYERR;
	}

	// ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_GenKeyWithIPK_ECC(session,
			uiIPKIndex,
			uiKeyBits,
			SGD_SM2_3,
			pucKey,
			phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_GenKeyWithIPK_ECC uiIPKIndex=%d", uiIPKIndex);
		}
	}

	return ret;
}


/*
描述：		生成会话密钥并用外部ECC公钥加密输出，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	    指定产生的会话密钥长度
			uiAlgID[in]	        外部ECC公钥的算法标识
			pucPublicKey[in]	输入的外部ECC公钥结构
			pucKey[out]	        缓冲区指针，用于存放返回的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		返回的密钥不包含IV部分.
*/
DLL u32 SDF_GenerateKeyWithEPK_ECC(HANDLE hSessionHandle,
	u32 uiKeyBits,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	ECCCipher *pucKey,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (NULL == pucPublicKey || NULL == pucKey)
		return SDR_INARGERR;

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_GenKeyWithEPK_ECC(session,
			uiKeyBits,
			SGD_SM2_3,
			*pucPublicKey,
			pucKey,
			phKeyHandle);
		if (SDR_OK != ret)
		{
			//_SDF_Log(SDF_ERR, "------>C_GenKeyWithEPK_ECC failed,ret(0x%x),uiKeyBits(%d)", ret, uiKeyBits);
		}
	}

	return ret;
}

/*
描述：		导入会话密钥并用内部ECC加密私钥解密，同时返回密钥句柄
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex[in]	    密码设备内部存储加密私钥的索引值，对应于加密时的公钥
			pucKey[in]	        缓冲区指针，用于存放输入的密钥密文
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_ImportKeyWithISK_ECC(HANDLE hSessionHandle,
	u32 uiISKIndex,
	ECCCipher *pucKey,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiISKIndex >= 1024 || uiISKIndex <= 0)
		return SDR_KEYERR;

	if (NULL == pucKey)
		return SDR_INARGERR;

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ImportKeyWithISK_ECC(session,
			uiISKIndex,
			*pucKey,
			phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ImportKeyWithISK_ECC uiIPKIndex=%d", uiISKIndex);
		}
	}

	return ret;
}


/* 生成密钥协商参数并输出*/
DLL u32 SDF_GenerateAgreementDataWithECC(
	HANDLE hSessionHandle,
	u32 uiISKIndex,
	u32 uiKeyBits,
	u8* pucSponsorID,
	u32 uiSponsorIDLength,
	ECCrefPublicKey  *pucSponsorPublicKey,
	ECCrefPublicKey  *pucSponsorTmpPublicKey,
	HANDLE* phAgreementHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_GenerateAgreementDataWithECC(session,
			uiISKIndex,
			uiKeyBits,
			pucSponsorID,
			uiSponsorIDLength,
			pucSponsorPublicKey,
			pucSponsorTmpPublicKey,
			phAgreementHandle);

		if (ret != 0)
		{
			// _SDF_Log(SDF_ERR, "------>C_GenerateAgreementDataWithECC,ret(%d)", ret);
			return ret;
		}
	}

	return ret;
}

/* 计算会话密钥*/
DLL u32 SDF_GenerateKeyWithECC(
	HANDLE hSessionHandle,
	u8* pucResponseID,
	u32 uiResponseIDLength,
	ECCrefPublicKey *pucResponsePublicKey,
	ECCrefPublicKey *pucResponseTmpPublicKey,
	HANDLE phAgreementHandle,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucResponsePublicKey == NULL)
		|| (pucResponseTmpPublicKey == NULL))
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_GenerateKeyWithECC(session,
			pucResponseID,
			uiResponseIDLength,
			*pucResponsePublicKey,
			*pucResponseTmpPublicKey,
			phAgreementHandle,
			phKeyHandle);
		if (ret != 0)
		{
			// _SDF_Log(SDF_ERR, "------>C_GenerateKeyWithECC,ret=%d", ret);
			return ret;
		}
	}

	return ret;
}

/* 产生协商参数并计算会话密钥*/
DLL u32 SDF_GenerateAgreementDataAndKeyWithECC(
	HANDLE hSessionHandle,
	u32 uiISKIndex,
	u32 uiKeyBits,
	u8* pucResponseID,
	u32 uiResponseIDLength,
	u8* pucSponsorID,
	u32 uiSponsorIDLength,
	ECCrefPublicKey *pucSponsorPublicKey,
	ECCrefPublicKey *pucSponsorTmpPublicKey,
	ECCrefPublicKey  *pucResponsePublicKey,
	ECCrefPublicKey  *pucResponseTmpPublicKey,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucResponsePublicKey == NULL)
		|| (pucResponseTmpPublicKey == NULL))
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_GenerateAgreementDataAndKeyWithECC(session,
			uiISKIndex,
			uiKeyBits,
			pucResponseID,
			uiResponseIDLength,
			pucSponsorID,
			uiSponsorIDLength,
			*pucSponsorPublicKey,
			*pucSponsorTmpPublicKey,
			pucResponsePublicKey,
			pucResponseTmpPublicKey,
			phKeyHandle);
		if (ret != 0)
		{
			// _SDF_Log(SDF_ERR, "------>C_GenerateAgreementDataAndKeyWithECC,ret=%d", ret);
			return ret;
		}
	}

	return ret;
}

/*
描述：		将由内部加密公钥加密的会话密钥转换为由外部指定的公钥加密，可用于数字信封转换.
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyIndex[in]	    密码设备存储的ECC密钥对索引值
			uiAlgID[in]	        外部ECC公钥的算法标识
			pucPublicKey [in]	外部ECC公钥结构
			pucEncDataIn[in]	缓冲区指针，用于存放输入的会话密钥密文
			pucEncDataOut[out]	缓冲区指针，用于存放输出的会话密钥密文
返回值：	0	成功
			非0	失败，返回错误代码
*/
DLL u32 SDF_ExchangeDigitEnvelopeBaseOnECC(HANDLE hSessionHandle,
	u32  uiKeyIndex,
	u32  uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	ECCCipher *pucEncDataIn,
	ECCCipher *pucEncDataOut)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiKeyIndex >= 1024 || uiKeyIndex <= 0)
	{
		return SDR_KEYERR;
	}

	if ((pucPublicKey == NULL) || (pucEncDataIn == NULL))
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ExchangeEnvelope_ECC(session,
			SGD_SM2_3,
			uiKeyIndex,
			*pucPublicKey,
			*pucEncDataIn,
			pucEncDataOut);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ExchangeEnvelope_ECC failed,ret(0x%x)uiIPKIndex(%d).", ret, uiKeyIndex);
		}
	}

	return ret;
}

/*
描述：		生成会话密钥并用密钥加密密钥加密输出，同时返回密钥句柄.
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiKeyBits[in]	    指定产生的会话密钥长度
			uiAlgID[in]	        算法标识，指定对称加密算法
			uiKEKIndex[in]	    密码设备内部存储密钥加密密钥的索引值
			pucKey[out]	        缓冲区指针，用于存放返回的密钥密文
			puiKeyLength[out]	返回的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式.
*/
DLL u32 SDF_GenerateKeyWithKEK(HANDLE hSessionHandle,
	u32 uiKeyBits,
	u32  uiAlgID,
	u32 uiKEKIndex,
	u8* pucKey,
	u32*  puiKeyLength,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiKEKIndex >= 1024 || uiKEKIndex <= 0)
	{
		return SDR_KEYERR;
	}

	if (uiAlgID != SGD_SM4_ECB)
	{
		return SDR_ALGNOTSUPPORT;
	}

	if (uiKeyBits == 0)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_GenKeyWithKEK(session,
			uiKEKIndex,
			uiAlgID,
			uiKeyBits,
			pucKey,
			puiKeyLength,
			phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_GenKeyWithKEK failed.ret(0x%x).",ret);
		}
	}

	return ret;
}

/*
描述：		导入会话密钥并用密钥加密密钥解密，同时返回会话密钥句柄.
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	        算法标识，指定对称加密算法
			uiKEKIndex[in]	    密码设备内部存储密钥加密密钥的索引值
			pucKey[in]	        缓冲区指针，用于存放输入的密钥密文
			puiKeyLength[in]	输入的密钥密文长度
			phKeyHandle[out]	返回的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		加密模式使用ECB模式.
*/
DLL u32 SDF_ImportKeyWithKEK(HANDLE hSessionHandle,
	u32  uiAlgID,
	u32 uiKEKIndex,
	u8* pucKey,
	u32 uiKeyLength,
	HANDLE* phKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiAlgID != SGD_SM4_ECB)
	{
		return SDR_ALGNOTSUPPORT;
	}

	if (uiKEKIndex >= 1024 || uiKEKIndex <= 0)
	{
		return SDR_KEYERR;
	}

	if ((pucKey == NULL) || (uiKeyLength > 512))
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);

	if (SDR_OK == ret)
	{
		ret = C_ImportKeyWithKEK(session,
			uiKEKIndex,
			uiAlgID,
			pucKey,
			uiKeyLength,
			phKeyHandle);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ImportKeyWithKEK failed, ret(0x%x),uiIPKIndex(%d).", ret, uiKEKIndex);
		}
	}

	return ret;
}



/*
描述：		销毁会话密钥，并释放为密钥句柄分配的内存等资源.
参数：		hSessionHandle[in]	与设备建立的会话句柄
			hKeyHandle[in]	    输入的密钥句柄
返回值：	0	成功
			非0	失败，返回错误代码
备注：		在对称算法运算完成后，应调用本函数销毁会话密钥.
*/
DLL u32 SDF_DestroyKey(HANDLE hSessionHandle,
	HANDLE hKeyHandle)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;
	sis_work_key* key = NULL;

	if (hKeyHandle == NULL)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret != SDR_OK)
	{
		debug_printf("LIB_GetSession error\n");
	}
	ret = LIB_GetWorkKey(session, hKeyHandle, &key);
	if (ret != SDR_OK)
	{
		debug_printf("LIB_GetWorkKey error\n");
	}
	if (SDR_OK == ret)
	{
		ret = C_DestorySymKey(session, key);
		if (SDR_OK != ret)
		{
			debug_printf("C_DestorySymKey errorCode:0x%02x\n",ret);
		}
	}

	return ret;
}







































