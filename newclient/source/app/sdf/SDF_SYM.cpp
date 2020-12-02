#include "SDF.h"
#include "SDF_EX.h"
#include "../base/SDFLog.h"
#include "../api/C_API.h"
#include "../api/C_API_EX.h"
#include "../base/Context.h"
#include "../base/Common.h"
#include "debug.h"
/*
描述：使用指定的密钥句柄和IV对数据进行对称加密运算
参数：	hSessionHandle[in]	        与设备建立的会话句柄
			hKeyHandle[in]	        指定的密钥句柄
			uiAlgID[in]	            算法标识，指定对称加密算法
			pucIV[in|out]	        缓冲区指针，用于存放输入和返回的IV数据
			pucData[in]	            缓冲区指针，用于存放输入的数据明文
			uiDataLength[in]	    输入的数据明文长度
			pucEncData[out]	        缓冲区指针，用于存放输出的数据密文
			puiEncDataLength[out]	输出的数据密文长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		此函数不对数据进行填充处理，输入的数据必须是指定算法分组长度的整数倍.
*/

DLL u32 SDF_Encrypt(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8 *pucIV,
	u8 *pucData,
	u32 uiDataLength,
	u8 *pucEncData,
	u32  *puiEncDataLength)
{
	u32 ret = SDR_OK;
	sis_session *session = NULL;
	sis_work_key *key = NULL;

	if (pucEncData == NULL)
	{
		return SDR_INARGERR;
	}

	if ((uiAlgID != SGD_SM4_ECB) && (uiAlgID != SGD_SM4_CBC) && (uiAlgID != SGD_SM4_OFB) && (uiAlgID != SGD_SM4_CFB) &&
		(uiAlgID != SGD_SM1_ECB) && (uiAlgID != SGD_SM1_CBC) && (uiAlgID != SGD_SM1_OFB) && (uiAlgID != SGD_SM1_CFB))
	{
		return SDR_ALGNOTSUPPORT;
	}

	if (pucData == NULL)
	{
		return SDR_INARGERR;
	}

	if ((uiDataLength % SM14_CHUNK_SIZE) != 0)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	if (ret != SDR_OK)
	{
		debug_printf("LIB_GetSession error\n");
	}
	debug_printf("-----------the size is %d\n", session->device->worklist->size);
	ret = LIB_GetWorkKey(session, hKeyHandle, &key);
	if (ret != SDR_OK)
	{
		debug_printf("LIB_GetWorkKey error\n");
	}

	if (ret == SDR_OK)
	{
		ret = C_Encrypt(session, uiAlgID, key, pucIV, pucData, uiDataLength, pucEncData, puiEncDataLength);
		if (ret == SDR_OK) {
			//_SDF_Log(SDF_INFO,"SDF_Encrypt complete......\n");
		
		}
		else {
			// _SDF_Log(SDF_ERR, "------>SDF_Encrypt,puiEncDataLength=%d", *puiEncDataLength);
			debug_printf("C_Encrypt error\n");
		}
	}
	return ret;
}



/*
描述：		使用指定的密钥句柄和IV对数据进行对称解密运算
参数：		hSessionHandle[in]	与设备建立的会话句柄
			hKeyHandle[in]	    指定的密钥句柄
			uiAlgID[in]	        算法标识，指定对称加密算法
			pucIV[in|out]	    缓冲区指针，用于存放输入和返回的IV数据
			pucEncData[in]	    缓冲区指针，用于存放输入的数据密文
			uiEncDataLength[in]	输入的数据密文长度
			pucData[out]	    缓冲区指针，用于存放输出的数据明文
			puiDataLength[out]	输出的数据明文长度
返回值：	0	成功
			非0	失败，返回错误代码
备注：		此函数不对数据进行填充处理，输入的数据必须是指定算法分组长度的整数倍.
*/
DLL u32 SDF_Decrypt(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8 *pucIV,
	u8 *pucEncData,
	u32 uiEncDataLength,
	u8 *pucData,
	u32  *puiDataLength)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;
	sis_work_key *key = NULL;

	if (pucEncData == NULL)
	{
		return SDR_INARGERR;
	}

	if ((uiAlgID != SGD_SM4_ECB) && (uiAlgID != SGD_SM4_CBC) && (uiAlgID != SGD_SM4_OFB) && (uiAlgID != SGD_SM4_CFB) &&
		(uiAlgID != SGD_SM1_ECB) && (uiAlgID != SGD_SM1_CBC) && (uiAlgID != SGD_SM1_OFB) && (uiAlgID != SGD_SM1_CFB))
	{
		return SDR_ALGNOTSUPPORT;
	}

	if (pucData == NULL)
	{
		return SDR_INARGERR;
	}

	if ((uiEncDataLength % SM14_CHUNK_SIZE) != 0)
	{
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	ret = LIB_GetWorkKey(session, hKeyHandle, &key);
	if (ret == SDR_OK)
	{
		ret = C_Decrypt(session, uiAlgID, key, pucIV, pucEncData, uiEncDataLength, pucData, puiDataLength);
		if (ret == SDR_OK)
		{
			// _SDF_Log(SDF_INFO,"SDF_Decrypt complete......\n");
		}
		else
		{
			// _SDF_Log(SDF_ERR, "------>SDF_Decrypt,puiDataLength=%d", *puiDataLength);
		}
	}
	return ret;
}



/*
描述：			使用指定的密钥句柄和IV对数据进行MAC运算
参数：			hSessionHandle[in]	与设备建立的会话句柄
				hKeyHandle[in]	    指定的密钥句柄
				uiAlgID[in]	        算法标识，指定MAC加密算法
				pucIV[in|out]	    缓冲区指针，用于存放输入和返回的IV数据
				pucData[in]	        缓冲区指针，用于存放输出的数据明文
				uiDataLength[in]	输出的数据明文长度
				pucMAC[out]	        缓冲区指针，用于存放输出的MAC值
				puiMACLength[out]	输出的MAC值长度
返回值：		0	成功
				非0	失败，返回错误代码
备注：			此函数不对数据进行分包处理，多包数据MAC运算由IV控制最后的MAC值.
*/
DLL u32 SDF_CalculateMAC(HANDLE hSessionHandle,
	HANDLE hKeyHandle,
	u32 uiAlgID,
	u8 *pucIV,
	u8 *pucData,
	u32 uiDataLength,
	u8 *pucMAC,
	u32  *puiMACLength)
{
	u32 ret = SDR_OK;
	sis_session* session = NULL;
	sis_work_key *key = NULL;

	if (pucMAC == NULL) {
		return 0;
	}

	if ((uiAlgID != SGD_SM4_MAC) && (uiAlgID != SGD_SM1_MAC)) {
		return   SDR_ALGNOTSUPPORT;
	}

	if ((pucIV == NULL) || (pucData == NULL)) {
		return SDR_INARGERR;
	}

	if ((uiDataLength % 16) != 0) {
		return SDR_INARGERR;
	}

	ret = LIB_GetSession(hSessionHandle, &session);
	ret = LIB_GetWorkKey(session, hKeyHandle, &key);
	if (ret == SDR_OK)
	{
		ret = C_CalculateMAC(session, uiAlgID, key,
			pucIV, pucData, uiDataLength,
			pucMAC, puiMACLength);
		if (ret != SDR_OK)
		{
			// _SDF_Log(SDF_ERR, "------>C_MAC,uiDataLength=%d", uiDataLength);
		}
	}
	return ret;
}
















