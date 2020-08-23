#include "SDF.h"
#include "SDF_EX.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/SDFLog.h"


/*客户端库全局上下文对象*/
// extern sis_sdf_lib_ctx *context;
/*
描述：		指定使用外部公钥对数据进行运算
参数：		hSessionHandle[in]	    与设备建立的会话句柄
			pucPublicKey [in]	    外部RSA公钥结构
			pucDataInput [in]	    缓冲区指针，用于存放输入的数据
			uiInputLength[in]	    输入的数据长度
			pucDataOutput[out]	    缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		数据格式由应用层封装
*/
DLL u32 SDF_ExternalPublicKeyOperation_RSA(HANDLE hSessionHandle,
	RSArefPublicKey *pucPublicKey,
	u8* pucDataInput,
	u32 uiInputLength,
	u8* pucDataOutput,
	u32 *puiOutputLength)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if ((pucDataInput == NULL) || (pucDataOutput == NULL))
	{
		return SDR_INARGERR;
	}

	if (uiInputLength > 512)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ExternPublicKeyOperationEnc_RSA(session,
			*pucPublicKey,
			pucDataInput, uiInputLength,
			pucDataOutput, puiOutputLength);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ExternPublicKeyOperationEnc_RSA,ret(0x%x)",ret);
		}
	}

	return ret;
}

/*
描述：		使用内部指定索引的公钥对数据进行运算
参数：		hSessionHandle[in]	    与设备建立的会话句柄
			uiKeyIndex[in]	        密码设备内部存储公钥的索引值
			pucDataInput[in]	    缓冲区指针，用于存放外部输入的数据
			uiInputLength[in]	    输入的数据长度
			pucDataOutput[out]	    缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		索引范围仅限于内部签名密钥对，数据格式由应用层封装
*/
DLL u32 SDF_InternalPublicKeyOperation_RSA(
	HANDLE hSessionHandle,
	u32  uiKeyIndex,
	u8* pucDataInput,
	u32 uiInputLength,
	u8* pucDataOutput,
	u32* puiOutputLength)
{
	u32 ret = SDR_OK;

	sis_session* session = NULL;

	if (uiKeyIndex >= 1024 || uiKeyIndex <= 0)
	{
		return SDR_KEYERR;
	}

	if ((pucDataInput == NULL) || (uiInputLength > 512))
	{
		return SDR_INARGERR;
	}

	if (pucDataOutput == NULL)
	{
		return SDR_INARGERR;
	}

	// ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_InterPublicKeyOperation_RSA(session,
			uiKeyIndex,
			pucDataInput, uiInputLength,
			pucDataOutput, puiOutputLength);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_InterPublicKeyOperation_RSA,ret(0x%x)uiIPKIndex(%d)",ret, uiKeyIndex);
		}
	}

	return ret;
}

/*
描述：		使用内部指定索引的私钥对数据进行运算
参数：		hSessionHandle[in]	    与设备建立的会话句柄
			uiKeyIndex[in]	        密码设备内部存储私钥的索引值
			pucDataInput[in]	    缓冲区指针，用于存放外部输入的数据
			uiInputLength[in]	    输入的数据长度
			pucDataOutput[out]	    缓冲区指针，用于存放输出的数据
			puiOutputLength[out]	输出的数据长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		索引范围仅限于内部签名密钥对，数据格式由应用层封装
*/
DLL u32 SDF_InternalPrivateKeyOperation_RSA(
	HANDLE hSessionHandle,
	u32  uiKeyIndex,
	u8* pucDataInput,
	u32  uiInputLength,
	u8* pucDataOutput,
	u32* puiOutputLength)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiKeyIndex >= 1024 || uiKeyIndex <= 0)
	{
		return SDR_KEYERR;
	}

	if ((pucDataInput == NULL) || (uiInputLength > 512))
	{
		return SDR_INARGERR;
	}

	if (pucDataOutput == NULL)
	{
		*puiOutputLength = 512;
		return SDR_INARGERR;
	}

	// ret = LIB_GetSession(hSessionHandle,&session);
	if (SDR_OK == ret)
	{
		ret = C_InterPrivateKeyOperation_RSA(session,
			uiKeyIndex,
			pucDataInput, uiInputLength,
			pucDataOutput, puiOutputLength);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_InterPrivateKeyOperation_RSA,ret(0x%x)uiIPKIndex(%d)",ret, uiKeyIndex);
		}
	}

	return ret;
}

/*
描述：		使用内部ECC私钥对数据进行签名运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex [in]	    密码设备内部存储的ECC签名私钥的索引值
			pucData[in]	        缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature [out]	缓冲区指针，用于存放输出的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL u32 SDF_InternalSign_ECC(HANDLE hSessionHandle,
	u32  uiISKIndex,
	u8* pucData,
	u32  uiDataLength,
	ECCSignature *pucSignature)
{
	u32 ret = SDR_OK;
	sis_session *session = NULL;

	if (uiISKIndex >= 1024 || uiISKIndex <= 0) {
		return SDR_KEYERR;
	}

	if (uiDataLength != SM3_HASH_SIZE) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_InterSign_ECC(session,
			uiISKIndex,
			pucData,
			uiDataLength,
			pucSignature);

		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_InterSign_ECC,ret(0x%x)uiIPKIndex(%d)", ret, uiISKIndex);
		}
	}

	return ret;
}

/*
描述：		使用内部ECC公钥对ECC签名值进行验证运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiISKIndex [in]	    密码设备内部存储的ECC签名公钥的索引值
			pucData[in]	        缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature[in]	缓冲区指针，用于存放输入的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL u32 SDF_InternalVerify_ECC(HANDLE hSessionHandle,
	u32  uiISKIndex,
	u8* pucData,
	u32  uiDataLength,
	ECCSignature *pucSignature)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;

	if (uiISKIndex >= 1024 || uiISKIndex <= 0) {
		return SDR_KEYERR;
	}

	if (uiDataLength != SM3_HASH_SIZE) {
		// _SDF_Log(SDF_ERR, "------>SDF_InternalSign_ECC uiDataLength=%d", uiDataLength);
		return SDR_INARGERR;
	}
	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret) {
		ret = C_InterVerify_ECC(session,
			uiISKIndex,
			pucData,
			uiDataLength,
			pucSignature);

		if (SDR_OK != ret) {
			// _SDF_Log(SDF_ERR, "------>C_InterVerify_ECC,ret(0x%x)uiIPKIndex(%d)", ret, uiISKIndex);
		}
	}

	return ret;
}

/*
描述：		使用外部ECC公钥对ECC签名值进行验证运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	        算法标识，指定使用的ECC算法
			pucPublicKey[in]	外部ECC公钥结构
			pucData[in]	        缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucSignature[in]	缓冲区指针，用于存放输入的签名值数据
返回值：	0	成功
			非0	失败，返回错误代码
备注：		对原文的杂凑运算，在函数外部完成。
*/
DLL u32 SDF_ExternalVerify_ECC(HANDLE hSessionHandle,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	u8* pucDataInput,
	u32  uiInputLength,
	ECCSignature *pucSignature)
{
	u32 ret = SDR_OK;
	sis_session *session = NULL;

	if (uiInputLength != SM3_HASH_SIZE)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ExternVerify_ECC(session,
			uiAlgID,
			*pucPublicKey,
			pucDataInput,
			uiInputLength,
			pucSignature);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ExternVerify_ECC,ret(0x%x)uiAlgID(0x%x)",ret, uiAlgID);
		}
	}
	return ret;
}

/*
描述：		使用外部ECC公钥对数据进行加密运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			uiAlgID[in]	        算法标识，指定使用的ECC算法
			pucPublicKey[in]	外部ECC公钥结构
			pucData[in]	        缓冲区指针，用于存放外部输入的数据
			uiDataLength[in]	输入的数据长度
			pucEncData[out]	    缓冲区指针，用于存放输出的数据密文
返回值：	0	成功
			非0	失败，返回错误代码
备注：		输入的数据长度uiDataLength不大于ECCref_MAX_LEN。
*/
DLL u32 SDF_ExternalEncrypt_ECC(HANDLE hSessionHandle,
	u32 uiAlgID,
	ECCrefPublicKey *pucPublicKey,
	u8* pucData,
	u32  uiDataLength,
	ECCCipher *pucEncData)
{
	u32 ret = SDR_OK;
	sis_session *session = NULL;

	if (uiDataLength > MAX_ECC_CIPHERLEN)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (SDR_OK == ret)
	{
		ret = C_ExternalEncrypt_ECC(session,
			uiAlgID,
			*pucPublicKey,
			pucData,
			uiDataLength,
			pucEncData);
		if (SDR_OK != ret)
		{
			// _SDF_Log(SDF_ERR, "------>C_ExternalEncrypt_ECC,ret(0x%x)uiAlgID(0x%x)", ret, uiAlgID);
		}
	}
	return ret;
}





